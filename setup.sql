-- Table for Artists
DROP DATABASE IF EXISTS music_library;
CREATE DATABASE music_library;
\c music_library;

-- CREATE TABLE artist (
--     id SERIAL PRIMARY KEY,
--     name VARCHAR(100) NOT NULL
-- );

-- Table for Songs
CREATE TABLE song (
    id SERIAL PRIMARY KEY,
    title VARCHAR(100) NOT NULL,
    absolute_file_path VARCHAR(255) NOT NULL,
    date_added TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Many-to-Many Relationship: Songs & Artists (For collaborations)
-- CREATE TABLE song_artist (
--     song_id INT NOT NULL,
--     artist_id INT NOT NULL,
--     PRIMARY KEY (song_id, artist_id),
--     CONSTRAINT fk_song FOREIGN KEY (song_id) REFERENCES song(id) ON DELETE CASCADE,
--     CONSTRAINT fk_artist FOREIGN KEY (artist_id) REFERENCES artist(id) ON DELETE CASCADE
-- );
