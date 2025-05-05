#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* open_or_create_file(const char* filename) {
    FILE* file = fopen(filename, "a+"); 
    if (!file) {
        perror("Ошибка открытия или создания файла");
        exit(EXIT_FAILURE);
    }
    return 0;
}

char* view_file(const char* filename, const char* target_file) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла для чтения");
        return NULL;
    }

    char* buffer = NULL;
    size_t size = 0;
    size_t found = 0;
    ssize_t read;

    while ((read = getline(&buffer, &size, file)) != -1) {
        if (strstr(buffer, target_file) != NULL) {
            found = 1; 
            break;
        }
    }
    if (found) {
        char* content = malloc(1024); 
        size_t index = 0;
        while ((read = getline(&buffer, &size, file)) != -1 && buffer[0] != '/') {
            strcat(content + index, buffer);
            index += read;
        }
        free(buffer);
        fclose(file);
        return content;
    }

    free(buffer);
    fclose(file);
    return 0; 
    
}
void delete_file(const char* filename, const char* target_file) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла для чтения");
        return;
    }

    FILE* temp_file = fopen("temp.txt", "w"); 
    char* buffer = NULL;
    size_t size = 0;
    ssize_t read;

    int skip = 0;
    while ((read = getline(&buffer, &size, file)) != -1) {
        if (strstr(buffer, target_file) != NULL) {
            skip = 1; 
        }

        if (skip) {
            if (buffer[0] == '/') {
                skip = 0; 
            }
            continue; 
        }

        fputs(buffer, temp_file); 
    }

    fclose(file);
    fclose(temp_file);
    free(buffer);

    remove(filename);
    rename("temp.txt", filename);
}


void add_new_file(const char* filename, const char* new_file_content) {
    FILE *file = fopen(filename, "a"); 
    if (file == NULL) {
        perror("Не удалось открыть файл");
        return;
    }
    fprintf(file, "%s\n", new_file_content); 
    fclose(file); 
}

#include <stdio.h>
#include <stdlib.h>

void modify_file(const char* filename, const char* target_file, const char* new_content) {
    FILE *file = fopen(filename, "r"); 
    if (file == NULL) {
        perror("Не удалось открыть файл");
        return;
    }

    FILE *temp_file = fopen("temp.txt", "w"); 
    if (temp_file == NULL) {
        perror("Не удалось создать временный файл");
        fclose(file);
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strcmp(buffer, target_file) == 0) {
            fprintf(temp_file, "%s\n", new_content); 
        } else {
            fputs(buffer, temp_file); 
        }
    }

    fclose(file);
    fclose(temp_file);
    remove(filename); 
    rename("temp.txt", filename); 
}
