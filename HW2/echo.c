#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
       	if (fork() == 0) {
	   execl("/bin/echo","echo","Hello from the child process",NULL);	    
	 }else{
           wait(NULL);
	   printf("Parent process done\n"); 
	 };
	return 0;
}

