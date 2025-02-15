// animation.c
#include "animation.h"
#include <stdio.h>
#include <windows.h>

void show_loading_screen() {
    const char *loading_chars = "|/-\\";
    int i = 0;
    while (i < 5) {
        printf("\r\033[1;32mProcessing %c\033[0m", loading_chars[i % 4]);
        fflush(stdout);
        Sleep(100);
        i++;
    }
}

void stop_loading_screen() {
    printf("\r\033[1;32mDone!                    \033[0m\n");
    fflush(stdout);
}

/*************************************Setting Command Window Size************************************
 * @param cols  : Number of columns 
 *        rows  : Number of rows
 * @description : This function controls the terminal window buffer size
 ***************************************************************************************************/
void setConsoleSize(int cols, int rows) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = {cols, rows};
    SetConsoleScreenBufferSize(hOut, bufferSize);
    SMALL_RECT windowSize = {0, 0, cols - 1, 30};
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);
}
/*******************************************End setConsoleSize***************************************/