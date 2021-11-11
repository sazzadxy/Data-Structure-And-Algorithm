#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

int searchElement(int arr[], int n, int searchValue)
{
    for(int i = 0; i < n; i++){
        if(arr[i] == searchValue)
            return i;
    }
    return -1;
}

int main()
{
    int arr[SIZE], n, searchValue, index;

    printf("Enter the number of elements: ");
    scanf("%d",&n);

    printf("Enter the elements: ");
    for(int i = 0; i < n; i++)
        scanf("%d",&arr[i]);


    printf("Enter the value to be search: ");
    scanf("%d",&searchValue);

    index = searchElement(arr,n,searchValue);

    if(index == -1)
        printf("%d not found in array\n", searchValue);
    else
        printf("%d found at index %d\n", searchValue, index);

    return 0;
}

