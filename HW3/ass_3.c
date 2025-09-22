#include <stdio.h>
#include <stdlib.h>  


void function1() {
    printf("Function 1 caleed \n");
}


void function2() {
    printf("Function 2 called \n");
}

int main() {

    atexit(function1);
    atexit(function2);
    exit(5);
  

    return 0;
}
