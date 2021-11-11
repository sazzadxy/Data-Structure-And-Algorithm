#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

/*
A standard linear search would go through all the elements checking the array
index every time to check when it has reached the last element.
But, the idea is sentinel search is to keep the element to be
searched in the end, and to skip the array index searching.
Considering the worst case in which the search element does not exist in the list of size N then
the Simple Linear Search will take a total of 2N+1 comparisons (N comparisons against
every element in the search list and N+1 comparisons to test against the end of the loop condition).
Sentinel Linear Search : Here the idea is to reduce the number of comparisons required to find an element in a list.
So in the worst case ( if the search element does not exists in the list )
then there will be at most N+2 comparisons ( N comparisons in the while loop and 2 comparisons in the if condition).
Which is better than ( 2N+1 ) comparisons as found in Simple Linear Search.
Take note that both the algorithms have time complexity of O(n).
*/

int searchElement(int arr[], int n, int searchValue)
{
    arr[n] = searchValue;
    int i = 0;
    while(searchValue != arr[i])
        i++;

    if(i < n)
        return i;
    else
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

