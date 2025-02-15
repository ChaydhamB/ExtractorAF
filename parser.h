// parsing.h
#ifndef PARSING_H
#define PARSING_H

#include <stdio.h>

#define MAX_LINE 1024 
void export_failed_tests(const char *filename);
void parse_line(char *line, FILE *csv_file);
void process_file(const char *input_file_name);
void process_all_files(const char *directory_path);

#endif // PARSING_H


