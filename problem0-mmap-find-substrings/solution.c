#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

// Программе передаются два аргумента: имя файла и строка для поиска.
// Необходимо найти все вхождения строки в текстовом файле,
// используя отображение на память с помощью системного вызова mmap.
// На стандартный поток вывода вывести список всех позиций (с нуля),
// где встречается искомая строка, по одной на строку.

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <search_string>\n", argv[0]);
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        return 1;
    }
    struct stat st;
    fstat(fd, &st);

    size_t n = st.st_size;
    char *data = mmap(NULL, n, PROT_READ, MAP_PRIVATE, fd, 0);

    size_t m = strlen(argv[2]);

    for (size_t i = 0; i + m <= n; i++) {
        if (memcmp(data + i, argv[2], m) == 0) {
            printf("%zu\n", i);
        }
    }

    munmap(data, n);
    close(fd);


    // TODO: откройте файл, получите его размер через fstat,
    //       отобразите в память через mmap,
    //       найдите все вхождения argv[2] и выведите их позиции

    return 0;
}

