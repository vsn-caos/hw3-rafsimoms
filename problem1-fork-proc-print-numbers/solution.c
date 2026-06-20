#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,  char *argv[])
{
    int N = atoi(argv[1]);

    for (int i = 1; i <= N; ++i) {
        printf("%d", i);

        if (i == N) {
            printf("\n");
            fflush(stdout);
            return 0;
        }

        printf(" ");
        fflush(stdout);

        pid_t pid = fork();

        if (pid > 0) {
            wait(NULL);
            return 0;
        }
    }

    return 0;
}
