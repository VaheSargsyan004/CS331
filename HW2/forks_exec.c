#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
	int a = fork();
	    if (a == 0) {
		execl("/bin/ls", "ls",NULL);    
	    }else{
		waitpid(a, NULL, 0) ;   
	        printf("Parent process done");
		
	    };
	 int b = fork();
	    if(b ==0){
		execl("/bin/date","date",NULL);
	    }else{
		waitpid(b, NULL,0);
	
	    };
	  return 0;
}	    

