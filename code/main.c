/***************************************************************************************************
 * @file        main.c                                                                             *
 * @author      Chaydham baya - Asteelflash                                                        *
 * @brief       Main program to sequence calling the functions                                     *
 * @date        2025                                                                               *
 **************************************************************************************************/

 #include <stdio.h>
 #include <string.h>
 #include "parser.c"
 #include "menu.c"
 #include "animation.c"
 #include "navigation.c"
 #include "file_utils.c"  // For file utility functions like change_extension_to_csv
 #include <windows.h>  // For Sleep function
 
 /*************************************Main Program Entry********************************************
  * @description : This is the main entry point of the program. It initializes the console size, 
  *                displays the navigation menu, and processes user input for file conversion.
  **************************************************************************************************/






 int main() {
    setConsoleSize(54,1000);
     int choice;
     const char *directory_path = "./";  // Set the directory path to scan for files
     char output_file_name[1024];
 
     // Loop to keep showing the navigation menu until the user chooses to exit
     do {
         // Display the navigation menu and get the user's choice
         choice = navigate_menu();  // Function from navigation.c
         getchar();
         switch (choice) {
             case 1: {
                 /*************************************Single File Processing******************************
                  * @description : Allows the user to select a single file and process it into a CSV format.
                  *******************************************************************************************/
                 char *selected_file = menu_select_file(directory_path);  // Function from menu.c
                 
                 if (selected_file == NULL) {
                     printf("No valid file selected.\n");
                     break;
                 }
 
                 // Open the selected file (replacing "input.txt" with the chosen file)
                 strcpy(output_file_name, selected_file);
                 change_extension_to_csv(output_file_name);  // Change the extension to .csv
 
                 FILE *input_file = fopen(selected_file, "r");
                 FILE *csv_file = fopen(output_file_name, "w");
 
                 if (!input_file || !csv_file) {
                     perror("Error opening file");
                     break;
                 }
 
                 // Writing CSV header
                 fprintf(csv_file, "ICT log\n Type of test;Board Num;Task name;Task number;Test number;Description;;Result;Measure;Low limit;High limit;Unit;Test point;Unique test ID\n");
 
                 char line[MAX_LINE];
                 int line_count = 0;
 
                 // Skip exactly the first three lines
                 while (line_count < 3 && fgets(line, sizeof(line), input_file)) {
                     line_count++;
                 }
 
                 // Process the rest of the file
                 while (fgets(line, sizeof(line), input_file)) {
                     if (strchr(line, '\n')) *strchr(line, '\n') = '\0'; // Remove newline
 
                     // Ensure we're processing only valid data lines (starting with "ANL;")
                     if (strncmp(line, "ANL;", 4) == 0) {
                         printf("Reading line: %s\n", line);  // Debug print
                         parse_line(line, csv_file);
                     }
                 }
 
                 fclose(input_file);
                 fclose(csv_file);
                 printf("CSV file generated successfully.\n");
                 break;
             }
 
             case 2: {
                 /*************************************Batch File Processing*******************************
                  * @description : Processes all .txt files in the specified directory and converts them 
                  *                to CSV format.
                  *******************************************************************************************/
                 process_all_files(directory_path);  // Call the function to process all files in the directory
                 break;
             }
             case 3:  // ✅ New Option: Get Board Result
                 get_board_result();
                 break;
 
             case 4:
                 printf("Exiting the program...\n");
                 break;
             case 5:
                 system("cls");
                 break;
 
             default:
                 printf("Invalid choice. Please try again.\n");
                 break;
         }
 
     } while ((choice != 4 )|| (sizeof(choice) == sizeof(int)));  // Loop until the user chooses to exit
 
     // Wait for the user to press Enter before closing the terminal
     printf("Press Enter to exit...");
     getchar();  // Read the Enter key
     getchar();  // Capture the extra newline character (if any)
 
     return 0;
 }
 




 /*******************************************End Main Program***************************************/
 