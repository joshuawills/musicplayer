#include "common.h"
#include "render.h"
#include "../include/raylib.h"
#include "db.h"

typedef struct {
    Vector2 pos;
    Vector2 speed;
} Ball;

Ball balls[NUM_BALLS] = {0};

#define TOP_BAR_HEIGHT 50 
#define BOTTOM_BAR_HEIGHT 100
#define SONG_BAR_THICKNESS 25
#define SONG_BAR_LENGTH 600
#define NUM_COLOR_COMBINATIONS 10


Color background_colors[NUM_COLOR_COMBINATIONS] = {
    BACKGROUND_COLOR,
    (Color) { 47, 60, 126, 1},
    (Color) { 16, 24, 32, 1},
    (Color) { 249, 97, 103, 1},
    (Color) { 153, 0, 17, 1},
    (Color) { 138, 170, 229, 1},
    (Color) { 44, 95, 45, 1},
    (Color) { 184, 80, 66, 1},
    (Color) { 55, 94, 151, 1},
    (Color) { 42, 49, 50, 1},

};

Color secondary_colors[NUM_COLOR_COMBINATIONS] = {
    SECONDARY_COLOR,
    (Color) { 251, 234, 235, 100},
    (Color) { 254, 231, 21, 100},
    (Color) { 249, 231, 149, 100},
    (Color) { 252, 246, 245, 100},
    (Color) { 255, 255, 255, 100},
    (Color) { 151, 188, 98, 100},
    (Color) { 167, 190, 174, 100},
    (Color) { 251, 101, 66, 100},
    (Color) { 118, 54, 38, 100},

};

static void draw_play_or_pause_button(State *state);

void init_balls(State *state) {
    int width = state->width;
    int height = state->height;
    for (int i = 0; i < NUM_BALLS; i++) {
        balls[i].pos.x = GetRandomValue(50, width - 50);
        balls[i].pos.y = GetRandomValue(TOP_BAR_HEIGHT + BALL_RADIUS, height - BOTTOM_BAR_HEIGHT - BALL_RADIUS);

        balls[i].speed.x = BALL_VELOCITY * (float)GetRandomValue(1, 100) / 100.0f;
        if (GetRandomValue(0, 1)) balls[i].speed.x *= -1;
        balls[i].speed.y = BALL_VELOCITY * (float)GetRandomValue(1, 100) / 100.0f;
        if (GetRandomValue(0, 1)) balls[i].speed.y *= -1;
    }
}

void update_balls(State *state) {
    int width = state->width;
    int height = state->height;
    for (int i = 0; i < NUM_BALLS; i++) {
        balls[i].pos.x += balls[i].speed.x;
        balls[i].pos.y += balls[i].speed.y;
        if ((balls[i].pos.x >= (width - BALL_RADIUS)) || (balls[i].pos.x <= BALL_RADIUS)) balls[i].speed.x *= -1.0f;
        if ((balls[i].pos.y >= (height - BALL_RADIUS - BOTTOM_BAR_HEIGHT)) || (balls[i].pos.y <= TOP_BAR_HEIGHT + BALL_RADIUS)) balls[i].speed.y *= -1.0f;
    }
}

void draw_balls(State *state) {
    for (int i = 0; i < NUM_BALLS; i++) {
        DrawCircleV(balls[i].pos, BALL_RADIUS, state->secondaryColor);
    }
}

void draw_top_bar(State *state) {
    // This is the entire top bar
    Rectangle topBar = { 0, 0, state->width, TOP_BAR_HEIGHT };
    DrawRectangleRec(topBar, BLACK);

    // This is the switch button
    draw_add_song_button(state);
}

void draw_bottom_bar(State *state) {

    float timePlayed = GetMusicTimePlayed(state->currentSong) / GetMusicTimeLength(state->currentSong);

    if (timePlayed > 1.0f) timePlayed = 1.0f;

    int width = state->width;
    int height = state->height;

    //  This is the entire bottom bar
    DrawRectangle(0, height - BOTTOM_BAR_HEIGHT, width, BOTTOM_BAR_HEIGHT, BLACK);

    // This is the total bar
    DrawRectangle((int) (width / 2) - (SONG_BAR_LENGTH / 2), height - (BOTTOM_BAR_HEIGHT / 2) - 25, SONG_BAR_LENGTH, SONG_BAR_THICKNESS, DARKGRAY);

    // This is the progress bar
    DrawRectangle((int) (width / 2) - (SONG_BAR_LENGTH / 2), height - (BOTTOM_BAR_HEIGHT / 2) - 25, (int)(timePlayed * (float) SONG_BAR_LENGTH), SONG_BAR_THICKNESS, LIGHTGRAY);

    if (state->songs[state->songIndex] != NULL) {
        DrawText(state->songs[state->songIndex]->name, (int) (width / 2) - (MeasureText(state->songs[state->songIndex]->name, 20) / 2), height - (BOTTOM_BAR_HEIGHT / 2) + 10, 20, WHITE);
    }

    draw_play_or_pause_button(state);    

    DrawRectangle((width / 2 ) + (SONG_BAR_LENGTH / 2) + 50, height - (BOTTOM_BAR_HEIGHT / 2) - 25, 100, 50, LIGHTGRAY);
    DrawText(">>", (width / 2 ) + (SONG_BAR_LENGTH / 2) + 80, height - (BOTTOM_BAR_HEIGHT / 2) - 25, 60, BLACK);

    DrawRectangle((width / 2 ) - (SONG_BAR_LENGTH / 2) - 250, height - (BOTTOM_BAR_HEIGHT / 2) - 25, 100, 50, LIGHTGRAY);
    DrawText("<<", (width / 2 ) - (SONG_BAR_LENGTH / 2) - 220, height - (BOTTOM_BAR_HEIGHT / 2) - 25, 60, BLACK);

}

