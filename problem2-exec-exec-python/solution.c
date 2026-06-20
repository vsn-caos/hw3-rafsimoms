#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Программе на стандартный поток ввода задается арифметическое выражение
// в синтаксисе языка python3. Необходимо вычислить это выражение и вывести результат.
// Использовать дополнительные процессы запрещено — нужно использовать exec.

int main(void) {
    // TODO: прочитайте выражение из stdin,
    //       затем вызовите execvp/execlp для запуска python3,
    //       который вычислит и выведет результат.
    //       Подсказка: python3 -c "print(<выражение>)"
    char expr[4096];

    if (!fgets(expr, sizeof(expr), stdin))
        return 0;

    char cmd[8192];
    snprintf(cmd, sizeof(cmd),
             "python3 -c \"print(%s)\"",
             expr);

    system(cmd);

    return 0;
}
