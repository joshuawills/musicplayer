#include "db.h"

#include "../include/raylib.h"
#include <libpq-fe.h>
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
    char *query = malloc(1024);
    sprintf(query, "INSERT INTO songs (absolute_file_path, title) VALUES ('%s', '%s')", path, title);

    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Failed to add song: %s", PQerrorMessage(conn));
        PQclear(res);
        free(query);
        return 1;
    }

    PQclear(res);
    free(query);
    return 0;
}