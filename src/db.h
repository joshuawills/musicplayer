#pragma once

#include "common.h"
#include "state.h"

void init_db();

void close_db();

int add_song(char *path, char *title);

Song **load_songs(State *state);