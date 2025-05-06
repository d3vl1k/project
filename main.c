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
