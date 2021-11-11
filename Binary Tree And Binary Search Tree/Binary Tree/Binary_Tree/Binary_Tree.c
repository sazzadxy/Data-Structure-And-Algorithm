#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

struct node{
    struct node *leftChild, *rightChild;
    char info;
};

struct node *getnode(char x);
void display(struct node *p, int level);
void preOrder(struct node *p);
void postOrder(struct node *p);
void inOrder(struct node *p);
void levelOrder(struct node *p);
int height(struct node *p);

struct node *queue[SIZE];
int front, rear = -1;
void insertQueue(struct node *item);
struct node *deletequeue();
int queueEmpty();

int main()
{
    struct node *root = NULL;
    root = getnode('A');
    root->leftChild = getnode('B');
    root->rightChild = getnode('C');
    root->rightChild = getnode('E');
    root->leftChild->rightChild = getnode('F');
    root->leftChild->leftChild = getnode('G');
    root->rightChild->leftChild = getnode('H');

    display(root,0);
    printf("\n\n");

    printf("Preorder: ");
    preOrder(root);
    printf("\n\n");

    printf("Postorder: ");
    postOrder(root);
    printf("\n\n");

    printf("Inorder: ");
    inOrder(root);
    printf("\n\n");

    printf("Height of tree is %d\n",height(root));
    return 0;
}

struct node *getnode(char x)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->info = x;
    p->leftChild = p->rightChild = NULL;
    return p;
}

void display(struct node *p, int level)
{
    if(p == NULL)
        return;
    display(p->leftChild,level+1);
    printf("\n");

    for(int i = 0; i < level; i++)
        printf("  ");
    printf("%c",p->info);

    display(p->rightChild,level+1);
}

int height(struct node *p)
{
    int hR, hL;
    if(p == NULL)
        return 0;
    hL = height(p->leftChild);
    hR = height(p->rightChild);

    if(hL > hR)
        return hL + 1;
    else
        return hR + 1;
}

void preOrder(struct node *p)
{
    if(p == NULL)
        return;

    printf("%c ",p->info);
    preOrder(p->leftChild);
    preOrder(p->rightChild);
}

void postOrder(struct node *p)
{
    if(p == NULL)
        return;

    postOrder(p->leftChild);
    postOrder(p->rightChild);
    printf("%c ",p->info);
}

void inOrder(struct node *p)
{
    if(p == NULL)
        return;

    inOrder(p->leftChild);
    printf("%c ",p->info);
    inOrder(p->rightChild);
}

void levelOrder(struct node *p)
{
    if(p == NULL){
        printf("Tree is empty\n");
        return;
    }

    insertQueue(p);

    while(!queueEmpty()){
        p = deletequeue();
        printf("%c ",p->info);

        if(p->leftChild != NULL)
            insertQueue(p->leftChild);
        if(p->rightChild != NULL)
            insertQueue(p->rightChild);
    }
}

void insertQueue(struct node *item)
{
    if(rear == SIZE - 1){
        printf("Queue Overflow\n");
        return;
    }

    if(front == -1)
        front = 0;
    rear = rear + 1;
    queue[rear] = item;
}

struct node *deletequeue()
{
    struct node *item;
    if(front == rear || front == rear+1){
        printf("Queue Underflow\n");
        return 0;
    }
    item = queue[front];
    front = front+1;
    return item;
}

int queueEmpty()
{
    if(front == -1 || front == rear+1)
        return 1;
    else
        return 0;
}
