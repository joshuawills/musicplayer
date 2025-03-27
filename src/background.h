#pragma once

#define NUM_BALLS 50 
#define BALL_VELOCITY 2.0f
#define BALL_RADIUS 25

void init_balls(int width, int height);
void update_balls();
void draw_balls();