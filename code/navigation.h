#ifndef NAVIGATION_H
#define NAVIGATION_H

// Function to get the terminal size (width and height) on Windows
void get_terminal_size(int *width, int *height);

// Function to print a box around a string (for menu title and options)
void print_box(const char* text, int width);

// Function to display the navigation menu and get user choice
int navigate_menu();

#endif  // NAVIGATION_H
