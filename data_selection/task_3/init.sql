-- создание таблиц
CREATE TABLE IF NOT EXISTS Genres (
    genre_id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS Executors (
    executor_id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL
);

CREATE TABLE IF NOT EXISTS ExecutorGenres (
    executor_id INT REFERENCES Executors(executor_id),
    genre_id INT REFERENCES Genres(genre_id),
    PRIMARY KEY (executor_id, genre_id)
);

CREATE TABLE IF NOT EXISTS Albums (
    album_id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    year INT NOT NULL
);

CREATE TABLE IF NOT EXISTS AlbumsExecutors (
    album_id INT REFERENCES Albums(album_id),
    executor_id INT REFERENCES Executors(executor_id),
    PRIMARY KEY (album_id, executor_id)
);

CREATE TABLE IF NOT EXISTS Tracks (
    track_id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    duration INTERVAL NOT NULL,
    album_id INT REFERENCES Albums(album_id)
);

CREATE TABLE IF NOT EXISTS Compilations (
    compilation_id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    year INT NOT NULL
);

CREATE TABLE IF NOT EXISTS CompilationTracks (
    compilation_id INT REFERENCES Compilations(compilation_id),
    track_id INT REFERENCES Tracks(track_id),
    PRIMARY KEY (compilation_id, track_id)
);


INSERT INTO Genres (name) VALUES
    ('Rock'),
    ('Pop'),
    ('Hip-hop');

INSERT INTO Executors (name) VALUES
    ('Sex Pistols'),
    ('Michael Jackson'),
    ('Eminem'),
    ('System of a Down'),
    ('Metallica'),
    ('Adele');

INSERT INTO ExecutorGenres (executor_id, genre_id) VALUES
    (1, 1),
    (2, 2),
    (3, 3),
    (4, 1),
    (5, 1),
    (6, 2);

INSERT INTO Albums (name, year) VALUES
    ('Never Mind the Bollocks', 1977),
    ('Thriller', 1982),
    ('The Marshall Mathers LP', 2000),
    ('Toxicity', 2001),
    ('Future Nostalgia', 2020),
    ('25', 2019);

INSERT INTO AlbumsExecutors (album_id, executor_id) VALUES
    (1, 1),
    (2, 2),
    (3, 3),
    (4, 4),
    (5, 6),
    (6, 6);

INSERT INTO Tracks (name, duration, album_id) VALUES
    ('Anarchy in the UK', '00:03:31', 1),
    ('God Save the Queen', '00:03:20', 1),
    ('Thriller', '00:05:58', 2),
    ('Beat It', '00:04:18', 2),
    ('The Real Slim Shady', '00:04:44', 3),
    ('Stan', '00:06:44', 3),
    ('Chop Suey!', '00:03:30', 4),
    ('Toxicity', '00:03:39', 4),
    ('My Way', '00:04:15', 2),
    ('Мой город', '00:03:50', 4),
    ('Hello', '00:04:55', 5),
    ('Send My Love', '00:03:43', 5),
    ('Don’t Start Now', '00:03:03', 6),
    ('Levitating', '00:03:23', 6);

INSERT INTO Compilations (name, year) VALUES
    ('Punk Classics', 2005),
    ('Pop Legends', 2010),
    ('Rap Essentials', 2015),
    ('Rock Revolution', 2020),
    ('Best of 2019', 2019),
    ('Summer Hits 2018', 2018);

INSERT INTO CompilationTracks (compilation_id, track_id) VALUES
    (1, 1),
    (1, 2),
    (2, 3),
    (2, 4),
    (3, 5),
    (3, 6),
    (4, 7),
    (4, 8),
    (5, 9),
    (6, 10),
    (2, 11),
    (2, 12);