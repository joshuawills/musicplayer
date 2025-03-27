#include "common.h"
#include "render.h"
#include "db.h"
#include "state.h"
#include "../include/raylib.h"

#define SONG_TITLE_WIDTH 500 
#define SONG_TITLE_HEIGHT 50 

int main(void)
{

    #ifdef DEBUG
        printf("Debug mode enabled\n");
    #endif

    // Setting up the database
    init_db();

    State state = {0};
    init_state(&state);

    // Generic Setup
    SetRandomSeed(time(NULL));

    InitWindow(state.width, state.height, "Music Player");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    InitAudioDevice();
    SetTargetFPS(144);
    
    // Initialising the balls
    init_balls(&state);

    float timePlayed = 0.0f;
    
    state.currentSong = LoadMusicStream(state.songs[state.songIndex]->path);

    PlayMusicStream(state.currentSong);
    PauseMusicStream(state.currentSong);
    state.pause = true;

    // Main game loop
    while (!WindowShouldClose())
    {

        // Check if the song has ended
        if (GetMusicTimePlayed(state.currentSong) + 0.1 >= GetMusicTimeLength(state.currentSong)) {
            skip_song_forward(&state);
        }

        if (state.currPage != ADD_SONG_PAGE) {
            if (IsKeyPressed(KEY_SPACE)) {
                state.pause = !state.pause;
            }
            if (IsKeyPressed(KEY_RIGHT)) {
                skip_song_forward(&state);
            }
            if (IsKeyPressed(KEY_LEFT)) {
                skip_song_backward(&state);
            }
        }

        state.width = GetScreenWidth();
        state.height = GetScreenHeight();

        // Update the mouse
        state.mousePos.x = GetMouseX();
        state.mousePos.y = GetMouseY();
        state.mousePos.pressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        UpdateMusicStream(state.currentSong);

        check_pause_button(&state); 
        check_skip_button(&state);
        check_switch_button(&state);
        check_back_button(&state);
        check_song_time_switched(&state);
        if (state.currPage == ADD_SONG_PAGE) {
            check_song_dragged(&state);
            check_upload_button_pressed(&state);
        }

        if (state.pause) PauseMusicStream(state.currentSong);
        else ResumeMusicStream(state.currentSong);


        // Bouncing ball logic
        if (!state.pause) {
            update_balls(&state);
        }

        if (state.hover) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        } else {
            SetMouseCursor(MOUSE_CURSOR_ARROW);
        }
        
        BeginDrawing();
        
        draw_top_bar(&state);

        // Draw the background
        ClearBackground(state.backgroundColor);
        draw_balls(&state);

        #ifdef DEBUG
            DrawFPS(10, 10);
            DrawText(TextFormat("Screen Size: [%i, %i]", GetScreenWidth(), GetScreenHeight()), 10, 40, 10, GREEN);
            DrawText(get_page_from_state(&state), 10, 60, 10, GREEN);  
            DrawText(TextFormat("Song Index: [%i]", state.songIndex), 10, 80, 10, GREEN);
            DrawText(TextFormat("Song Duration v Time Elapsed: [%f] v [%f]", GetMusicTimeLength(state.currentSong), GetMusicTimePlayed(state.currentSong)), 10, 100, 10, GREEN);
        #endif

        draw_bottom_bar(&state);

        if (state.currPage == ADD_SONG_PAGE) {
            draw_add_song_page(&state);
        }

        EndDrawing();
        state.hover = false;
    }

    UnloadMusicStream(state.currentSong);
    CloseAudioDevice();
    CloseWindow();

    close_db();
    free_state(&state);

    return 0;
}

