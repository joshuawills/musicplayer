#pragma once

#include "common.h"
#include "state.h"

#define NUM_BALLS 50 
#define BALL_VELOCITY 2.0f
#define BALL_RADIUS 25

void init_balls(State *state);
void update_balls();
void draw_balls();

void draw_bottom_bar(State *state);
void check_pause_button(State *state);