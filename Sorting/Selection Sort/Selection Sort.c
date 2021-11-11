
/*  
    - not a data sensitive sort
    - less data movement
    - unstable sort
    - performance O(n^2)
    - in-place sort
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int main()
{
    int arr[MAX], i, j, n, temp, minIndex;

    printf("Enter the number of elements: ");
    scanf("%d",&n);

    for(i = 0; i < n; i++)
    {
        printf("Enter element %d: ",i+1);
        scanf("%d",&arr[i]);
    }

    for(i = 0; i < n-1; i++)
    {
        minIndex = i;
        for(j = i+1; j < n; j++)
        {
            if(arr[j] < arr[minIndex])
                minIndex = j;
        }

        if(i != minIndex)
        {
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }

    printf("Sorted list is: ");
    for(i = 0; i < n; i++)
        printf("%d ",arr[i]);
    printf("\n");

    return 0;
}
