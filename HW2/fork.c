#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
   int pid1 = fork();
     if(pid1 == 0){
	printf("After first fork we get: Child Pid = %d, PPid = %d\n", getpid(), getppid());
     }else{
	waitpid(pid1,NULL,0);
	printf("After first fork we get: Parent Pid = %d, PPid = %d\n",getpid(),pid1);
     };
    int pid2 = fork();
     if(pid2 == 0) {
	printf("After second fork we get: Child Pid = %d, PPid = %d\n", getpid(), getppid());
     }else{
	waitpid(pid2,NULL,0);     
	printf("After second fork we get: Parent Pid = %d, PPid = %d\n",getpid(),pid2);
     };
    int pid3 = fork();
     if(pid3 == 0){
	printf("After third fork we get: Child Pid = %d, PPid = %d\n", getpid(), getppid());
     }else{     
	waitpid(pid3,NULL,0);     
	printf("After third fork we get: Parent Pid = %d, PPid = %d\n",getpid(),pid3);
     };
     return 0; 
}
