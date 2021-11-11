#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void merge(int a1[], int a2[], int temp[], int n1, int n2);

int main()
{
    int a1[MAX], a2[MAX], temp[2*MAX], n1, n2, i;

    printf("Enter the number of elements in first array: ");
    scanf("%d",&n1);

    for(i = 0; i < n1; i++)
    {
        printf("Enter element %d: ",i+1);
        scanf("%d",&a1[i]);
    }

    printf("Enter the number of elements in second array: ");
    scanf("%d",&n2);

    for(i = 0; i < n2; i++)
    {
        printf("Enter element %d: ",i+1);
        scanf("%d",&a2[i]);
    }

    merge(a1,a2,temp,n1,n2);

    printf("Merged array is: ");
    for(i = 0; i < n1+n2; i++)
        printf("%d ",temp[i]);

    printf("\n");

    return 0;
}

void merge(int a1[], int a2[], int temp[], int n1, int n2)
{
    int i = 0, j = 0, k = 0;

    while((i <= n1-1) && (j <= n2-1))
    {
        if(a1[i] < a2[j])
            temp[k++] = a1[i++];
        else
            temp[k++] = a2[j++];
    }

    // copy remaining elements of a1, a2 finished
    while(i <= n1-1)
        temp[k++] = a1[i++];
    // copy remaining elements of a2, a1 finished
    while(j <= n2-1)
        temp[k++] = a2[j++];
}
