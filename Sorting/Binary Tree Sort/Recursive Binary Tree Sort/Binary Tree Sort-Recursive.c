/*
    - stable sort
    - performance tree reduces to a chain O(n^2), tree is balanced (n log n)
    - not in-place sort
    - can use threaded binary tree
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct Node
{
    struct Node *lchild;
    int info;
    struct Node *rchild;
};

struct Node *getNode(int x);
struct Node *insertNode(struct Node *p, int x);
struct Node *Destroy(struct Node *ptr);
void inOrder(struct Node *root, int a[], int *i);
void binaryTreeSort(int a[], int n);

int main()
{
    struct Node *root = NULL;
    int a[MAX], n, i;

    printf("Enter the number of elements: ");
    scanf("%d",&n);

    for(i = 0; i < n; i++)
    {
        printf("Enter element %d: ",i+1);
        scanf("%d",&a[i]);
    }

    for(i = 0; i < n; i++)
        root = insertNode(root,a[i]);

    binaryTreeSort(a,n);

    printf("\nSorted list is: \n");
    for(i = 0; i < n; i++)
        printf("%d ",a[i]);
    printf("\n");

    root = Destroy(root);
    return 0;
}

struct Node *getNode(int x)
{
    struct Node *p = (struct Node*)malloc(sizeof(struct Node));
    p->info = x;
    p->lchild = p->rchild = NULL;
    return p;
}

struct Node *insertNode(struct Node *p, int x)
{
    if(p == NULL)
        p = getNode(x);
    else if(x < p->info)
        p->lchild = insertNode(p->lchild,x);
    else
        p->rchild = insertNode(p->rchild,x);

    return p;
}

void inOrder(struct Node *p, int a[], int *i)
{
    if(p != NULL)
    {
        inOrder(p->lchild,a,i);
        a[(*i)++] = p->info;
        inOrder(p->rchild,a,i);
    }
}

void binaryTreeSort(int a[], int n)
{
    struct Node *root = NULL;
    int i;
    //root = insertNode(root,a[0]);

    for(i = 0; i < n; i++)
        root = insertNode(root,a[i]);
    i = 0;
    inOrder(root,a,&i);
}

struct Node *Destroy(struct Node *ptr)
{
    if(ptr != NULL)
    {
        Destroy(ptr->lchild);
        Destroy(ptr->rchild);
        free(ptr);
    }
    return NULL;
}
