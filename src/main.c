#include "common.h"
#include "background.h"
#include "db.h"
#include "../include/raylib.h"

// Ensure the MySQL development library is installed and the include path is configured correctly.

#define SONG_TITLE_WIDTH 500 
#define SONG_TITLE_HEIGHT 50 
#define SONG_MAX 10 

FilePathList music_list;

int width = 1920;
int height = 1080;

int main(void)
{
    #ifdef DEBUG
        printf("Debug mode enabled\n");
    #endif

    init_db();

    // if (!is_db_setup()) {

    // }

    // Generic Setup
    SetRandomSeed(time(NULL));

    InitWindow(width, height, "Music Player");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    InitAudioDevice();
    width = GetScreenWidth();
    height = GetScreenHeight();
    SetTargetFPS(144);
    
    // Initialising the balls
    init_balls(width, height);

    // Setting up the music
    music_list = LoadDirectoryFiles("resources");

    bool pause = false;
    float timePlayed = 0.0f;
    Music music = LoadMusicStream("resources/letdown.mp3");
    PlayMusicStream(music);

    // Main game loop
    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);

        // Handle the pausing of the music with the space bar
        if (IsKeyPressed(KEY_SPACE)) {
            pause = !pause;

            if (pause) PauseMusicStream(music);
            else ResumeMusicStream(music);
        }

        // Bouncing ball logic
        if (!pause) {
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

        // Draw list of songs
        int heightRel = (GetScreenHeight() / 2) - (SONG_TITLE_HEIGHT / 2) - (max_number(SONG_MAX, music_list.count));
        for (int i = 0; i < music_list.count; i++) {
            width = GetScreenWidth();
            int x = (width / 2) - (SONG_TITLE_WIDTH / 2);
            int y = heightRel + (i * SONG_TITLE_HEIGHT) + (i % 2 == 1 ? 20 : 0);
            DrawRectangle(x, y, SONG_TITLE_WIDTH, SONG_TITLE_HEIGHT, TERTIARY_COLOR);
            DrawText(music_list.paths[i], x + SONG_TITLE_WIDTH / 10, y + SONG_TITLE_HEIGHT / 3, 30, GRAY);
        }

        // Draw music bar
        timePlayed = GetMusicTimePlayed(music) / GetMusicTimeLength(music);
        if (timePlayed > 1.0f) timePlayed = 1.0f;
        DrawRectangle((int) (GetScreenWidth() / 2)- 200, GetScreenHeight() - 75, 400, 50, DARKGRAY);
        DrawRectangle((int) (GetScreenWidth() / 2) - 200, GetScreenHeight() - 75, (int)(timePlayed * 400.0f), 50, LIGHTGRAY);

        EndDrawing();
    }

    UnloadMusicStream(music);
    UnloadDirectoryFiles(music_list);
    CloseAudioDevice();
    CloseWindow();

    close_db();

    return 0;
}

