-- Table for Artists
DROP DATABASE IF EXISTS music_library;
CREATE DATABASE music_library;
\c music_library;

CREATE TABLE song (
    id SERIAL PRIMARY KEY,
    title VARCHAR(100) NOT NULL,
    absolute_file_path VARCHAR(255) NOT NULL,
    date_added TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
