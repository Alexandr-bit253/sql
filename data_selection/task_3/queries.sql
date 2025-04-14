SELECT name AS track_name, duration
FROM Tracks
WHERE duration=(SELECT MAX(duration) FROM Tracks);

SELECT name AS track_name, duration
FROM Tracks
WHERE duration>='00:03:30';

SELECT name AS compilation_name, year 
FROM Compilations
WHERE year BETWEEN 2018 AND 2020;

SELECT name AS executor_name
FROM Executors
WHERE name NOT LIKE '% %';

SELECT name AS track_name 
FROM Tracks
WHERE name ILIKE '%мой%' OR name ILIKE '%my%';