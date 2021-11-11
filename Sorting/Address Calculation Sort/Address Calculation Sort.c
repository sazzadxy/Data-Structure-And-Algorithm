/*
    - Not an in-place sort
    - Stable sort
    - Time requirement depends on the  insertion time of elements in list
      if any list becomes very long, the run time becomes close to O(n^2)
      if all the elements are uniformly distributed, the run time is linear O(n)
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct Node
{
    int info;
    struct Node *next;
};

struct Node *start[6];  // Array of pointers of Linked List from 0-5

void addrCalSort(int a[], int n);
void insertInList(int num, int addr);
int hash_fn(int x, int large);

int main()
{
    int i, a[MAX], n;
    printf("Enter the number of elements in the list: ");
    scanf("%d",&n);

    for(i = 0; i < n; i++)
    {
        printf("Enter the elements %d: ", i+1);
        scanf("%d",&a[i]);
    }

    addrCalSort(a,n);

    printf("Sorted list is:\n");
    for(i = 0; i < n; i++)
        printf("%d ",a[i]);
    printf("\n");

    return 0;
}

void addrCalSort(int a[], int n)
{
    int i, j, addr, large = 0;
    struct Node *p;

    for(i = 0; i <= 5; i++)
        start[i] = NULL;

    for(i = 0; i < n; i++)
    {
        if(a[i] > large)
            large = a[i];
    }

    for(i = 0; i < n; i++)
    {
        addr = hash_fn(a[i],large);
        insertInList(a[i],addr);
    }

    // Elements of linked lists are copied to array
    i = 0;
    for(j = 0; j <= 5; j++)
    {
        p = start[j];
        while(p != NULL)
        {
            a[i++] = p->info;
            p = p->next;
        }
    }

}

int hash_fn(int x, int large) // f(x) = (x/L)*5, L is largest of all numbers, f(x) is non decreasing or order preserving functions
{
    int addr;
    float temp;
    temp = (float)x/large;
    addr = temp*5;
    return addr;
}

void insertInList(int num, int addr)
{
    struct Node *temp, *q;

    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->info = num;

    if(start[addr] == NULL || num < start[addr]->info)
    {
        temp->next = start[addr];
        start[addr] = temp;
        return;
    }
    else
    {
        q = start[addr];
        while(q->next != NULL && q->next->info < num)
            q = q->next;
        temp->next = q->next;
        q->next = temp;
    }
}
