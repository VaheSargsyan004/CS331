#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
       	if (fork() == 0) {
	   execl("/bin/grep","grep","Noratus","test.txt", NULL);	    
	 }else{
           wait(NULL);
	   printf("Parent process completed"); 
	 };
	return 0;
}

