#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Enter number of integers: ");
    scanf("%d", &n);

    int *arr;
    arr = (int *)calloc(n,sizeof(int));
    if(arr == NULL){
       printf("Allocation failed!!!! \n");
       return 1;

    }
    printf("Zeros: \n");
    for(int i=0; i<n;i++){
        printf("%d ",arr[i]);
    } 
    printf("\n");
 
   printf("Enter %d integers:\n", n);
   int sum = 0;
   for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }
    int average = sum /n;
    for(int i =0;i<n;i++){
        printf("%d ", arr[i]);

    }
    printf("\n");

    printf("The avearge of the array is equal to  : %d\n", average);
    free(arr);

    return 0;



}
