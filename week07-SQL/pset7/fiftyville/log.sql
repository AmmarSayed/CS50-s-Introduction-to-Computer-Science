-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street";
/*
Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.
*/

SELECT name, transcript FROM interviews WHERE year = 2020 AND month =7 AND day = 28 AND transcript LIKE "%courthouse%";
/*
name | transcript
Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.*/


SELECT activity, license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <=25;
/*
activity | license_plate
exit | 5P2BI95
exit | 94KL13X
exit | 6P58WS2
exit | 4328GD8
exit | G412CB7
exit | L93JTIZ
exit | 322W7JE
exit | 0NTHK55
*/

SELECT people.name, people.phone_number , people.passport_number, people.license_plate FROM people
INNER JOIN  bank_accounts ON bank_accounts.person_id =  people.id
INNER JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
INNER JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate
WHERE atm_transactions.atm_location LIKE "%Fifer%" AND atm_transactions.transaction_type = "withdraw"
AND atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28
AND courthouse_security_logs.hour = 10 AND courthouse_security_logs.minute >= 15 AND courthouse_security_logs.minute <=25;

/*
name        | phone_number      | passport_number   | license_plate
Ernest      | (367) 555-5533    | 5773159633        | 94KL13X
Russell     | (770) 555-1861    | 3592750733        | 322W7JE
Elizabeth   | (829) 555-5269    | 7049073643        | L93JTIZ
Danielle    | (389) 555-5198    | 8496433585        | 4328GD8
*/

-- CHECK for the departure flight from Fiftyville on 29th from one of the above passports
SELECT people.name, passengers.passport_number, airports.full_name, airports.city, flights.hour, flights.minute, flights.destination_airport_id FROM flights
INNER JOIN airports ON flights.origin_airport_id = airports.id
INNER JOIN passengers ON flights.id = passengers.flight_id
INNER JOIN people ON people.passport_number = passengers.passport_number
WHERE flights.year = 2020 AND flights.month = 7 AND flights.day = 29
AND (passengers.passport_number = 5773159633 OR passengers.passport_number = 3592750733 OR passengers.passport_number = 7049073643 OR passengers.passport_number = 8496433585 )
AND airports.full_name LIKE "%Fiftyville%"
ORDER BY flights.hour;

/*
name        | passport_number   | full_name                     | city          | hour  | minute    | destination_airport_id
Ernest      | 5773159633        | Fiftyville Regional Airport   | Fiftyville    | 8     | 20        | 4
Danielle    | 8496433585        | Fiftyville Regional Airport   | Fiftyville    | 8     | 20        | 4
Russell     | 3592750733        | Fiftyville Regional Airport   | Fiftyville    | 16    | 0         | 6 ////// NOT A SUSPECT AS HE DIDN'T FLY IN THE MORNING
*/

-- CHECK for phone calls for Ernest and Danielle ,duration is less than a minute
SELECT people.name, phone_calls.receiver, phone_calls.duration  FROM phone_calls
INNER JOIN people ON phone_calls.caller = phone_number
WHERE people.name = "Ernest" AND phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration <= 60;
/*
name    | receiver          | duration
Ernest  | (375) 555-8161    | 45 /////////////// YAaaaaaaaaaaaaaaaY the Thief
*/
SELECT people.name, phone_calls.receiver, phone_calls.duration  FROM phone_calls
INNER JOIN people ON phone_calls.caller = phone_number
WHERE people.name = "Danielle" AND phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration <= 60;
/*No phone calls*/

-- ACCOMPLICE phone number (375) 555-8161
SELECT name FROM people WHERE phone_number = "(375) 555-8161";
/*name
Berthold
*/

-- the destination airport is
SELECT full_name , city FROM airports WHERE id = 4;
/*
full_name           | city
Heathrow Airport    | London
*/