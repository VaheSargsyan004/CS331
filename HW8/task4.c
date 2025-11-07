#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main() {
    const char *name = "log.txt";
    int o_f;
    char input[256];
    char output[300]; 
    ssize_t len;

    o_f = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (o_f < 0) {
        write(1, "Cannot open log file!!\n", 23);
        return 1;
    }

    len = read(0, input, sizeof(input) - 1);
    if (len < 0) {
        write(1, "Read error!!\n", 12);
        close(o_f);
        return 1;
    }

    input[len] = '\0';

    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    int n = snprintf(output, sizeof(output), "PID=%d: %s\n", getpid(), input);

    if (write(o_f, output, n) != n) {
        write(1, "Write error!!\n", 13);
        close(o_f);
        return 1;
    }

    off_t final_offset = lseek(o_f, 0, SEEK_CUR);
    if (final_offset < 0) {
        write(1, "Seek error!!!\n", 12);
        close(o_f);
        return 1;
    }

    char buf[50];
    int l = snprintf(buf, sizeof(buf), "Final file offset: %lld\n", (long long)final_offset);
    write(1, buf, l);

    close(o_f);
    return 0;
}

