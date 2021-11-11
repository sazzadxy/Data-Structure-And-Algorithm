#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct Node
{
    struct Node *lchild;
    int info;
    struct Node *rchild;
};

struct Node *stack[MAX];
int top;
void initializeStack();
void push(struct Node *item);
struct Node *pop();
int empty();

struct Node *getNode(int x);
struct Node *insertNode(struct Node *root, int x);
void inorder(struct Node *ptr, int a[]);
struct Node *Destroy(struct Node *ptr);

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

    inorder(root,a);

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

struct Node *insertNode(struct Node *root, int x)
{
    struct Node *par, *temp, *p;
    p = root;
    par = NULL;

    while(p != NULL)
    {
        par = p;
        if(x < p->info)
            p = p->lchild;
        else
            p = p->rchild;
    }

    temp = getNode(x);

    if(par == NULL)
        root = temp;
    else if(x < par->info)
        par->lchild = temp;
    else
        par->rchild = temp;

    return root;
}

void inorder(struct Node *root, int a[])
{
    struct Node *p;
    int i;

    if(root == NULL)
    {
        printf("Tree is empty\n");
        return;
    }

    initializeStack();
    p = root;
    i = 0;
    while(1)
    {
        // Move on leftmost path rooted at p, pushing all the nodes in the path
        while(p->lchild != NULL)
        {
            push(p);
            p = p->lchild;
        }

        while(p->rchild == NULL) // visit and pop nodes till a node with right subtree is popped
        {
            a[i++] = p->info; // Visit p
            if(empty())   // If stack becomes empty traversal is finished
                return;
            p = pop();
        }

        // Now p points to node that has a right subtree
        a[i++] = p->info; // Visit p
        p = p->rchild; // Move to right subtree of p
    }
    printf("\n");
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

void initializeStack()
{
    top = -1;
}

void push(struct Node *item)
{
    if(top == (MAX-1))
    {
        printf("Stack Overflow\n");
        return;
    }

    stack[++top] = item;
}

struct Node *pop()
{
    struct  Node *item;
    if(top == -1)
    {
        printf("Stack Overflow\n");
        exit(1);
    }

    item = stack[top--];
    return item;
}

int empty()
{
    if(top == -1)
        return 1;
    else
        return 0;
}
