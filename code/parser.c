/***************************************************************************************************
 * @file        parser.c                                                                           *
 * @author      Chaydham Baya - Asteelflash                                                        *
 * @brief       Contains:                                                                          *
 *               > Loading screen animation                                                        *
 *               > Parsing logic                                                                   *
 *               > File processing (extension conversion)                                          *
 *               > Filename modifications                                                          *
 * @date        2025                                                                               *
 ***************************************************************************************************/

 #include "parser.h"
 #include "file_utils.h"
 #include <unistd.h>   // For usleep (Linux)
 #include <windows.h>  // For Sleep (Windows)
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <dirent.h>
 
 
 /************************************* Export Failed Tests ****************************************/
 void export_failed_tests(const char *filename) {
     int choice;
     int fail_flag = 0; // Assume no failure initially
     printf("\n1- Export the failed result to a CSV file\n");
     printf("2- Export the entire failed test to a CSV file\n");
     printf("3- Cancel\n");
     printf("Enter your choice: ");
     scanf("%d", &choice);
     
     if (choice == 3) {
         printf("Export cancelled.\n");
         return;
     }
     if (choice != 1 && choice != 2) {
         printf("Invalid choice. Please enter 1 or 2.\n");
         return;
     }
 
     char output_file[MAX_LINE];
     strcpy(output_file, filename);
     change_extension_to_csv(output_file);
 
     if (choice == 1) modify_filename(output_file, output_file, "FAIL_SCOOP");
     else if (choice == 2) modify_filename(output_file, output_file, "FAILED_FULL");
 
     FILE *input_file = fopen(filename, "r");
     FILE *csv_file = fopen(output_file, "w");
     if (!input_file || !csv_file) {
         perror("Error opening file");
         if (input_file) fclose(input_file);
         if (csv_file) fclose(csv_file);
         return;
     }
 
     fprintf(csv_file, "ICT log\nType of test;Board Num;Task name;Task number;Test number;Description;Result;Measure;Low limit;High limit;Unit;Test point;Unique test ID\n");
     char line[MAX_LINE];
     while (fgets(line, sizeof(line), input_file)) {
         if (strncmp(line, "ANL;", 4) == 0) {
             if (choice == 1 && strstr(line, "FAIL")) parse_line(line, csv_file);
             else if (choice == 2) parse_line(line, csv_file);
         }
     }
     fclose(input_file);
     fclose(csv_file);
     printf("\033[1;32mFailed tests exported to: %s\033[0m\n", output_file);
 }
 
 /************************************* Custom strsep **********************************************/
 char *custom_strsep(char **stringp, const char *delim) {
    if (*stringp == NULL) return NULL;
    char *start = *stringp;
    char *ptr = strchr(start, delim[0]); // Find first occurrence of ';'

    if (ptr) {
        *ptr = '\0';  // Null-terminate the token
        *stringp = ptr + 1;  // Move pointer to next character after ';'
        if (*stringp[0] == '\0') *stringp = NULL;  // Handle trailing empty field
    } else {
        *stringp = NULL;  // No more delimiters found
    }
    return (*start == '\0') ? "" : start;  // Ensure empty fields return ""
}

 
 
 /************************************* Parse Line Function ***************************************/
 void parse_line(char *line, FILE *csv_file) {
     char *tokens[14];
     char *ptr = line;
     for (int i = 0; i < 14; i++) tokens[i] = custom_strsep(&ptr, ";");
     fprintf(csv_file, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", tokens[0], tokens[1], tokens[2], tokens[3], tokens[4],
             tokens[5], tokens[6], tokens[7], tokens[8], tokens[9], tokens[10], tokens[11], tokens[12], tokens[13]);
 }
 
 
 /************************************* Process Single File ***************************************/
 void process_file(const char *filename) {
     FILE *input_file = fopen(filename, "r");
     if (!input_file) {
         perror("Error opening file");
         return;
     }
     char output_file[MAX_LINE];
     strcpy(output_file, filename);
     change_extension_to_csv(output_file);
     FILE *csv_file = fopen(output_file, "w");
     if (!csv_file) {
         perror("Error opening output file");
         fclose(input_file);
         return;
     }
     fprintf(csv_file, "ICT log\nType of test;Board Num;Task name;Task number;Test number;Description;Result;Measure;Low limit;High limit;Unit;Test point;Unique test ID\n");
     char line[MAX_LINE];
     while (fgets(line, sizeof(line), input_file)) if (strncmp(line, "ANL;", 4) == 0) parse_line(line, csv_file);
     fclose(input_file);
     fclose(csv_file);
     printf("\033[1;32mFile converted to CSV successfully: %s\033[0m\n", output_file);
 }
 