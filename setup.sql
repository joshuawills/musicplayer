DROP DATABASE IF EXISTS `Media_Player`;
CREATE DATABASE `Media_Player`;
USE `Media_Player`;

DROP DATABASE IF EXISTS `Media_Player`;
CREATE DATABASE `Media_Player`;
USE `Media_Player`;

-- Table for Artists
CREATE TABLE artist (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL
);

-- Table for Albums
CREATE TABLE album (
    id INT AUTO_INCREMENT PRIMARY KEY,
    artist_id INT NOT NULL,
    title VARCHAR(100) NOT NULL,
    release_date DATE,
    FOREIGN KEY (artist_id) REFERENCES artist(id) ON DELETE CASCADE
);

-- Table for Songs
CREATE TABLE song (
    id INT AUTO_INCREMENT PRIMARY KEY,
    album_id INT,
    title VARCHAR(100) NOT NULL,
    absolute_file_path VARCHAR(255) NOT NULL,
    date_added TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    duration TIME,
    FOREIGN KEY (album_id) REFERENCES album(id) ON DELETE SET NULL
);

-- Many-to-Many Relationship: Songs & Artists (For collaborations)
CREATE TABLE song_artist (
    song_id INT NOT NULL,
    artist_id INT NOT NULL,
    PRIMARY KEY (song_id, artist_id),
    FOREIGN KEY (song_id) REFERENCES song(id) ON DELETE CASCADE,
    FOREIGN KEY (artist_id) REFERENCES artist(id) ON DELETE CASCADE
);
