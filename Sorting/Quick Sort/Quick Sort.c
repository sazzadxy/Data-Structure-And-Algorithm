/*
    - unstable sort
    - performance worst case O(n^2), best case O(n log2 n)
    - in-place sort
    - space complexity O(log n)
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void quickSort(int a[], int low, int up);
int partition(int a[], int low, int up);

int main()
{
    int a[MAX], i, n;

    printf("Enter the number of elements: ");
    scanf("%d",&n);

    for(i = 0; i < n; i++)
    {
        printf("Enter element %d: ",i+1);
        scanf("%d",&a[i]);
    }

    quickSort(a,0,n-1);

    printf("Sorted list is: ");
    for(i = 0; i < n; i++)
        printf("%d ",a[i]);
    printf("\n");

    return 0;
}

void quickSort(int a[], int low, int up)
{
    int p; // index for pivot;

    if(low >= up) // zero or one element in sublist
        return;

    p = partition(a,low,up);
    quickSort(a,low,p-1);  // sort left sublist
    quickSort(a,p+1,up);   // sort right sublist
}

int partition(int a[], int low, int up)
{
    int i, j, temp, pivot;
    pivot = a[low];

    i = low+1; // moves from left to right
    j = up;    // moves from right to left

    while(i <= j)
    {
        while(a[i] < pivot && i < up)
            i++;

        while(a[j] > pivot)
            j--;

        if(i < j)  // swap a[i] and a[j]
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
        else       // find proper place for pivot, when i > j
            break;
    }

    // Proper place for pivot is j
    a[low] = a[j];
    a[j] = pivot;

    return j;
}
