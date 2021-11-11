#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int main()
{
    int arr[SIZE], i, size, num, pos;

    printf("Enter size of the array : ");
    scanf("%d", &size);

    printf("Enter elements in array : ");
    for(i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    printf("Array elements  : ");
    for(i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Enter element to insert : ");
    scanf("%d", &num);
    printf("Enter the element position : ");
    scanf("%d", &pos);

    if(pos > size || pos < 0) // pos == size+1 || pos < 0
        printf("Invalid position! Please enter position between 0 to %d", size);
    else
    {
        for(i = size; i >= pos; i--)
            arr[i] = arr[i-1];

        arr[pos] = num;
        size++;

        printf("Array elements after insertion : ");
        for(i = 0; i < size; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }

    return 0;
}
