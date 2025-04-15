-- 1. Названия альбомов, в которых присутствуют исполнители более чем одного жанра.
SELECT DISTINCT a.name
FROM Albums a
JOIN AlbumsExecutors ae ON a.album_id = ae.album_id
JOIN ExecutorGenres eg ON ae.executor_id = eg.executor_id
GROUP BY a.album_id, a.name
HAVING COUNT(DISTINCT eg.genre_id) > 1;

-- 2. Наименования треков, которые не входят в сборники.
SELECT *
FROM Tracks t
LEFT JOIN CompilationTracks ct ON t.track_id = ct.track_id
WHERE ct.track_id IS NULL;

-- 3. Исполнитель или исполнители, написавшие самый короткий по продолжительности трек, — теоретически таких треков может быть несколько.
WITH MinDuration AS (
    SELECT MIN(duration) AS min_dur FROM Tracks
)
SELECT DISTINCT e.name
FROM Tracks t
jOIN Albums a ON t.album_id = a.album_id
JOIN AlbumsExecutors ae ON a.album_id = ae.album_id
JOIN Executors e ON ae.executor_id = e.executor_id
JOIN MinDuration md ON t.duration = md.min_dur;

-- 4. Названия альбомов, содержащих наименьшее количество треков.
WITH TrackCounts AS (
    SELECT album_id, COUNT(*) as track_count
    FROM Tracks
    GROUP BY album_id
),
MinCount AS (
    SELECT MIN(track_count) AS min_count FROM TrackCounts
)
SELECT a.name
FROM Albums a
jOIN TrackCounts tc ON a.album_id = tc.album_id
JOIN MinCount mc ON tc.track_count = mc.min_count;