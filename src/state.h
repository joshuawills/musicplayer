#pragma once

#include "common.h"
#include "../include/raylib.h"

#define SONG_MAX 1000

typedef enum {
    MAIN_PAGE,
    ADD_SONG_PAGE
} Page;

typedef struct {
    char *name;
    char *path;
} Song;

typedef struct {
    int pressed;
    int x;
    int y;
} Mouse;

typedef struct {
    Page currPage;
    int pause;
    int hover;

    Song **songs;
    int songIndex;
    Music currentSong;
    int songCount;

    Mouse mousePos;

    int width;
    int height;

    char name_buf[MAX_INPUT_CHARS + 1];
    int letterCount;

    char *currentSongPath;
} State;

void init_state(State *state);
void free_state(State *state);

char *get_page_from_state(State *state);