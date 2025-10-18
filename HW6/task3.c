#include<stdio.h>
struct myStruct{
  char a;
  int  b;
  double c;
};

int main(){
   struct myStruct s;
   printf("Size of the struct myStruct:%zu bytes\n", sizeof(s));
   printf("Address of a: %p\n", (void*)&s.a);
   printf("Address of b: %p\n", (void*)&s.b);
   printf("Address of c: %p\n", (void*)&s.c);

return 0;
}
