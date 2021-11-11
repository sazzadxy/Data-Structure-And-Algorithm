
/*
    - unstable sort
    - performance worst case complexity O(n^2), best and average case O(n log n)
    - in-place sort
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int main()
{
    int arr[MAX], i, j, h, n, temp;

    printf("Enter the number of elements: ");
    scanf("%d",&n);

    for(i = 0; i < n; i++)
    {
        printf("Enter element %d: ",i+1);
        scanf("%d",&arr[i]);
    }

    printf("Enter maximum increment(odd value): ");
    scanf("%d",&h);

    while(h>=1)
    {
        for(i = h; i < n; i++)
        {
            temp = arr[i];
            for(j = i-h; j >= 0 && arr[j] > temp; j = j-h)
                arr[j+h] = arr[j];

            arr[j+h] = temp;
        }
        h = h-2;
    }

    printf("Sorted list is: ");
    for(i = 0; i < n; i++)
        printf("%d ",arr[i]);
    printf("\n");
}
