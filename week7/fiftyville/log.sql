-- Keep a log of any SQL queries you execute as you solve the mystery
-- see all the crimes descriptions that took a place in that paticular date
SELECT description FROM crime_scene_reports
WHERE year == 2021
AND month == 7
AND day == 28
AND street == 'Humphrey Street';
-- deg into the interviews
SELECT transcript FROM interviews
WHERE year == 2021
AND month == 7
AND day == 28
AND transcript LIKE '%bakery%';
-- detect the atm transactions at thet day early oin the morning
SELECT account_number FROM atm_transactions
WHERE year == 2021
AND month == 7
AND day == 28
AND atm_location == 'Leggett Street'
AND transaction_type LIKE '%withdraw%';
-- account nums that has been used to withdraw money thet day
-- 28500762
-- 28296815
-- 76054385
-- 49610011
-- 16153065
-- 25506511
-- 81061156
-- 26013199
-- check the id's of the people that own these account nums
SELECT person_id FROM bank_accounts
JOIN atm_transactions
ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.year == 2021
AND atm_transactions.month == 7
AND atm_transactions.day == 28
AND atm_transactions.atm_location == 'Leggett Street'
AND atm_transactions.transaction_type LIKE '%withdraw%';
-- determain the names of the people with these id's
SELECT name FROM people
JOIN bank_accounts
ON bank_accounts.person_id = people.id
JOIN atm_transactions
ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.year == 2021
AND atm_transactions.month == 7
AND atm_transactions.day == 28
AND atm_transactions.atm_location == 'Leggett Street'
AND atm_transactions.transaction_type LIKE '%withdraw%';
-- list of suspects
-- +---------+
-- |  name   |
-- +---------+
-- | Bruce   |
-- | Diana   |
-- | Brooke  |
-- | Kenny   |
-- | Iman    |
-- | Luca    |
-- | Taylor  |
-- | Benista |
-- +---------+
-- check the footage in the bakery parking at the ggiven time in the interview transcript
SELECT license_plate FROM bakery_security_logs
WHERE year == 2021
AND month == 7
AND day == 28
AND hour == 10
AND minute == 23;
-- trying to tight the list
SELECT name FROM people
JOIN bakery_security_logs
on bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.year == 2021
AND bakery_security_logs.month == 7
AND bakery_security_logs.day == 28
AND bakery_security_logs.hour == 10
AND bakery_security_logs.minute >= 18
AND bakery_security_logs.minute <= 23
AND name IN (SELECT name FROM people
JOIN bank_accounts
ON bank_accounts.person_id = people.id
JOIN atm_transactions
ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.year == 2021
AND atm_transactions.month == 7
AND atm_transactions.day == 28
AND atm_transactions.atm_location == 'Leggett Street'
AND atm_transactions.transaction_type LIKE '%withdraw%');
-- smaller list
-- +-------+
-- | name  |
-- +-------+
-- | Bruce |
-- | Luca  |
-- | Iman  |
-- | Diana |
-- +-------+
-- we knew from the previos list of susprects that the name Diana matches a name in the list we found after checkinmg the bank accounts so prpubly Diana is the theif
-- now we will check the flights in the next day
SELECT destination_airport_id FROM flights
JOIN airports
ON flights.origin_airport_id = airports.id
WHERE airports.city LIKE '%fiftyville%'
AND year == 2021
AND month == 7
AND day == 29
ORDER BY hour,minute
LIMIT 1;
-- +------------------------+
-- | destination_airport_id |
-- +------------------------+
-- | 4                      |
-- +------------------------+
SELECT distinct(city) FROM airports
WHERE id IN (SELECT destination_airport_id FROM flights
WHERE year == 2021
AND month == 7
AND day == 29
ORDER BY hour, minute LIMIT 1);
-- names of the city that had the earliest flight in the next day
-- +---------------+
-- |     city      |
-- +---------------+
-- | New York City |
-- +---------------+
-- check for who of that list was on the first flight
SELECT name FROM people
JOIN passengers
ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id = (SELECT id FROM flights
WHERE destination_airport_id = 4
AND year == 2021
AND month == 7
AND day == 29);
-- we end here with tow names at the suspects list which are
-- Bruce
-- Luca
-- know we want to find out the ACCOMPLICE who helped the theif
SELECT receiver FROM phone_calls
JOIN people
ON phone_calls.caller = people.phone_number
WHERE year == 2021
AND month == 7
AND day == 28
AND people.name  = 'Luca';
-- Luca didnt call anyone that day
SELECT receiver FROM phone_calls
JOIN people
ON phone_calls.caller = people.phone_number
WHERE year == 2021
AND month == 7
AND day == 28
AND people.name  = 'Bruce'
AND duration <= 60;
-- Bruce called four numbers that day and one of the calls didnt last more than one minute so he is the final suspect to be the theif eho stole the duck
--lets find out who helped Bruce to ran away from the city
SELECT name FROM people
WHERE phone_number = '(375) 555-8161';
-- Roben you mf you helped the theif to steal the duck 

