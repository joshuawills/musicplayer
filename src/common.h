#pragma once

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iconv.h>
#include <string.h>

// #define DEBUG

#define MAX_INPUT_CHARS 100 

int max_number(int a, int b);
void convert_encoding(const char *input, char *output, size_t out_size);

#define BACKGROUND_COLOR (Color) { 24, 24, 24, 1}
#define SECONDARY_COLOR (Color){ 245, 245, 245, 100}
#define TERTIARY_COLOR (Color){ 245, 245, 245, 180}