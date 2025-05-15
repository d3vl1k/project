#ifndef FILESYSTEM_H
#define FILESYSTEM_H

FILE* open_or_create_file(const char* filename);
char* view_file(const char* filename, const char* target_file);
void delete_file(const char* filename, const char* target_file);
void add_new_file(const char* filename, const char* new_file_content);
void modify_file(const char* filename, const char* target_file, const char* new_content);

#endif 
