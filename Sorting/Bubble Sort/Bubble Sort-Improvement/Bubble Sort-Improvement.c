/*
    - stable sort
    - performance best case O(n), worst and average case O(n^2)
    - in-place sort
*/

#include <stdlib.h>
#include <stdio.h>
#define MAX 100

int main()
{
    int arr[MAX], i, j, x, temp, n, swaps;

    printf("Enter the number of elements: ");
    scanf("%d",&n);

    for(i = 0; i < n; i++)
    {
        printf("Enter element %d: ",i+1);
        scanf("%d",&arr[i]);
    }

    for(x = n-2; x >= 0; x--)
    {
        swaps = 0;
        for(j = 0; j <= x; j++)
        {
            if(arr[j] > arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swaps++;
            }
        }
        if(swaps == 0)
            break;
    }

    printf("Sorted list is: ");
    for(i = 0; i < n; i++)
        printf("%d ",arr[i]);
    printf("\n");

    return 0;
}
