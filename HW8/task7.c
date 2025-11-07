#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUF_SIZE 1024

int main() {
    char file1[256], file2[256];
    int o_f1, o_f2;
    ssize_t n1, n2;
    unsigned char buf1[BUF_SIZE], buf2[BUF_SIZE];
    off_t index = 0;

    write(1, "Enter first file path: ", 24);
    ssize_t len1 = read(0, file1, sizeof(file1));
    if (len1 <= 0) {
        write(1, "Error reading input!\n", 21);
        return 1;
    }
    if (file1[len1 - 1] == '\n') file1[len1 - 1] = '\0';

    write(1, "Enter second file path: ", 25);
    ssize_t len2 = read(0, file2, sizeof(file2));
    if (len2 <= 0) {
        write(1, "Error reading input!\n", 21);
        return 1;
    }
    if (file2[len2 - 1] == '\n') file2[len2 - 1] = '\0';

    o_f1 = open(file1, O_RDONLY);
    if (o_f1 < 0) {
        write(1, "Cannot open first file!\n", 25);
        return 1;
    }
    o_f2 = open(file2, O_RDONLY);
    if (o_f2 < 0) {
        write(1, "Cannot open second file!\n", 26);
        close(o_f1);
        return 1;
    }

    while (1) {
        n1 = read(o_f1, buf1, BUF_SIZE);
        n2 = read(o_f2, buf2, BUF_SIZE);

        if (n1 < 0 || n2 < 0) {
            write(1, "Read error!\n", 12);
            close(o_f1);
            close(o_f2);
            return 1;
        }

        if (n1 == 0 && n2 == 0) break;

        ssize_t min_n = n1 < n2 ? n1 : n2;
        for (ssize_t i = 0; i < min_n; i++) {
            if (buf1[i] != buf2[i]) {
                char msg[50];
                int l = snprintf(msg, sizeof(msg), "Files differ at byte %lld\n", (long long)(index + i));
                write(1, msg, l);
                close(o_f1);
                close(o_f2);
                return 1;
            }
        }

        if (n1 != n2) {
            char msg[50];
            int l = snprintf(msg, sizeof(msg), "Files differ at byte %lld\n", (long long)(index + min_n));
            write(1, msg, l);
            close(o_f1);
            close(o_f2);
            return 1;
        }

        index += n1;
    }

    write(1, "Files are identical\n", 20);
    close(o_f1);
    close(o_f2);
    return 0;
}

