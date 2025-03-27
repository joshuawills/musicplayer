#include "state.h"
#include "../include/raylib.h"
#include "db.h"

void init_state(State *state) {
    state->currPage = MAIN_PAGE;
    state->pause = false;
    state->hover = false;
    state->songIndex = 0;
    state->songs = load_songs(state);
    state->mousePos.pressed = 0;
    state->mousePos.x = 0;
    state->mousePos.y = 0;
    state->width = 1920;
    state->height = 1080;
    state->name_buf[0] = '\0';
    state->letterCount = 0;
    
    state->currentSongPath = NULL;
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

char *get_page_from_state(State *state) {
    switch (state->currPage) {
        case MAIN_PAGE:
            return "Main Page";
        case ADD_SONG_PAGE:
            return "Add Song Page";
        default:
            return "Unknown Page";
    }
}
