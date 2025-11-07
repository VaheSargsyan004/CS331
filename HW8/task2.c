#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    const char *name ="data.txt";
    int o_f = open(name,O_WRONLY|O_CREAT|O_TRUNC,0644);
    if(o_f == -1){
       perror("Fail to open data.txt");
       exit(1);
    }
    write(o_f,"ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26);
    close(o_f);

    o_f = open(name, O_RDWR);
    if (o_f == -1){
       perror("fail to reopen"); 
       exit(1);
    }

    off_t size = lseek(o_f, 0, SEEK_END);
    printf("Original size: %ld\n", size);
    
    if (ftruncate(o_f, 10) < 0){
       perror("ftruncate");
       exit(1);
    }

    size = lseek(o_f, 0, SEEK_END);
    printf("Truncated size: %ld\n", size);
    
    lseek(o_f, 0, SEEK_SET);
    char buffer[11] = {0};
    read(o_f, buffer, 10);
    printf("Remaining content: %s\n", buffer);

    close(o_f);
    return 0;   
}
