#include "common.h"
#include "render.h"
#include "db.h"
#include "state.h"
#include "../include/raylib.h"

#define SONG_TITLE_WIDTH 500 
#define SONG_TITLE_HEIGHT 50 

int main(void)
{

    State state = {0};
    init_state(&state);

    #ifdef DEBUG
        printf("Debug mode enabled\n");
    #endif

    // Setting up the database
    init_db();

    // Generic Setup
    SetRandomSeed(time(NULL));

    InitWindow(state.width, state.height, "Music Player");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    InitAudioDevice();
    SetTargetFPS(144);
    
    // Initialising the balls
    init_balls(&state);

    float timePlayed = 0.0f;
    state.currentSong = LoadMusicStream("resources/letdown.mp3");
    PlayMusicStream(state.currentSong);
    PauseMusicStream(state.currentSong);
    state.pause = true;

    // Main game loop
    while (!WindowShouldClose())
    {

        state.width = GetScreenWidth();
        state.height = GetScreenHeight();

        // Update the mouse
        state.mousePos.x = GetMouseX();
        state.mousePos.y = GetMouseY();
        state.mousePos.pressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        UpdateMusicStream(state.currentSong);

        check_pause_button(&state); 
        if (state.pause) PauseMusicStream(state.currentSong);
        else ResumeMusicStream(state.currentSong);

        // Bouncing ball logic
        if (!state.pause) {
            update_balls();
        }
        
        BeginDrawing();

        // Draw border
        DrawRectangleLinesEx((Rectangle) { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, 4, LIGHTGRAY);

        // Draw the background
        ClearBackground(BACKGROUND_COLOR);
        draw_balls();

        #ifdef DEBUG
            DrawFPS(10, 10);
            DrawText(TextFormat("Screen Size: [%i, %i]", GetScreenWidth(), GetScreenHeight()), 10, 40, 10, GREEN);
        #endif

        draw_bottom_bar(&state);

        EndDrawing();
    }

    UnloadMusicStream(state.currentSong);
    CloseAudioDevice();
    CloseWindow();

    close_db();
    free_state(&state);

    return 0;
}

