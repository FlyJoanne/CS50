-- Keep a log of any SQL queries you execute as you solve the mystery.

--Find crime scene description
sqlite> SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
|                                                                                                       description                                                                                                        |
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
| Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


--Check witnesses' interviews
sqlite> SELECT name, transcript FROM interviews WHERE month = 7 AND day = 28;
+---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
|  name   |                                                                                                                                                     transcript                                                                                                                                                      |
+---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| Jose    | “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”                                                                                                                               |
| Eugene  | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”                                                                                                                                                                                      |
| Barbara | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.                                                                                                                   |
| Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
| Lily    | Our neighboring courthouse has a very annoying rooster that crows loudly at 6am every day. My sons Robert and Patrick took the rooster to a city far, far away, so it may never bother us again. My sons have successfully arrived in Paris.                                                                        |
+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


--Check bakery security video for evidence
sqlite> SELECT activity, license_plate, hour, minute FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;
+----------+---------------+------+--------+
| activity | license_plate | hour | minute |
+----------+---------------+------+--------+
| exit     | 5P2BI95       | 10   | 16     |
| exit     | 94KL13X       | 10   | 18     |
| exit     | 6P58WS2       | 10   | 18     |
| exit     | 4328GD8       | 10   | 19     |
| exit     | G412CB7       | 10   | 20     |
| exit     | L93JTIZ       | 10   | 21     |
| exit     | 322W7JE       | 10   | 23     |
| exit     | 0NTHK55       | 10   | 23     |
+----------+---------------+------+--------+

--Check who own these cars
sqlite> SELECT id, name, passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25);
+--------+---------+-----------------+
|   id   |  name   | passport_number |
+--------+---------+-----------------+
| 221103 | Vanessa | 2963008352      |
| 243696 | Barry   | 7526138472      |
| 396669 | Iman    | 7049073643      |
| 398010 | Sofia   | 1695452385      |
| 467400 | Luca    | 8496433585      |
| 514354 | Diana   | 3592750733      |
| 560886 | Kelsey  | 8294398571      |
| 686048 | Bruce   | 5773159633      |
+--------+---------+-----------------+

--Check ATM transactions at Leggett Street earlier that morning:
sqlite> SELECT account_number, amount FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
+----------------+--------+
| account_number | amount |
+----------------+--------+
| 28500762       | 48     |
| 28296815       | 20     |
| 76054385       | 60     |
| 49610011       | 50     |
| 16153065       | 80     |
| 25506511       | 20     |
| 81061156       | 30     |
| 26013199       | 35     |
+----------------+--------+

--Check who withdrew money at that time:
sqlite> SELECT name, passport_number, phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'));
+---------+-----------------+----------------+
|  name   | passport_number |  phone_number  |
+---------+-----------------+----------------+
| Kenny   | 9878712108      | (826) 555-1652 |
| Iman    | 7049073643      | (829) 555-5269 |
| Benista | 9586786673      | (338) 555-6650 |
| Taylor  | 1988161715      | (286) 555-6063 |
| Brooke  | 4408372428      | (122) 555-4581 |
| Luca    | 8496433585      | (389) 555-5198 |
| Diana   | 3592750733      | (770) 555-1861 |
| Bruce   | 5773159633      | (367) 555-5533 |
+---------+-----------------+----------------+

-- so by checking the overlap, I have narrowed it down to three suspects: Luca, Diana and Bruce
-- now I want to find out who made phone calls to ask his/her accomplice to buy him/her air tickets
sqlite> SELECT caller.name, receiver.name, phone_calls.duration
   ...> FROM phone_calls
   ...> JOIN people AS caller
   ...> ON phone_calls.caller = caller.phone_number
   ...> JOIN people AS receiver
   ...> ON phone_calls.receiver = receiver.phone_number
   ...> WHERE month = 7 AND day = 28 AND phone_calls.duration < 60 AND caller IN (SELECT phone_number FROM people WHERE name = 'Luca' OR name = 'Diana' OR name = 'Bruce');
+-------+---------+----------+
| name  |  name   | duration |
+-------+---------+----------+
| Bruce | Robin   | 45       |
| Diana | Philip  | 49       |
+-------+---------+----------+

--Find the filght id and the city:
SELECT id FROM flights WHERE day = 29 AND month = 7 AND origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') ORDER BY hour LIMIT 1;
SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE id = (SELECT id FROM flights WHERE day = 29 AND month = 7 AND origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') ORDER BY hour LIMIT 1));

--Find the passenger:
sqlite> SELECT name FROM people WHERE name = 'Bruce' OR name = 'Diana' AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE day = 29 AND month = 7 AND origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') ORDER BY hour LIMIT 1));
+-------+
| name  |
+-------+
| Bruce |
+-------+

--So the thief is Bruce, he called Robin to fly to New York City.
