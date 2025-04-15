-- 1. Количество исполнителей в каждом жанре.
-- SELECT g.name AS genre, COUNT(eg.executor_id) AS executor_count 
-- FROM Genres g
-- LEFT JOIN ExecutorGenres eg ON eg.genre_id = g.genre_id
-- GROUP BY  g.genre_id, g.name;

-- 2. Количество треков, вошедших в альбомы 2019–2020 годов
-- SELECT COUNT(*) AS track_count
-- FROM Tracks t
-- JOIN Albums a ON t.album_id = a.album_id
-- WHERE year BETWEEN 2019 AND 2020;

-- 3. Средняя продолжительность треков по каждому альбому.
-- SELECT a.name AS album, AVG(t.duration) AS avg_duration
-- FROM Albums a
-- JOIN Tracks t ON a.album_id = t.album_id
-- GROUP BY a.album_id;

-- 4. Все исполнители, которые не выпустили альбомы в 2020 году.
-- SELECT e.name AS executor_name
-- FROM Executors e
-- WHERE e.executor_id NOT IN
-- (
--     SELECT ae.executor_id
--     FROM AlbumsExecutors ae
--     JOIN Albums a ON ae.album_id = a.album_id
--     WHERE a.year = 2020
-- );

-- 5. Названия сборников, в которых присутствует конкретный исполнитель (выберите его сами).
-- тут немного усложнил задание и вывел названия всех сборников в которых присутствует конкретный исполнитель
SELECT c.name AS compilation_name, e.name  AS executor_name
FROM Compilations c
JOIN Executors e ON c.name ILIKE '%' || e.name || '%';