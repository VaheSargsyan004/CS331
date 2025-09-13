#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
       	if (fork() == 0) {
	   execl("/bin/ls","ls",NULL);	    
	 }else{
           wait(NULL);
	   printf("Parent process done\n"); 
	 };
	return 0;
}

