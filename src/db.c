#include "db.h"

#define WIN32_LEAN_AND_MEAN
#include <mysql.h>

MYSQL* conn;

void init_db() {
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    // mysql_options(conn, MYSQL_OPT_SSL_MODE, (const char *)SSL_MODE_DISABLED);

    if (mysql_real_connect(conn, "localhost", "root", "Winter@23Winter@23", NULL, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Connection Failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    printf("Connection successful\n");
}

void close_db() {
    mysql_close(conn);
}

int is_db_setup() {

}