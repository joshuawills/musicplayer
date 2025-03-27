#pragma once

#include "common.h"
#include "state.h"

#define NUM_BALLS 50 
#define BALL_VELOCITY 2.0f
#define BALL_RADIUS 25

void init_balls(State *state);
void update_balls(State *state);
void draw_balls();

void draw_top_bar(State *state);
void draw_bottom_bar(State *state);
void check_pause_button(State *state);
void check_switch_button(State *state);

void draw_add_song_button(State *state);
void draw_add_song_page(State *state);
void check_song_dragged(State *state);

void check_upload_button_pressed(State *state);
void check_skip_button(State *state);
void check_back_button(State* state);
void check_song_time_switched(State *state);

void skip_song_forward(State *state);
void skip_song_backward(State *state);