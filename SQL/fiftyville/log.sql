-- To find the description of the crimes that happened on that date
SELECT description
FROM crime_scene_reports
WHERE year = 2024 AND month = 7 AND day = 28 AND description LIKE '%CS50%';

-- To find the transcripts of the interviews
SELECT name, transcript
FROM interviews
WHERE year = 2024 AND month = 7 AND day = 28
AND transcript LIKE '%bakery%';

-- Determining the flight that the thief took
SELECT city FROM airports WHERE id = 
    (SELECT destination_airport_id
    FROM flights
    WHERE year = 2024 AND month = 7 AND day = 29
    ORDER BY hour,minute
    LIMIT 1);

SELECT people.name AS suspects FROM people
JOIN phone_calls AS ph ON people.phone_number = ph.caller
JOIN passengers AS p ON people.passport_number = p.passport_number
JOIN flights AS f ON p.flight_id = f.id
-- Determining who was taking the flight
WHERE f.year = 2024 AND f.month = 7 AND f.day = 29
AND f.destination_airport_id = (
    SELECT destination_airport_id
    FROM flights
    WHERE year = 2024 AND month = 7 AND day = 29
    ORDER BY hour,minute
    LIMIT 1
)
AND people.name IN (
    -- Suspects according to the atm transactions and license plate and phone call
    SELECT people.name FROM people
    JOIN bakery_security_logs AS b ON b.license_plate = people.license_plate
    JOIN bank_accounts ON bank_accounts.person_id = people.id
    JOIN atm_transactions AS a ON a.account_number = bank_accounts.account_number
    WHERE a.year = 2024 AND a.month = 7 AND a.day = 28 
    AND a.atm_location = 'Leggett Street' AND a.transaction_type = 'withdraw'
    AND b.year = 2024 AND b.month = 7 AND b.day = 28 AND b.hour = 10 
    AND b.minute BETWEEN 15 AND 25 
    AND ph.year = 2024 AND ph.month = 7 AND ph.day = 28 AND ph.duration < 60
);

SELECT name FROM people 
WHERE phone_number = (
    SELECT receiver FROM phone_calls
    WHERE caller = (
    SELECT phone_number FROM people
    WHERE name = 'Bruce'
    AND year = 2024 AND month = 7 AND day = 28 AND duration < 60
));