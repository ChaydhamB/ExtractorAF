// file_utils.c
#include "file_utils.h"
#include <string.h>
#include <stdio.h>
 #include <dirent.h>

void change_extension_to_csv(char *filename) {
    char *dot = strrchr(filename, '.');
    if (dot && strcmp(dot, ".txt") == 0) {
        *dot = '\0';
    }
    strcat(filename, ".csv");
}

void modify_filename(const char *original, char *new_filename, const char *word) {
    char name_part[1024], ext_part[1024];
    char *dot = strrchr(original, '.');
    if (dot) {
        strncpy(name_part, original, dot - original);
        name_part[dot - original] = '\0';
        strcpy(ext_part, dot);
    } else {
        strcpy(name_part, original);
        ext_part[0] = '\0';
    }
    sprintf(new_filename, "%s_%s%s", name_part, word, ext_part);
}
/********************************************Get board Result*****************************************
 * @param cols  : Number of columns 
 *        rows  : Number of rows
 * @description : This function controls the terminal window buffer size
 ****************************************************************************************************/
void get_board_result() {
    char filename[1024];

    // Prompt user for the filename
    printf("\nEnter the filename to check the board result: \n");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line1[256] = "", line2[256] = "";
    char buffer[256];

    // Read file and store last two lines
    while (fgets(buffer, sizeof(buffer), file)) {
        strcpy(line1, line2);
        strcpy(line2, buffer);
    }
    fclose(file);

    // Remove newline characters if present
    line1[strcspn(line1, "\r\n")] = 0;
    line2[strcspn(line2, "\r\n")] = 0;

    // Check if last two lines match expected format
    if (strncmp(line1, "BOARDRESULT;", 12) == 0) {
        char *result = strchr(line1, ';'); 
        if (result) {
            result++; // Move past the semicolon
            printf("\n\033[1;33mBoard Test Result: \033[1;31m%s\033[0m\n", result);
            
            // Use strcmp for string comparison
            if (strcmp(result, "FAIL") == 0) {
                // Set fail_flag or a similar variable to indicate failure
                int fail_flag = 1;  // Local variable for fail_flag
                
                // You can call export_failed_tests here if needed
                export_failed_tests(filename);
            }
        } else {
            printf("\n\033[1;31mInvalid format in file.\033[0m\n");
        }
    } else {
        printf("\n\033[1;31mCould not find BOARDRESULT line in the file.\033[0m\n");
    }

    // Ask the user if they want to export failed tests to CSV
    //process_file(filename);
    getchar();  // Read the Enter key
    getchar();
}


/*************************************Process All Files********************************************
 * @param directory_path : Path to the directory containing .txt files
 * @description          : Processes all .txt files in the given directory
 ***************************************************************************************************/
void process_all_files(const char *directory_path) {
    DIR *dir = opendir(directory_path);
    if (dir == NULL) {
        perror("Unable to open directory");
        return;
    }

    struct dirent *entry;
    int file_count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".txt") != NULL) {
            printf("Processing file:\n %s\n", entry->d_name);
            if (++file_count > 10000) {
                printf("Too many files, stopping early...\n");
                break;
            }

            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", directory_path, entry->d_name);
            
            process_file(full_path);

            // Display the loading screen animation
            show_loading_screen();
        }
    }

    closedir(dir);
    printf("\n\033[1;32mAll files processed successfully!\033[0m\n");
}

