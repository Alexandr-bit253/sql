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