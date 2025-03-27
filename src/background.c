#include "common.h"
#include "background.h"
#include "../include/raylib.h"

typedef struct {
    Vector2 pos;
    Vector2 speed;
} Ball;

Ball balls[NUM_BALLS] = {0};

void init_balls(int width, int height) {
    for (int i = 0; i < NUM_BALLS; i++) {
        // #ifdef DEBUG
        //     printf("Width: %d, Height: %d\n, Rand: %d\n", GetScreenWidth(), GetScreenHeight(), GetRandomValue(0, width));
        // #endif
        balls[i].pos.x = GetRandomValue(50, width - 50);
        balls[i].pos.y = GetRandomValue(50, height - 50);

        balls[i].speed.x = BALL_VELOCITY;
        if (GetRandomValue(0, 1)) balls[i].speed.x *= -1;
        balls[i].speed.y = BALL_VELOCITY;
        if (GetRandomValue(0, 1)) balls[i].speed.y *= -1;
    }
}

void update_balls() {
    for (int i = 0; i < NUM_BALLS; i++) {
        balls[i].pos.x += balls[i].speed.x;
        balls[i].pos.y += balls[i].speed.y;
        if ((balls[i].pos.x >= (GetScreenWidth() - BALL_RADIUS)) || (balls[i].pos.x <= BALL_RADIUS)) balls[i].speed.x *= -1.0f;
        if ((balls[i].pos.y >= (GetScreenHeight() - BALL_RADIUS)) || (balls[i].pos.y <= BALL_RADIUS)) balls[i].speed.y *= -1.0f;
        // #ifdef DEBUG
        //     printf("Iteration value: %d. X: %d, Y: %d\n", i, balls[i].pos.x, balls[i].pos.y);
        // #endif
    }
}

void draw_balls() {
    for (int i = 0; i < NUM_BALLS; i++) {
        DrawCircleV(balls[i].pos, BALL_RADIUS, SECONDARY_COLOR);
    }
}