static void draw_play_or_pause_button(State *state) {
    int width = state->width;
    int height = state->height;
    if (state->pause) {
        DrawTriangle((Vector2){ (width / 2) - 400, height - 75 },
            (Vector2){ (width / 2) - 400, height - 25 },
            (Vector2){ (width / 2) - 350, height - 50 }, LIGHTGRAY);
    } else {
        DrawRectangle((width / 2) - 400, height - 75, 15, 50, LIGHTGRAY);
        DrawRectangle((width / 2) - 375, height - 75, 15, 50, LIGHTGRAY);
    }
}

void check_switch_button(State *state) {
    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){ state->width - 90, 10, 80, TOP_BAR_HEIGHT - 20 })) {
        state->hover = true;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (state->currPage == ADD_SONG_PAGE) state->currPage = MAIN_PAGE;
            else state->currPage = ADD_SONG_PAGE;
        }
    }
}

void check_pause_button(State *state) {
    int width = state->width;
    int height = state->height;

    // Need to check if the pause button is pressed
    if (CheckCollisionPointTriangle(GetMousePosition(), (Vector2){ (width / 2) - 400, height - 75 },
                        (Vector2){ (width / 2) - 400, height - 25 },
                        (Vector2){ (width / 2) - 350, height - 50 })) {
        state->hover = true;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            state->pause = !state->pause;
        }
    }
}

void update_colors(State *state) {
    int colorIndex = state->colorIndex;
    while (colorIndex == state->colorIndex) {
        colorIndex = GetRandomValue(0, NUM_COLOR_COMBINATIONS - 1);
    }
    state->colorIndex = colorIndex;
    state->backgroundColor = background_colors[colorIndex];
    state->secondaryColor = secondary_colors[colorIndex];
}

void skip_song_backward(State *state) {
    state->songIndex--;
    if (state->songIndex < 0) {
        state->songIndex = state->songCount - 1;
    }
    UnloadMusicStream(state->currentSong);
    state->currentSong = LoadMusicStream(state->songs[state->songIndex]->path);
    PlayMusicStream(state->currentSong);

    update_colors(state);
}

void check_back_button(State* state) {
    int width = state->width;
    int height = state->height;

    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){ (width / 2 ) - (SONG_BAR_LENGTH / 2) - 250, height - (BOTTOM_BAR_HEIGHT / 2) - 25, 100, 50 })) {
        state->hover = true;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            skip_song_backward(state); 
        }
    }
}

void skip_song_forward(State *state) {
    state->songIndex++;
    if (state->songIndex == state->songCount) {
        state->songIndex = 0;
    }
    UnloadMusicStream(state->currentSong);
    state->currentSong = LoadMusicStream(state->songs[state->songIndex]->path);
    PlayMusicStream(state->currentSong);

    update_colors(state);
}

void check_skip_button(State *state) {
    int width = state->width;
    int height = state->height;

    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){ (width / 2 ) + (SONG_BAR_LENGTH / 2) + 50, height - (BOTTOM_BAR_HEIGHT / 2) - 25, 100, 50 })) {
        state->hover = true;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            skip_song_forward(state);   
        }
    }
}

void draw_add_song_button(State *state) {
    Rectangle addSongButton = { state->width - 90, 10, 80, TOP_BAR_HEIGHT - 20};
    DrawRectangleRec(addSongButton, TERTIARY_COLOR);
    if (state->currPage == ADD_SONG_PAGE) {
        DrawText("Back", addSongButton.x + 10, addSongButton.y + 10, 12, BLACK);
    } else {
        DrawText("Add Song", addSongButton.x + 10, addSongButton.y + 10, 12, BLACK);
    }
}

