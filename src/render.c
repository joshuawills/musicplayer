#include "common.h"
#include "render.h"
#include "../include/raylib.h"

typedef struct {
    Vector2 pos;
    Vector2 speed;
} Ball;

Ball balls[NUM_BALLS] = {0};

void init_balls(State *state) {
    int width = state->width;
    int height = state->height;
    for (int i = 0; i < NUM_BALLS; i++) {
        balls[i].pos.x = GetRandomValue(50, width - 50);
        balls[i].pos.y = GetRandomValue(50, height - 50);

        balls[i].speed.x = BALL_VELOCITY * (float)GetRandomValue(1, 100) / 100.0f;
        if (GetRandomValue(0, 1)) balls[i].speed.x *= -1;
        balls[i].speed.y = BALL_VELOCITY * (float)GetRandomValue(1, 100) / 100.0f;
        if (GetRandomValue(0, 1)) balls[i].speed.y *= -1;
    }
}

void update_balls() {
    for (int i = 0; i < NUM_BALLS; i++) {
        balls[i].pos.x += balls[i].speed.x;
        balls[i].pos.y += balls[i].speed.y;
        if ((balls[i].pos.x >= (GetScreenWidth() - BALL_RADIUS)) || (balls[i].pos.x <= BALL_RADIUS)) balls[i].speed.x *= -1.0f;
        if ((balls[i].pos.y >= (GetScreenHeight() - BALL_RADIUS)) || (balls[i].pos.y <= BALL_RADIUS)) balls[i].speed.y *= -1.0f;
    }
}

void draw_balls() {
    for (int i = 0; i < NUM_BALLS; i++) {
        DrawCircleV(balls[i].pos, BALL_RADIUS, SECONDARY_COLOR);
    }
}

void draw_bottom_bar(State *state) {

    float timePlayed = GetMusicTimePlayed(state->currentSong) / GetMusicTimeLength(state->currentSong);

    if (timePlayed > 1.0f) timePlayed = 1.0f;

    int w = GetScreenWidth();
    int h = GetScreenHeight();

    //  This is the entire bottom bar
    DrawRectangle(4, h - 100, w - 8, 96, BLACK);

    // This is the total bar
    DrawRectangle((int) (w / 2)- 200, h - 75, 400, 50, DARKGRAY);

    // This is the progress bar
    DrawRectangle((int) (w / 2) - 200, h - 75, (int)(timePlayed * 400.0f), 50, LIGHTGRAY);

 


    if (state->pause) {
        DrawTriangle((Vector2){ (w / 2) - 302, h - 77 },
                         (Vector2){ (w / 2) - 302, h - 22 },
                         (Vector2){ (w / 2) - 248, h - 50 }, 
                        DARKGRAY);
    }
    DrawTriangle((Vector2){ (w / 2) - 300, h - 75 },
                         (Vector2){ (w / 2) - 300, h - 25 },
                         (Vector2){ (w / 2) - 250, h - 50 }, 
                        LIGHTGRAY);

}

void check_pause_button(State *state) {
    // Handle the pausing of the music with the space bar
    if (IsKeyPressed(KEY_SPACE)) {
        state->pause = !state->pause;
        return;
    }
    
    int width = state->width;
    int height = state->height;

    // Need to check if the pause button is pressed
    if (CheckCollisionPointTriangle(GetMousePosition(), (Vector2){ (width / 2) - 300, height - 75 },
                        (Vector2){ (width / 2) - 300, height - 25 },
                        (Vector2){ (width / 2) - 250, height - 50 })) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            state->pause = !state->pause;
        }
    } else {
        SetMouseCursor(MOUSE_CURSOR_ARROW);
    }

}