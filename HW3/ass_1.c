#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int pid_1 = fork();
    if(pid_1==0){
       printf("Child process PID is:%d\n",getpid());
       exit(0);
    }else{
       printf("Patent process PID is:%d\n",getpid()); 

    }
    return 0;
}

