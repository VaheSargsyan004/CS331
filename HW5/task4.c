#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char **arr;  

    arr = (char **)malloc(3 * sizeof(char *));
    if (arr == NULL) {
        printf("failed!\n");
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        arr[i] = (char *)malloc(50 * sizeof(char));
        if (arr[i] == NULL) {
            printf("failed!\n");
            return 1;
        }
    }

    printf("Enter 3 strings: ");
    for (int i = 0; i < 3; i++) {
        scanf("%49s", arr[i]);  
    }

    arr = (char **)realloc(arr, 5 * sizeof(char *));
    if (arr == NULL) {
        printf("failed!\n");
        return 1;
    }

    for (int i = 3; i < 5; i++) {
        arr[i] = (char *)malloc(50 * sizeof(char));
        if (arr[i] == NULL) {
            printf("failed!\n");
            return 1;
        }
    }

    printf("Enter 2 more strings: ");
    for (int i = 3; i < 5; i++) {
        scanf("%49s", arr[i]);
    }

    printf("All strings: ");
    for (int i = 0; i < 5; i++) {
        printf("%s ", arr[i]);
    }
    
    for (int i = 0; i < 5; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}

