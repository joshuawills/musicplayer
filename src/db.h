#pragma once

#include "common.h"

void init_db();

void close_db();

int add_song(char *path, char *title);