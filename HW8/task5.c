#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    const char *name = "sparse.bin";
    int o_f;
    off_t size;

    o_f = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (o_f < 0) {
        write(1, "Cannot create file!\n", 21);
        return 1;
    }

    if (write(o_f, "START", 5) != 5) {
        write(1, "Write error!\n", 13);
        close(o_f);
        return 1;
    }

    if (lseek(o_f, 1024 * 1024, SEEK_CUR) < 0) {
        write(1, "Seek error!\n", 12);
        close(o_f);
        return 1;
    }

    if (write(o_f, "END", 3) != 3) {
        write(1, "Write error!\n", 13);
        close(o_f);
        return 1;
    }

    close(o_f);

    o_f = open(name, O_RDONLY);
    if (o_f < 0) {
        write(1, "Cannot open file!\n", 18);
        return 1;
    }

    size = lseek(o_f, 0, SEEK_END);
    if (size < 0) {
        write(1, "Seek error!\n", 12);
        close(o_f);
        return 1;
    }

    char buf[100];
    int len = snprintf(buf, sizeof(buf), "Apparent file size: %lld bytes\n", (long long)size);
    write(1, buf, len);

    close(o_f);
    return 0;
}
