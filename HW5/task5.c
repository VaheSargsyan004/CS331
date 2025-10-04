#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Enter number of students in class: ");
    scanf("%d", &n);
   
    int *arr;
    arr = (int *)malloc(n * sizeof(int));
    if(arr == NULL){
       printf("Allocation failed!!!! \n");
       return 1;

   }
   printf("Enter %d grades:\n", n);
   for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

   int max = arr[0];
   int min = arr[0];
    for (int i = 1; i < n; i++) {
        if(arr[i] > max){
           max = arr[i];
        }if(arr[i] < min)
            min = arr[i];
    }

 
    printf("Highest grade: %d\n", max);
    printf("Lowest grade: %d\n", min);
    free(arr);

    return 0;



}
