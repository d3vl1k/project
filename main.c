#include <stdio.h>
#include <stdlib.h>
#include "filesystem.h"

int main() {
    const char* filename = "demo.txt";

    // 1. Создаём файл и записываем начальный контент
    add_new_file(filename, "Это начальное содержимое.\n");

    // 2. Открываем или создаём файл (по факту просто проверка)
    FILE* f = open_or_create_file(filename);
    if (f) {
        printf("Файл успешно открыт или создан: %s\n", filename);
        fclose(f);
    } else {
        printf("Не удалось открыть файл.\n");
    }

    // 3. Просматриваем содержимое
    char* content = view_file(filename, filename);
    if (content) {
        printf("Содержимое файла до изменений:\n%s\n", content);
        free(content);
    } else {
        printf("Не удалось прочитать файл.\n");
    }

    // 4. Модифицируем содержимое
    modify_file(filename, filename, "Это обновлённое содержимое.\n");

    // 5. Просматриваем снова
    content = view_file(filename, filename);
    if (content) {
        printf("Содержимое файла после изменений:\n%s\n", content);
        free(content);
    }

    // 6. Удаляем файл
    delete_file(filename, filename);
    printf("Файл '%s' удалён.\n", filename);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LEN 256

void создать_файл(const char *путь) {
    FILE *файл = fopen(путь, "w");
    if (файл == NULL) {
        printf("Не удалось создать файл: %s\n", путь);
        return;
    }
    fclose(файл);
    printf("Файл создан: %s\n", путь);
}

void удалить_файл(const char *путь) {
    if (remove(путь) == 0) {
        printf("Файл удалён: %s\n", путь);
    } else {
        printf("Не удалось удалить файл: %s\n", путь);
    }
}

void изменить_файл(const char *путь, const char *текст) {
    FILE *файл = fopen(путь, "a");
    if (файл == NULL) {
        printf("Не удалось открыть файл: %s\n", путь);
        return;
    }
    fprintf(файл, "%s\n", текст);
    fclose(файл);
    printf("Файл изменён: %s\n", путь);
}

void посмотреть_файл(const char *путь) {
    FILE *файл = fopen(путь, "r");
    if (файл == NULL) {
        printf("Не удалось открыть файл: %s\n", путь);
        return;
    }
    char строка[1024];
    while (fgets(строка, sizeof(строка), файл)) {
        printf("%s", строка);
    }
    fclose(файл);
}

int main() {
    char ввод[MAX_COMMAND_LEN];

    while (1) {
        printf("> ");
        if (!fgets(ввод, sizeof(ввод), stdin)) break;

        // Удаляем символ новой строки
        ввод[strcspn(ввод, "\n")] = 0;

        char *команда = strtok(ввод, " ");
        if (!команда) continue;

        if (strcmp(команда, "создать") == 0) {
            char *путь = strtok(NULL, " ");
            if (путь) создать_файл(путь);
        } else if (strcmp(команда, "удалить") == 0) {
            char *путь = strtok(NULL, " ");
            if (путь) удалить_файл(путь);
        } else if (strcmp(команда, "изменить") == 0) {
            char *путь = strtok(NULL, " ");
            char *текст = strtok(NULL, "");
            if (путь && текст) изменить_файл(путь, текст);
        } else if (strcmp(команда, "посмотреть") == 0) {
            char *путь = strtok(NULL, " ");
            if (путь) посмотреть_файл(путь);
        } else {
            printf("Неизвестная команда: %s\n", команда);
        }
    }

    return 0;
}
