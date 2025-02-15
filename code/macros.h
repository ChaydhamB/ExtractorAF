#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>
#include <string.h>

// Platform-specific sleep
#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP(ms) usleep(ms * 1000)
#endif

// ANSI Colors
#define COLOR_GREEN "\033[1;32m"
#define COLOR_RESET "\033[0m"

// File handling with safety
#define OPEN_FILES(input, input_name, output, output_name) \
    FILE *input = fopen(input_name, "r"); \
    FILE *output = fopen(output_name, "w"); \
    if (!(input) || !(output)) { \
        perror("Error opening files"); \
        if (input) fclose(input); \
        if (output) fclose(output); \
        return; \
    }

// CSV processing
#define WRITE_CSV_HEADER(file) \
    fprintf((file), "ICT log\nType of test;Board Num;Task name;Task number;Test number;Description;Result;Measure;Low limit;High limit;Unit;Test point;Unique test ID\n")

#define PARSE_TOKENS(ptr, tokens) \
    for (int i = 0; i < 14; i++) (tokens)[i] = custom_strsep(&(ptr), ";")

#define PRINT_TOKENS(file, tokens) \
    fprintf((file), "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", \
            (tokens)[0], (tokens)[1], (tokens)[2], (tokens)[3], (tokens)[4], \
            (tokens)[5], (tokens)[6], (tokens)[7], (tokens)[8], (tokens)[9], \
            (tokens)[10], (tokens)[11], (tokens)[12], (tokens)[13])

#endif // MACROS_H