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
    Song **songs;
    Music currentSong;
    Mouse mousePos;
    int width;
    int height;
} State;

void init_state(State *state);
void free_state(State *state);