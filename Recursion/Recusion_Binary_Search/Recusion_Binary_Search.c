#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

int recusionBinarySearch(int arr[], int lb, int ub, int target)
{
    if(lb > ub)
        return -1;

    int mid = (lb + ub)/2;

    if(arr[mid] == target)
        return mid;
    else if(arr[mid] < target)
        return recusionBinarySearch(arr,mid+1,ub,target);
    else
        return recusionBinarySearch(arr,lb,mid-1,target);
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

    index = recusionBinarySearch(arr,0,n-1,searchValue);

    if(index == -1)
        printf("%d not found in array\n", searchValue);
    else
        printf("%d found at index %d\n", searchValue, index);

    return 0;
}
