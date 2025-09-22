#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int pid1 = fork();
    if(pid1 ==0){
       printf("Child process started with PID %d\n : \n", getpid());
       exit(0);
    }
    sleep(35);
    printf("Parent with PID %d\n is done",getppid());






}
