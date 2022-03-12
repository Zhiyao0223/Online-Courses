-- Keep a log of any SQL queries you execute as you solve the mystery.

/*
Time  : 28 Jul 2020 (10:15am)
Venue : Chamberlin Street
Event : Duck Stolen
*/


-- Details of Event
SELECT description FROM crime_scene_reports
WHERE year = '2020' AND month = '7' AND day = '28';

/*
Event Description:
Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

Discover event happen time. Mention courthouse
*/


-- Investigate Witness Interview
SELECT name, transcript FROM interviews
WHERE year = '2020' AND month = '7' AND day = '28';

/*
Ruth :
Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.

Eugene :
I don't know the thief's name, but it was someone I recognized.
Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.

Raymond :
As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.
In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
The thief then asked the person on the other end of the phone to purchase the flight ticket.
*/


-- Investigate Courthouse Security Log
SELECT license_plate, hour, minute FROM courthouse_security_logs
WHERE year = '2020' AND month = '7' AND day = '28' AND hour = '10' AND minute <= '25' AND minute >= '15' AND activity = 'exit';

/*
License Plate   | Hour  | Minute
5P2BI95         | 10    | 16
94KL13X         | 10    | 18
6P58WS2         | 10    | 18
4328GD8         | 10    | 19
G412CB7         | 10    | 20
L93JTIZ         | 10    | 21
322W7JE         | 10    | 23
0NTHK55         | 10    | 23
*/


-- Check License Plate Owner
SELECT id, name, phone_number, passport_number, license_plate FROM people
WHERE license_plate = '5P2BI95'
    OR license_plate = '94KL13X'
    OR license_plate = '6P58WS2 '
    OR license_plate = '4328GD8'
    OR license_plate = 'G412CB7'
    OR license_plate = 'L93JTIZ '
    OR license_plate = '322W7JE'
    OR license_plate = '0NTHK55';

/*
id      | name      | phone_number      | passport_number   | license_plate
221103  | Patrick   | (725) 555-4692    | 2963008352        | 5P2BI95
398010  | Roger     | (130) 555-0289    | 1695452385        | G412CB7
467400  | Danielle  | (389) 555-5198    | 8496433585        | 4328GD8
514354  | Russell   | (770) 555-1861    | 3592750733        | 322W7JE
560886  | Evelyn    | (499) 555-9472    | 8294398571        | 0NTHK55
686048  | Ernest    | (367) 555-5533    | 5773159633        | 94KL13X
*/


-- Check ATM Transactions
SELECT name, atm_transactions.account_number FROM people
INNER JOIN bank_accounts ON bank_accounts.person_id = people.id
INNER JOIN atm_transactions ON year = '2020'
                                AND month = '7'
                                AND day = '28'
                                AND atm_location = 'Fifer Street'
                                AND transaction_type = 'withdraw'
                                AND atm_transactions.account_number = bank_accounts.account_number;


/*
Bank Transaction After Matching With Security Log
name        | account_number
Ernest      | 49610011
Russell     | 26013199 (excluded)
Roy         | 16153065 (excluded)
Bobby       | 28296815 (excluded)
Elizabeth   | 25506511 (excluded)
Danielle    | 28500762
Madison     | 76054385 (excluded)
Victoria    | 81061156 (excluded)
*/

-- Investigate Phone Call of Ernest and Danielle
SELECT name, caller, receiver FROM people
INNER JOIN phone_calls ON people.phone_number = receiver
                        AND year = '2020'
                        AND month = '7'
                        AND day = '28'
                        AND duration <= '60'
                        AND (caller = '(367) 555-5533' OR caller = '(389) 555-5198');

/*
name        | caller            | receiver
Berthold    | (367) 555-5533    | (375) 555-8161
*/


-- Check Fiftyville airport
SELECT * FROM airports
WHERE city = 'Fiftyville';

/*
8 | CSF | Fiftyville Regional Airport | Fiftyville
*/


-- Check Flight Schedule
SELECT abbreviation, full_name, city, hour, minute FROM flights
INNER JOIN airports ON origin_airport_id = '8'
                        AND year = '2020'
                        AND month = '7'
                        AND day = '29'
                        AND airports.id = destination_airport_id
ORDER BY hour ASC, minute ASC
LIMIT 1;

/*
abbreviation    | full_name         | city      | hour  | minute
LHR             | Heathrow Airport  | London    | 8     | 20
*/

