#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 4096

int main(){
    char src[256];
    char dest[256];
    printf("Enter source file path: ");
    scanf("%s",src);
    printf("Enter destination file path: ");
    scanf("%s",dest);
    
    int o_src = open(src, O_RDONLY);
    if(o_src == -1){
       perror("fail to open src file");
       exit(1);
    }
    int o_dest = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(o_dest == -1){
       perror("fail to open dest file");
       exit(1);
    }
    char buffer[BUFFER_SIZE];
    ssize_t bytes_rd;
    ssize_t total_bytes = 0;
    bytes_rd = read(o_src, buffer, BUFFER_SIZE);

    while (bytes_rd > 0) {
        ssize_t bytes_wr = write(o_dest, buffer, bytes_rd);
        if (bytes_wr != bytes_rd) {
            perror("Error writing to destination file");
            close(o_src);
            close(o_dest);
            exit(1);
        }
        total_bytes += bytes_wr;
        bytes_rd = read(o_src, buffer, BUFFER_SIZE);

    }

    if (bytes_rd < 0) {
        perror("Error reading source file");
    }

    printf("Total bytes copied: %zd\n", total_bytes);

    close(o_src);
    close(o_dest);

    return 0;

}
