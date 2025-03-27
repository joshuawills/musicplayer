#!/usr/bin/env bash

gcc src/main.c src/render.c src/common.c src/db.c src/state.c -o main -O1 -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib  -I'~/raylib/include/' -L'~/raylib/lib' -lm -lpq