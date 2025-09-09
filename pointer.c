#include <stdio.h>
#include <string.h>

//Exercise 1{
void assignment1(){
    printf("----------------Exercise_1------------------\n");
    int a =10;                                  //initializing an integer with value of 5
    int *p1 =&a;                                //assigning integer's address to the pointer
    printf("Address of num: %p\n", &a);         // Printing the address of number 
    printf("Address of num: %p\n", p1);  // Printing the address stored in pointer
}

void assignment2(){
    printf("----------------Exercise_2----------------\n");
    int arr[5] = {1,2,3,4,7}; //initializing an array 
    int *ptr; //initializing a pointer

    ptr = &arr[0];  // Pointing to the first element of the array

    for (int i = 0; i < 5; i++) {
        printf("Value of arr[%d]: %d\n", i, *(ptr + i));  // Accessing array elements using pointer
    }

    for (int i = 0; i < 5; i++) {
        *(ptr + i)=i*2;  // Modifying array elements using pointer
        printf("%d -> Value of arr: %d; Value with pointer: %d\n", i, arr[i], *(ptr + i));  // Accessing array elements using pointer

    }
}

    void swap(int *a, int *b){ // creating a swap function giving it pointers as an argument
       int temp = *a;
       *a = *b;
       *b = temp;
    }

    void assignment3(){
        printf("----------------Exercise_3----------------\n");
        int a1 = 10; //initializing an integer
        int a2 = 23; //initializing an integer
        printf("Value of a1 = %d\nValue of a2 = %d\n", a1, a2 );//printing the value of integers before calling swap function
        swap(&a1,&a2);
        printf("Value of a1 = %d\nValue of a2 = %d\n", a1, a2 ); //printing the value of integers after calling swap function

    }

    void assignment4(){
        printf("----------------Exercise_4----------------\n");
        int c; // declaring an integer
        int *pnt = &c; // assiging an address of integer to the pointer
        int **pnt1 = &pnt; // assiging an address of the pointer to another pointer
        **pnt1 = 15; // initilaizing double pointer
        printf("Value of an integer with pointer %d\nValue of an integer with double pointer %d\n", *pnt, **pnt1); //printing the value of the pointer and the double pointer
    }

    void assignment5(){
        printf("----------------Exercise_5----------------\n");
        char str[] = "Hello"; //initializing a string array
        char *j = &str[0]; // declare a pointer to the first character of the string
        int count =0; //giving count a value of 0
        for(int i=0;i<5;i++){ //looping over the string using a pointer property 
            printf("%c", *(j+i));
            
        }
        printf("\n");
        while (*(j +count) !='\0') { // we are incrementing the pointer using its value and compare it with '\0', so it will end up working at the end of the array
        count++; //incrementing the count
        }
        printf("The number of the characterS in the string is --> %d", count); // printing the count
    }



int main(){
    assignment1();
    assignment2();
    assignment3();
    assignment4();
    assignment5();

}