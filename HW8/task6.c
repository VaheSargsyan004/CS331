#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    const char *name = "numbers.txt";
    int o_f;
    char buf[1024];
    ssize_t n;

    o_f = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (o_f < 0) {
        write(1, "Cannot open file!\n", 18);
        return 1;
    }

    for (int i = 1; i <= 10; i++) {
        char line[10];
        int len = snprintf(line, sizeof(line), "%d\n", i);
        if (write(o_f, line, len) != len) {
            write(1, "Write error!\n", 13);
            close(o_f);
            return 1;
        }
    }

    close(o_f);

    o_f = open(name, O_RDWR);
    if (o_f < 0) {
        write(1, "Cannot open file!\n", 18);
        return 1;
    }

    off_t offset = 0;
    int line_count = 0;
    char c;
    while (read(o_f, &c, 1) == 1) {
        if (line_count == 3) break;
        if (c == '\n') line_count++;
        offset++;
    }

    off_t remainder_size = lseek(o_f, 0, SEEK_END) - offset;
    char *remainder = malloc(remainder_size);
    if (!remainder) {
        write(1, "Memory allocation failed!\n", 26);
        close(o_f);
        return 1;
    }

    lseek(o_f, offset, SEEK_SET);
    if (read(o_f, remainder, remainder_size) != remainder_size) {
        write(1, "Read error!\n", 12);
        free(remainder);
        close(o_f);
        return 1;
    }

    lseek(o_f, offset, SEEK_SET);
    const char *new_line = "100\n";
    if (write(o_f, new_line, 4) != 4) {
        write(1, "Write error!\n", 13);
        free(remainder);
        close(o_f);
        return 1;
    }

    if (write(o_f, remainder + strlen("4\n"), remainder_size - strlen("4\n")) != remainder_size - strlen("4\n")) {
        write(1, "Write error!\n", 13);
        free(remainder);
        close(o_f);
        return 1;
    }

    free(remainder);
    close(o_f);

    o_f = open(name, O_RDONLY);
    if (o_f < 0) {
        write(1, "Cannot open file!\n", 18);
        return 1;
    }

    while ((n = read(o_f, buf, sizeof(buf))) > 0) {
        write(1, buf, n);
    }

    close(o_f);
    return 0;
}

