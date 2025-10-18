#include <stdio.h>

int main(){
    int  a = 5;
    char b = 'd';
    double c = 56.25;
    short d = 7;

    printf("Size of int: %lu bytes\n", sizeof(a));
    printf("Size of char: %lu bytes\n", sizeof(b));
    printf("Size of double: %lu bytes\n", sizeof(c));
    printf("Size of short: %lu bytes\n", sizeof(d));

    printf("\nAddress of int is: %p\n",(void*)&a);
    printf("\nAddress of char is: %p\n",(void*)&b);
    printf("\nAddress of double is: %p\n",(void*)&c);
    printf("\nAddress of short is: %p\n",(void*)&d);

return 0;
}

