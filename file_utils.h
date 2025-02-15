// file_utils.h
#ifndef FILE_UTILS_H
#define FILE_UTILS_H

void change_extension_to_csv(char *filename);
void modify_filename(const char *original, char *new_filename, const char *word);
void get_board_result();
void process_all_files(const char *directory_path);
#endif // FILE_UTILS_H