import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    allStocks = db.execute("SELECT stocks.stock, sum(stocks.buy - stocks.sell) as 'shares' , updatedPrices.latest_price ,(stocks.buy + stocks.sell)* updatedPrices.latest_price as 'total' FROM stocks INNER JOIN  updatedPrices on stocks.stock = share WHERE stocks.user_id = ? GROUP BY stocks.stock HAVING shares <> 0", user_id)

    # get current balance
    curntBalance = round(
        (db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]), 2)

    # total cost for purchased stocks
    totalStocksBuyCost = db.execute(
        "SELECT SUM(total) as 'total' from (SELECT stocks.stock, sum(stocks.buy - stocks.sell) as 'shares' , stocks.price ,updatedPrices.latest_price ,SUM(stocks.buy - stocks.sell)* updatedPrices.latest_price as 'total' FROM stocks INNER JOIN  updatedPrices on stocks.stock = share WHERE stocks.user_id = ? GROUP BY stocks.stock HAVING shares <> 0 ) ", user_id)[0]["total"]

    if not totalStocksBuyCost:
        totalStocksBuyCost = 0
    else:
        totalStocksBuyCost = round(totalStocksBuyCost, 2)

    TotalWealth = (totalStocksBuyCost + curntBalance)

    return render_template("index.html", stocks=allStocks, curntBalance=curntBalance, totalStocksBuyCost=totalStocksBuyCost, TotalWealth=TotalWealth)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        amount = request.form.get("shares")
        if not amount or not amount.isnumeric():
            return apology("Please Enter a valid number!")

        amount = int(amount)
        if amount <= 0:
            return apology("Please Enter a valid number!")
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("Stock Not found!")

        # if found then get the symbol it self
        symbol = stock["symbol"]

        stockPrice = lookup(request.form.get("symbol"))["price"]

        totalCost = stockPrice * amount
        # check the total amount user have enough balance
        currentUser = session["user_id"]
        curntBalance = db.execute(
            "SELECT cash FROM users WHERE id = ?", currentUser)[0]["cash"]
        if curntBalance < totalCost:
            return apology("Not enough Balance!")

        # buy the stock
        trans_date = datetime.now().strftime("%d-%b-%Y %H:%M:%S")

        db.execute("INSERT INTO stocks (user_id, stock, buy , price, trans_date, buy_sell,sell) VALUES(?,?,?,?,?,'Buy', 0)",
                   currentUser, symbol, amount, stockPrice, trans_date)

        # check the if stock exists in the updatedPrice table
        checkStock = db.execute(
            "SELECT share FROM updatedPrices WHERE share = ?", symbol)
        if not checkStock:
            db.execute(
                "INSERT INTO updatedPrices (share, latest_price) VALUES(?,?)", symbol, stockPrice)
        elif checkStock:
            db.execute(
                "UPDATE updatedPrices SET latest_price = ? WHERE share = ?", stockPrice, symbol)

        # update users current balance
        newBalance = curntBalance - totalCost

        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   newBalance, currentUser)
        return redirect("/")
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    allStocks = db.execute(
        "SELECT stock, (buy+sell) as 'shares' ,buy_sell, trans_date, price,(price * (buy+sell)) as 'total' FROM stocks WHERE user_id =? ORDER BY trans_date DESC;", user_id)

    return render_template("history.html", stocks=allStocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if not len(rows) == 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        mySymbol = request.form.get("symbol")
        myQuote = lookup(mySymbol)
        if not myQuote:
            return apology("invalid sumbol, please try again!", 400)
        return render_template("quoted.html", quote=myQuote)
    return render_template("/quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        userName = request.form.get("username")
        password = request.form.get("password")
        passwordConf = request.form.get("confirmation")

        if not userName:
            return apology("must provide a username", 400)
        elif not password:
            return apology("must provide a password", 400)
        elif passwordConf != password:
            return apology("Passwords doesn't match", 400)

        # check if the username matches another user in database
        usernamecheck = db.execute(
            "SELECT username FROM users WHERE username = ?", userName)

        if usernamecheck:
            usernamecheck = usernamecheck[0]['username']

        if len(usernamecheck) != 0:
            return apology("User Name already exist", 400)

        # update database for username and hash new password
        hashedPAss = generate_password_hash(passwordConf)
        db.execute("INSERT INTO users (username,hash) VALUES(?,?)",
                   userName, hashedPAss)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", userName)
        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        return redirect("/")

    return render_template("/register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        # validate user input
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("Not a valid symbol!")

        numbertoSell = request.form.get("shares")
        if not numbertoSell:
            return apology("Please enter a valid number!")
        numbertoSell = int(numbertoSell)
        if numbertoSell <= 0:
            return apology("Please enter a valid number!")

        # if found then get the symbol it self
        symbol = stock["symbol"]

        # check availability in stock
        user_id = session["user_id"]

        totalPurchased = db.execute(
            "SELECT sum(buy) as amount FROM 'stocks' WHERE  user_id = ? AND stock = ?;", user_id, symbol)[0]["amount"]
        if not totalPurchased:
            return apology("You don't have enough Stocks!")

        totalSold = db.execute(
            "SELECT sum(sell) as amount FROM 'stocks' WHERE  user_id = ? AND stock = ?;", user_id, symbol)[0]["amount"]

        availStock = totalPurchased - totalSold
        if not availStock > 0:
            return apology("You don't have this stock!")
        elif availStock < numbertoSell:
            return apology("You don't have enough stocks to sell!")

        trans_date = datetime.now().strftime("%d-%b-%Y %H:%M:%S")
        # get the most updated current price
        updatedStockPrice = lookup(symbol)["price"]

        # update stock
        db.execute("INSERT INTO stocks (user_id, stock, sell, price, trans_date,buy_sell, buy) VALUES(?,?,?,?,?,'Sell',0)",
                   user_id, symbol, numbertoSell, updatedStockPrice, trans_date)

        # update the price of the stock sold
        db.execute(
            "UPDATE updatedPrices SET latest_price = ? WHERE share = ?", updatedStockPrice, symbol)

        # total cost to sold stocks
        totalCost = numbertoSell * updatedStockPrice

        # update users current balance
        curntBalance = db.execute(
            "SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        newBalance = curntBalance + totalCost

        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   newBalance, user_id)
        return redirect("/")

    return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
