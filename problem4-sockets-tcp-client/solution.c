#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Программе передаются два аргумента:
//   argv[1] — IPv4-адрес сервера в десятичной записи (например, "127.0.0.1")
//   argv[2] — номер порта
//
// Программа должна:
//   1. Установить TCP-соединение с указанным сервером.
//   2. В цикле читать со stdin целые знаковые числа в текстовом формате.
//   3. Отправлять каждое число на сервер в бинарном виде (int32, Little Endian).
//   4. Получать от сервера int32 LE в ответ и выводить его в stdout в текстовом виде.
//   5. Если сервер закрыл соединение — завершиться с кодом возврата 0.

static int read_all(int fd, void *buf, size_t n) {
    char *p = buf;

    while (n) {
        ssize_t r = read(fd, p, n);

        if (r <= 0)
            return -1;

        p += r;
        n -= r;
    }

    return 0;
}

static int write_all(int fd, const void *buf, size_t n) {
    const char *p = buf;

    while (n) {
        ssize_t w = write(fd, p, n);

        if (w <= 0)
            return -1;

        p += w;
        n -= w;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <ipv4_addr> <port>\n", argv[0]);
        return 1;
    }
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));

    inet_pton(AF_INET, argv[1], &addr.sin_addr);

    if (connect(sock,
                (struct sockaddr *)&addr,
                sizeof(addr)) < 0)
        return 1;

    int32_t x;

    while (scanf("%d", &x) == 1) {
        if (write_all(sock, &x, sizeof(x)) < 0)
            break;

        int32_t ans;

        if (read_all(sock, &ans, sizeof(ans)) < 0) {
            close(sock);
            return 0;
        }

        printf("%d\n", ans);
    }

    close(sock);

    // TODO: создайте TCP-сокет (AF_INET, SOCK_STREAM),
    //       заполните struct sockaddr_in с помощью inet_aton/inet_pton,
    //       подключитесь через connect,
    //       реализуйте цикл чтения/отправки/приёма/вывода чисел.
    //       Порядок байт — Little Endian (на x86/x86_64 это нативный порядок).

    return 0;
}
