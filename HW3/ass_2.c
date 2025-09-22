#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pid1;
    int pid2;
    int status;
    int status2;
    pid1 = fork();

    if (pid1 == 0) {
        printf("Child_1 PID is: %d\n", getpid());
        exit(7); 
    }
    wait(&status); 

    pid2 = fork();
    if (pid2 == 0) {
        printf("Child_2 PID is: %d\n", getpid());
        exit(10); 
    }
    waitpid(pid2, &status2, 0);

    printf("Parent: Child with  PID %d exited with status %d\n", pid2, WEXITSTATUS(status));
   
    printf("Parent: Child with PID %d exited with status %d\n", pid1 ,WEXITSTATUS(status2));
  


    return 0;
}
