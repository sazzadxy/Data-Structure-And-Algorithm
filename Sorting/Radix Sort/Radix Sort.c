/*
    - Number of passes p is equal to number of digits in largest element
      In each pass has n operations
      Run time complexity id O(p*n)
    - If number of digits in largest element is n, run time is O(n^2)
    - If number of digits in largest element is log n, run time is O(n log n)
    - Not an in-place sort
    - Stable sort
*/

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int info;
    struct Node *next;
}*start = NULL;

void radixSort();
int digitsInLargest();
int digit(int number, int k);

int main()
{
    struct Node *temp, *p;
    int i, n, item;

    printf("Enter number of elements in the list: ");
    scanf("%d",&n);

    for(i = 0; i < n; i++)
    {
        printf("Enter element %d: ",i+1);
        scanf("%d",&item);

        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->info = item;
        temp->next = NULL;

        if(start == NULL)
            start = temp;
        else
        {
            p = start;
            while(p->next != NULL)
                p = p->next;
            p->next = temp;
        }
    }

    radixSort();
    printf("Sorted list is: \n");

    p = start;
    while(p != NULL)
    {
        printf("%d ",p->info);
        p = p->next;
    }
    printf("\n");

    return 0;
}

void radixSort()
{
    int i, k, dig, leastSigPos, mostSigPos;
    struct Node *p, *rear[10], *front[10];   // front & rear = array to pinter of 0-9 significant digit order

    leastSigPos = 1;
    mostSigPos = digitsInLargest();

    for(k = leastSigPos; k <= mostSigPos; k++)
    {
        // Making all the queues empty at the beginning of each pass
        for(i = 0; i <= 9; i++)
        {
            rear[i] = NULL;
            front[i] = NULL;
        }

        for(p = start; p != NULL; p = p->next)
        {
            // Find kth digit from right in the number
            dig = digit(p->info,k);

            // Insert the node in Queue(dig)
            if(front[dig] == NULL)
                front[dig] = p;
            else
                rear[dig]->next = p;
            rear[dig] = p;
        }

        // Join all queues to from new linked list
        i = 0;
        while(front[i] == NULL) // Finding first non empty queue
            i++;
        start = front[i];
        while(i <= 8)
        {
            if(rear[i+1] != NULL) // if next queue (i+1)th is not empty
                rear[i]->next = front[i+1];  // join end of i th queue to start of (i+1)th queue
            else
                rear[i+1] = rear[i]; // continue  with rear[i]
            i++;
        }
        rear[9]->next = NULL;
    }
}

// Returns number of digits in the largest element of the list
int digitsInLargest()
{
    struct Node *p = start;
    int large = 0, ndigits = 0;

    // Find largest element
    while(p != NULL)
    {
        if(p->info > large)
            large = p->info;
        p = p->next;
    }

    // Find number of digits in largest element
    while(large != 0)
    {
        ndigits++;
        large/=10;
    }
    return ndigits;
}

// Returns kth digit from right in n
int digit(int n, int k)
{
    int d, i;
    for(i = 1; i <= k; i++)
    {
        d = n % 10;
        n /= 10;
    }
    return d;
}
