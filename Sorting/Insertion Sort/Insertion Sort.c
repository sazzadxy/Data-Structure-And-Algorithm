/*
    - stable sort
    - complexity worst case O(n^2), best case O(n)
    - in-place sort
    - efficient when n is small
    - many movements
    - efficient for lists that are almost sorted
*/

#include <stdlib.h>
#include <stdio.h>
#define MAX 100

int main()
{
    int arr[MAX], i, j, temp, n;

    printf("Enter the number of elements: ");
    scanf("%d",&n);

    for(i = 0; i < n; i++)
    {
        printf("Enter element %d: ",i+1);
        scanf("%d",&arr[i]);
    }

    for(i = 1; i < n; i++)
    {
        temp = arr[i];
        for(j = i-1; j >= 0 && arr[j] > temp; j--)
            arr[j+1] = arr[j];

        arr[j+1] = temp;
    }

    printf("Sorted list is: ");
    for(i = 0; i < n; i++)
        printf("%d ",arr[i]);
    printf("\n");

    return 0;
}
