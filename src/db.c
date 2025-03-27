#include "db.h"

#include "../include/raylib.h"
#include <libpq-fe.h>
#include <string.h>
#include <stdlib.h>

PGconn *conn;

void init_db() {
    conn = PQconnectdb("host=localhost dbname=music_library user=postgres");

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    #ifdef DEBUG
        printf("Connected to PostgreSQL successfully!\n");
    #endif
}

void close_db() {
    PQfinish(conn);
}

int add_song(char *path, char *title) {
    #ifdef DEBUG
        printf("Adding song to database\n");
    #endif
    char *query = malloc(1024);
    sprintf(query, "INSERT INTO song (absolute_file_path, title) VALUES ('%s', '%s')", path, title);

    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Failed to add song: %s", PQerrorMessage(conn));
        PQclear(res);
        free(query);
        return 1;
    }

    #ifdef DEBUG
        printf("Added song successfully\n");   
    #endif

    PQclear(res);
    free(query);
    return 0;
}

Song **load_songs(State *state) {
    char *query = "SELECT * FROM song";
    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Failed to load songs: %s", PQerrorMessage(conn));
        PQclear(res);
        return NULL;
    }

    int rows = PQntuples(res);
    Song **songs = malloc(sizeof(Song *) * rows);

    for (int i = 0; i < rows; i++) {
        songs[i] = malloc(sizeof(Song));
        songs[i]->name = malloc(1024);
        songs[i]->path = malloc(1024);

        strcpy(songs[i]->name, PQgetvalue(res, i, 1));
        strcpy(songs[i]->path, PQgetvalue(res, i, 2));
    }

    state->songCount = rows;
    printf("SIGMA songCount: %d\n", state->songCount);

    PQclear(res);
    #ifdef DEBUG
        printf("Loaded %d songs\n", rows);
    #endif
    return songs;
}