#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Программе передается аргумент — целое число N > 0.
// Необходимо создать N-1 дополнительных процессов таким образом,
// чтобы у каждого процесса было не более одного дочернего процесса.
// Каждый из процессов должен вывести ровно одно число так,
// чтобы на выходе получилась строка: 1 2 3 4 ... N
// Между числами — ровно один пробел, строка завершается символом '\n'.

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    for (int i = 1; i < N; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            continue;
        }

        wait(NULL);

        printf("%d", i);

        if (i < N)
            printf(" ");

        fflush(stdout);
        return 0;
    }

    printf("%d\n", N);
    fflush(stdout);

    // TODO: создайте цепочку из N процессов (каждый не более чем с одним потомком).
    //       Каждый процесс выводит одно число. Порядок вывода должен быть 1 2 3 ... N.

    return 0;
}
