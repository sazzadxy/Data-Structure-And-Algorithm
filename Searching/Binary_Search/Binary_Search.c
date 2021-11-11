#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

int binarySearch(int arr[], int size, int target)
{
    int lb = 0, up = size-1;

    while(lb <= up){
        int mid = (lb+up)/2;

        if(target > arr[mid])
            lb = mid + 1;
        else if(target < arr[mid])
            up = mid - 1;
        else
            return mid;
    }
    return -1;
}

int main()
{
    int arr[SIZE], n, searchValue, index;

    printf("Enter the number of elements: ");
    scanf("%d",&n);

    printf("Enter the elements (in sorted order): ");
    for(int i = 0; i < n; i++)
        scanf("%d",&arr[i]);


    printf("Enter the value to be search: ");
    scanf("%d",&searchValue);

    index = binarySearch(arr,n,searchValue);

    if(index == -1)
        printf("%d not found in array\n", searchValue);
    else
        printf("%d found at index %d\n", searchValue, index);

    return 0;
}

