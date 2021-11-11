#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

int binarySearchR(int arr[], int lb, int ub, int target)
{
    if(lb > ub)
        return -1;

    int mid = (lb+ub)/2;

    if(target > arr[mid])
        return binarySearchR(arr, mid+1, ub, target);
    else if(target < arr[mid])
        return binarySearchR(arr, lb, mid-1, target);
    else
        return mid;
}

int recursiveBinarySearch(int arr[], int size, int target)
{
    return binarySearchR(arr, 0, size-1, target);
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

    index = recursiveBinarySearch(arr,n,searchValue);

    if(index == -1)
        printf("%d not found in array\n", searchValue);
    else
        printf("%d found at index %d\n", searchValue, index);

    return 0;
}
