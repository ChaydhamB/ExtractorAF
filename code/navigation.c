#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>  // For GetConsoleScreenBufferInfo
#include "navigation.h"  // Include the header file for navigation functions

/***************************************************************************************************
 * @file        Navigation.c                                                                       *
 * @author      Chaydham baya - Asteelflash                                                        *
 * @brief       >|creates a simple multiple choice entry menu to choose the operation type          *
 *             >|contains terminal size configuration                                             *
 *             >|contains navigation menu styling                                                  *
 * @date        2025                                                                               *
 **************************************************************************************************/

/***************************************************************************************************
  * @brief       Get the terminal size (width and height) on Windows
  * @param[out]  width   : Pointer to store terminal width
  * @param[out]  height  : Pointer to store terminal height
  ***************************************************************************************************/
void get_terminal_size(int *width, int *height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        *width = 45;
        *height = 0;
    } else {
        *width = 80;  // Default width
        *height = 24; // Default height
    }
}

/***************************************************************************************************
  * @brief       Print a box around a string (for menu title and options)
  * @param[in]   text  : Text to be enclosed in a box
  * @param[in]   width : Width of the terminal
  ***************************************************************************************************/
void print_box(const char* text, int width) {
    int len = strlen(text);
    int padding = 2;
    int total_length = len + 2 * padding;
    int spaces = (width - total_length) / 2;
    
    // Top border
    printf("\033[1;34m╔");
    for (int i = 0; i < 52; i++) printf("═");
    printf("╗\033[0m\n");

    // Print the text with padding and centering
    printf("\033[1;34m║");
    for (int i = 0; i < spaces; i++) printf(" ");
    printf("\033[1;37m%s\033[0m", text);
    for (int i = 0; i < spaces; i++) printf(" ");
    printf("\033[1;34m \033[0m\n");

    // Bottom border
    printf("\033[1;34m╚");
    for (int i = 0; i < 52; i++) printf("═");
    printf("╝\033[0m\n");
}

/***************************************************************************************************
  * @brief       Display navigation menu and get user choice
  * @return      User choice (1-5)
  ***************************************************************************************************/
int navigate_menu() {
    system("chcp 65001");  // Set terminal to UTF-8 to support ANSI escape codes
    int choice;

    // Get terminal size
    int term_width, term_height;
    get_terminal_size(&term_width, &term_height);

    // Menu box dimensions
    int box_width = 53;
    int box_height = 6;
    int start_row = (term_height - box_height) / 2;

    // Add vertical offset before menu
    for (int i = 0; i < start_row - 1; i++) {
        printf("\n");
    }

    // Print menu title
    printf("                 ASTEELFLASH \u00A9 2025\n");
    print_box("\033[1;33m  \t Welcome to the EXTRACTOR Menu        \033[0m", box_width);

    // Print menu options
    print_box("1. Convert a single file", box_width);
    print_box("2. Convert all .txt files in the directory", box_width);
    print_box("3. Get data from a specific file", 53);
    print_box("4. Exit", box_width);
    print_box("5. Clear screen", box_width);

    // Get user choice
    printf("\n\033[1;37mEnter your choice (1-5): \033[0m");
    scanf("%d", &choice);

    return choice;
}
