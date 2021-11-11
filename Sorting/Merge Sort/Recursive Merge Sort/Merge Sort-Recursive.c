/*
    - stable sort
    - performance O(n log2 n)
    - not a in-place sort, needs O(n) extra space
*/


#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void mergeSort(int a[], int low, int up);
void merge(int a[], int temp[], int low1, int up1, int low2, int up2);
void copy(int a[], int temp[], int low, int up);

int main()
{
    int n, i, a[MAX];

    printf("Enter the number of elements: ");
    scanf("%d",&n);

    for(i = 0; i < n; i++)
    {
        printf("Enter element %d: ",i+1);
        scanf("%d",&a[i]);
    }

    mergeSort(a,0,n-1);

    printf("Sorted list is: ");
    for(i = 0; i < n; i++)
        printf("%d ",a[i]);
    printf("\n");

    return 0;
}

void mergeSort(int a[], int low, int up)
{
    int temp[MAX];
    int mid;

    if(low == up) // only one element
        return;

    mid = (low+up)/2;

    mergeSort(a,low,mid);  // Sort a[low]...a[mid]
    mergeSort(a,mid+1,up); // Sort a[mid+1]...a[mid]

    // merge a[low]...a[mid] and a[mid+1]...a[mid] to temp[low]...temp[up]
    merge(a,temp,low,mid,mid+1,up);
    // copy temp[low]...temp[up] to a[low]...a[up]
    copy(a,temp,low,up);
}

void merge(int a[], int temp[], int low1, int up1, int low2, int up2)
{
    int i = low1;
    int j = low2;
    int k = low1;

    while((i <= up1) && (j <= up2))
    {
        if(a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while(i <= up1)
        temp[k++] = a[i++];

    while(j <= up2)
        temp[k++] = a[j++];
}

void copy(int a[], int temp[], int low, int up)
{
    int i;
    for(i = low; i <= up; i++)
        a[i] = temp[i];
}
