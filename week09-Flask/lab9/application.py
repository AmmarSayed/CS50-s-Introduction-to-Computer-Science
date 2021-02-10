import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_cors import CORS

# Configure application
app = Flask(__name__)
CORS(app)
# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.route("/", methods=["GET", "POST"])
def index():
    return render_template("/index.html")


@ app.route("/people", methods=["GET", "POST"])
def people():

    if request.method == "POST":
        # get the form data
        data = request.get_json()
        name = data["name"]
        month = data["month"]
        day = data["day"]
        if (name and month and day):
            db.execute(
                "INSERT INTO birthdays (name, day, month) VALUES(?,?,?)", name, day, month)
        else:
            print("not valid data")

    response = db.execute("SELECT * FROM birthdays")
    return jsonify(response)
