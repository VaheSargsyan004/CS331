#include<stdio.h>

struct myStruct1{
 char a;
 int b;
 double c;
};

struct myStruct2{
  int b;
  double c;
  char a;
};


int main(){
 struct myStruct1 s1;
 struct myStruct2 s2;
 printf("Size of struct myStruct1: %lu bytes\n", sizeof(s1));
 printf("Address of a: %p\n", (void*)&s1.a);
 printf("Address of b: %p\n", (void*)&s1.b);
 printf("Address of c: %p\n", (void*)&s1.c);
 printf("Size of struct myStruct2: %lu bytes\n", sizeof(s2));
 printf("Address of b: %p\n", (void*)&s2.b);
 printf("Address of c: %p\n", (void*)&s2.c);
 printf("Address of a: %p\n", (void*)&s2.a);



return 0;
}
