#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"  // Include the header file for menu functions

#define MAX_FILES 25  // Maximum number of files to list

/************************************* File Selection Menu *************************************
 * @param dir_path : Path to the directory containing the files.
 * @return         : Returns the name of the selected file as a dynamically allocated string.
 * @description    : This function lists all .txt files in the given directory, presents a menu 
 *                   for user selection, and returns the chosen file name. It ensures proper 
 *                   memory management by freeing unused allocations.
 **********************************************************************************************/

char* menu_select_file(const char *dir_path) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("Unable to open directory");
        return NULL;
    }

    struct dirent *entry;
    char *files[MAX_FILES];  // Array to store file names
    int file_count = 0;

    // Read files from the directory and store the names
    while ((entry = readdir(dir)) != NULL) {
        // Check if the file has a .txt extension and is a regular file
        if (strstr(entry->d_name, ".txt") != NULL && entry->d_type == DT_REG) {
            if (file_count < MAX_FILES) {
                files[file_count] = strdup(entry->d_name);  // Store file name
                file_count++;
            } else {
                break;  // Stop if we have reached the maximum number of files to list
            }
        }
    }
    closedir(dir);

    if (file_count == 0) {
        printf("\033[1;31mNo .txt files found in the directory.\033[0m\n");  // Red text
        return NULL;
    }

    // Display the menu with styling
    printf("\033[1;34m******************************************************\033[0m\n");  // Blue border
    printf("\033[1;34m*               Select a file to open:               *\033[0m\n");  // Blue border
    printf("\033[1;34m******************************************************\033[0m\n");  // Blue border
    printf("\033[1;32m\nChoose a file from the list below:\033[0m\n\n");  // Green text
    
    // Print the file list with separators
    for (int i = 0; i < file_count; i++) {
        printf("\033[1;37m------------------------------------------------------\033[0m\n");  // Separator line
        printf("\033[1;33m  %d. %s\033[0m\n", i + 1, files[i]);  // Yellow text for file names
    }

    // Get user input for selection
    int choice;
    printf("\033[1;37mEnter your choice (1-%d): \033[0m", file_count);  // White prompt
    scanf("%d", &choice);

    if (choice < 1 || choice > file_count) {
        printf("\033[1;31mInvalid choice.\033[0m\n");  // Red text for invalid input
        // Free memory for all files before returning
        for (int i = 0; i < file_count; i++) {
            free(files[i]);
        }
        return NULL;
    }

    // Return the selected file name
    char *selected_file = files[choice - 1];

    // Free memory for remaining file names
    for (int i = 0; i < file_count; i++) {
        if (i != choice - 1) {
            free(files[i]);
        }
    }

    return selected_file;
}
