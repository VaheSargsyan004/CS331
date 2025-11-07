#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char path[256];
    int o_f;
    off_t size;
    char a;

    printf("Enter the file path: ");
    if (scanf("%255s", path) != 1) {
        printf("Invalid input\n");
        exit(1);
    }
    
    o_f = open(path, O_RDONLY);
    if (o_f == -1) {
        printf("fail to open the file");
        exit(1);
    }
    
    size = lseek(o_f, 0, SEEK_END);
    if (size == (off_t)-1) {
        printf("lseek fail");
        close(o_f);
        exit(1);
    }

    if (size == 0) {
        printf("\n");
        close(o_f);
        return 0;
    }
    
    for (off_t pos = size - 1; pos >= 0; pos--) {
        if (lseek(o_f, pos, SEEK_SET) == (off_t)-1) {
            perror("lseek");
            close(o_f);
            exit(1);
        }

        if (read(o_f, &a, 1) != 1) {
            printf("read error");
            close(o_f);
            exit(1);
        }

        write(STDOUT_FILENO, &a, 1);
    }

    printf("\n");

    close(o_f);
    return 0;
}