void draw_add_song_page(State *state) {
    int width = state->width;
    int height = state->height;

    int leftWidth = width / 2 - (3 * width / 8);
    int topHeight = height / 2 - (3 * height / 8);

    DrawRectangle(leftWidth, topHeight, (3 * width / 4), (3 * height / 4), TERTIARY_COLOR);
    DrawText("Add a Song to the Library", leftWidth + 10, topHeight + 10, 40, BLACK);

    DrawRectangle(leftWidth + (width * 0.1), topHeight + (height * 0.1), (width * 0.55) , height * 0.3, DARKGRAY);
    DrawText("Drag Song Here", leftWidth + (width * 0.1) + 10, topHeight + (height * 0.1) + 10, 20, BLACK);

    if (state->currentSongPath != NULL) {
        // We already have a song dropped
        DrawText(state->currentSongPath, leftWidth + (width * 0.1) + 10, topHeight + (height * 0.1) + 40, 20, BLACK);
    }

    Rectangle textBox = { leftWidth + (width * 0.1), topHeight + (height * 0.5), (width * 0.55), height * 0.1 };

    bool mouseOnTextBox = CheckCollisionPointRec(GetMousePosition(), textBox);
    if (mouseOnTextBox) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        int key = GetKeyPressed();

        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (state->letterCount < MAX_INPUT_CHARS))
            {
                state->name_buf[state->letterCount] = (char)key;
                state->name_buf[state->letterCount + 1] = '\0';
                state->letterCount++;
            }
            key = GetKeyPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            state->letterCount--;
            if (state->letterCount < 0) state->letterCount = 0;
            state->name_buf[state->letterCount] = '\0';
        }
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    DrawText("Song Name", leftWidth + (width * 0.1) + 10, topHeight + (height * 0.5) - 20, 20, BLACK);
    DrawRectangleRec(textBox, GRAY);
    if (mouseOnTextBox) {
        DrawRectangleLines(textBox.x, textBox.y, textBox.width, textBox.height, BLACK);
    } else {
        DrawRectangleLines(textBox.x, textBox.y, textBox.width, textBox.height, DARKGRAY);
    }

    DrawText(state->name_buf, (int)textBox.x + 5, (int)textBox.y + 8, 40, BLACK);


    int bottomRightX = leftWidth + (3 * width / 4);
    int bottomRightY = topHeight + (3 * height / 4);
    Rectangle submitButton = { bottomRightX - (width / 10), bottomRightY - (height / 10), (width * 0.08), height * 0.08 };
    DrawRectangleRec(submitButton, GRAY);
    DrawText("Upload", submitButton.x + 10, submitButton.y + 10, 20, BLACK);

}

void check_upload_button_pressed(State *state) {
    int width = state->width;
    int height = state->height;
    int leftWidth = width / 2 - (3 * width / 8);
    int topHeight = height / 2 - (3 * height / 8);
    int bottomRightX = leftWidth + (3 * width / 4);
    int bottomRightY = topHeight + (3 * height / 4);
    Rectangle submitButton = { bottomRightX - (width / 10), bottomRightY - (height / 10), (width * 0.08), height * 0.08 };
    bool mouseOnSubmit = CheckCollisionPointRec(GetMousePosition(), submitButton);
    if (mouseOnSubmit) {
        state->hover = true;
    }

    // Check if we can safely upload the song
    if (state->currentSongPath != NULL && state->name_buf[0] != '\0' && mouseOnSubmit && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        #ifdef DEBUG
            printf("Uploading song\n");
        #endif

        // name_buf must be UTF-8 encoded
        char *utf8_name = malloc(MAX_INPUT_CHARS + 1);
        convert_encoding(state->name_buf, utf8_name, MAX_INPUT_CHARS + 1);

        printf("SIGMA currentSongPath: %s\n", state->currentSongPath);
        char *utf8_path = malloc(MAX_INPUT_CHARS + 1);
        convert_encoding(state->currentSongPath, utf8_path, strlen(state->currentSongPath) + 1);

        add_song(utf8_path, utf8_name);
        free(utf8_name);
        free(utf8_path);
        state->currentSongPath = NULL;
        state->name_buf[0] = '\0';
        state->letterCount = 0;
        state->currPage = MAIN_PAGE;
        state->songs = load_songs(state);
    }
}

void check_song_dragged(State *state) {

    if (state->currentSongPath != NULL) {
        return;
    }

    int width = state->width;
    int height = state->height;

    int leftWidth = width / 2 - (3 * width / 8);
    int topHeight = height / 2 - (3 * height / 8);

    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){ leftWidth + (width * 0.1), topHeight + (height * 0.1), (width * 0.55), height * 0.3 })) {
        state->hover = true;
    }

    if (IsFileDropped()) {
        FilePathList droppedFiles = LoadDroppedFiles();
        char *name = malloc(strlen(droppedFiles.paths[0]) + 1);
        strcpy(name, droppedFiles.paths[0]);
        state->currentSongPath = name;
        UnloadDroppedFiles(droppedFiles);
    }
}

void check_song_time_switched(State *state) {
    int width = state->width;
    int height = state->height;

    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){ (width / 2 ) - (SONG_BAR_LENGTH / 2), height - (BOTTOM_BAR_HEIGHT / 2) - 25, SONG_BAR_LENGTH, SONG_BAR_THICKNESS })) {
        state->hover = true;
        // Want it so it doesn't apply until the mouse is let go (if the user is holding the mouse down)
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            float timePlayed = (GetMouseX() - (width / 2) + (SONG_BAR_LENGTH / 2)) / (float) SONG_BAR_LENGTH;
            SeekMusicStream(state->currentSong, timePlayed * GetMusicTimeLength(state->currentSong));
        }
    }
}