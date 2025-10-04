#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Enter number of integers: ");
    scanf("%d", &n);
   
    int *arr;
    arr = (int *)malloc(n * sizeof(int));
    if(arr == NULL){
       printf("Allocation failed!!!! \n");
       return 1;

   }
   printf("Enter %d integers:\n", n);
   int sum = 0;
   for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i]; 
    }

    
    printf("The sum of the integers is equal to  : %d\n", sum);
    free(arr);

    return 0;



}
