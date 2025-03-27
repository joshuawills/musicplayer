#include "state.h"
#include "../include/raylib.h"

void init_state(State *state) {
    state->currPage = MAIN_PAGE;
    state->pause = false;
    state->songs = malloc(sizeof(Song *) * SONG_MAX);
    state->mousePos.pressed = 0;
    state->mousePos.x = 0;
    state->mousePos.y = 0;
    state->width = 1920;
    state->height = 1080;
}

void free_state(State *state) {
    for (int i = 0; i < SONG_MAX; i++) {
        if (state->songs[i] != NULL) {
            free(state->songs[i]->name);
            free(state->songs[i]->path);
            free(state->songs[i]);
        }
    }
    free(state->songs);
}