#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

struct Node
{
    struct Node *lchild, *rchild;
    short int balance;
    int info;
};

void display(struct Node *p, int level);
void inorder(struct Node *p);

struct Node *rotateLeft(struct Node *p);
struct Node *rotateRight(struct Node *p);

struct Node *getNode(int x);
struct Node *insertNode(struct Node *p, int x);
struct Node *insertionLeftSubtreeCheck(struct Node *p, int *taller);
struct Node *insertionRightSubtreeCheck(struct Node *p, int *taller);
struct Node *insertionLeftBalance(struct Node *p);
struct Node *insertionRightBalance(struct Node *p);

struct Node *deleteNode(struct Node *p, int x);
struct Node *deletionLeftSubtreeCheck(struct Node *p, int *shorter);
struct Node *deletionRightSubtreeCheck(struct Node *p, int *shorter);
struct Node *deleteionLeftBalance(struct Node *p, int *shorter);
struct Node *deleteiontRightBalance(struct Node *p, int *shorter);

int main()
{
    int choice, key;
    struct Node *root = NULL;

    while(1)
    {
        printf("\n\n");
        printf("\t AVL Tree\t\n");
        printf("\t ========\t\n");
        printf("1.Display Tree\n");
        printf("2.Insert a new node\n");
        printf("3.Delete a node\n");
        printf("4.Inorder Traversal\n");
        printf("5.Quit\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            display(root,0);
            break;
        case 2:
            printf("Enter the key to be inserted: \n");
            scanf("%d",&key);
            root = insertNode(root,key);
            break;
        case 3:
            printf("Enter the key to be deleted: \n");
            scanf("%d",&key);
            root = deleteNode(root,key);
            break;
        case 4:
            inorder(root);
            break;
        case 5:
            exit(1);
        default:
            printf("Wrong choice\n");
        }
    }
    return 0;
}

void display(struct Node *p, int level)
{
    if(p == NULL)
        return;

    display(p->rchild,level+1);
    printf("\n");

    for(int i = 0; i < level; i++)
        printf("   ");

    printf("%d",p->info);
    display(p->lchild,level+1);
}

void inorder(struct Node *p)
{
    if(p == NULL)
        return;

    inorder(p->lchild);
    printf("%d ",p->info);
    inorder(p->rchild);
}

struct Node *rotateLeft(struct Node *p)
{
    struct Node *a;
    a = p->rchild;
    p->rchild = a->lchild;
    a->lchild = p;
    return a;
}

struct Node *rotateRight(struct Node *p)
{
    struct Node *a;
    a = p->lchild;
    p->lchild = a->rchild;
    a->rchild = p;
    return a;
}

struct Node *getNode(int x)
{
    struct Node *p = (struct Node*)malloc(sizeof(struct Node));
    p->info = x;
    p->lchild = p->rchild = NULL;
    p->balance = 0;
    return p;
}

struct Node *insertNode(struct Node *p, int x)
{
    static int taller;
    if(p == NULL)
    {
        p = getNode(x);
        taller = TRUE;
    }
    else if(x < p->info)
    {
        p->lchild = insertNode(p->lchild,x);
        if(taller == TRUE)
            p = insertionLeftSubtreeCheck(p,&taller);
    }
    else if(x > p->info)
    {
        p->rchild = insertNode(p->rchild,x);
        if(taller == TRUE)
            p = insertionRightSubtreeCheck(p,&taller);
    }
    else
    {
        printf("%d already present in tree\n",x);
        taller = FALSE;
    }
    return p;
}

struct Node *insertionLeftSubtreeCheck(struct Node *p, int *taller)
{
    switch(p->balance)
    {
    case 0: // Case L_1 : was balanced
        p->balance = 1;  // Now left heavy
        break;
    case -1: // Case L_2 : was right heavy
        p->balance = 0; // Now balanced
        *taller = FALSE;
        break;
    case 1: // Case L_3 : was left heavy
        p = insertionLeftBalance(p); // Left balancing
        *taller = FALSE;
    }
    return p;
}

struct Node *insertionRightSubtreeCheck(struct Node *p, int *taller)
{
    switch(p->balance)
    {
    case 0: // Case R_1 : was balanced
        p->balance = -1; // Now right heavy
        break;
    case 1: // Case R_2 : was left heavy
        p->balance = 0; // Now balanced
        *taller = FALSE;
        break;
    case -1: // Case R_3 : was right heavy
        p = insertionRightBalance(p); // Right balancing
        *taller = FALSE;
    }
    return p;
}

struct Node *insertionLeftBalance(struct Node *p)
{
    struct Node *a,*b;

    a = p->lchild;
    if(a->balance == 1)  // Case L_3A : Insertion in AL, left-left imbalance
    {
        p->balance = 0;
        a->balance = 0;
        p = rotateRight(p);
    }
    else                // Case L_3B : Insertion in AR, left-right imbalance
    {
        b = a->rchild;
        switch(b->balance)
        {
        case 1:         // Case L_3B1 : Insertion in BL
            p->balance = -1;
            a->balance = 0;
            break;
        case -1:  // Case L_3B2 : Insertion in BR
            p->balance = 0;
            a->balance = 1;
            break;
        case 0:   // Case L_3B3 : B is the newly inserted node
            p->balance = 0;
            a->balance = 0;
        }
        b->balance = 0;
        p->lchild = rotateLeft(a);
        p = rotateRight(p);
    }
    return p;
}

struct Node *insertionRightBalance(struct Node *p)
{
    struct Node *a,*b;

    a = p->rchild;
    if(a->balance == -1)  // Case R_3A : Insertion in AR, right-right imbalance
    {
        p->balance = 0;
        a->balance = 0;
        p = rotateLeft(p);
    }
    else  // Case R_3B : Insertion in AL, right-left imbalance
    {
        b = a->lchild;
        switch(b->balance)
        {
        case -1: // Case R_3B1 : Insertion in BR
            p->balance = 1;
            a->balance = 0;
            break;
        case 1: // Case R_3B2 : Insertion in BL
            p->balance = 0;
            a->balance = -1;
            break;
        case 0: // Case R_3B3 : B is the newly inserted node
            p->balance = 0;
            a->balance = 0;
        }
        b->balance = 0;
        p->rchild = rotateRight(a);
        p = rotateLeft(p);
    }
    return p;
}


struct Node *deleteNode(struct Node *p, int x)
{
    struct Node *ch, *s;
    static int shorter;

    if(p == NULL)
    {
        printf("%d not found\n",x);
        shorter = FALSE;
        return p;
    }

    if(x < p->info)  // delete from the left subtree
    {
        p->lchild = deleteNode(p->lchild,x);
        if(shorter == TRUE)
            p = deletionLeftSubtreeCheck(p,&shorter);
    }
    else if(x > p->info)  // delete from the right subtree
    {
        p->rchild = deleteNode(p->rchild,x);
        if(shorter == TRUE)
            p = deletionRightSubtreeCheck(p,&shorter);
    }
    else  // key to be deleted is found
    {
        if(p->lchild != NULL && p->rchild != NULL)  // 2 children
        {
            s = p->rchild;  // finding in-order successor in the right subtree
            while(s->lchild)   // leftmost node of right subtree is in-order successor
            {
                s = s->lchild;
            }

            p->info = s->info; // copy in-order successor data to deleted target node data
            p->rchild = deleteNode(p->rchild,s->info);  // delete in-order successor from tree
            if(shorter == TRUE)
                p = deletionRightSubtreeCheck(p,&shorter);
        }
        else   // 1 child or no child
        {
            if(p->lchild != NULL)  // Only left child
                ch = p->lchild;    // Initialize left child pointer
            else                   // Only right child or no child
                ch = p->rchild;    // Initialize right child pointer
            free(p);               // Delete target node
            p = ch;                // Assign child node to deleted target node
            shorter = TRUE;
        }
    }
    return p;
}

struct Node *deletionLeftSubtreeCheck(struct Node *p, int *shorter)
{
    switch(p->balance)
    {
    case 0:   // Case L_1: was balanced
        p->balance = -1; // now right heavy
        *shorter = FALSE;
        break;
    case 1:   // Case L_2: was left heavy
        p->balance = 0; // now balanced
        break;
    case -1:  // Case L_3: was right heavy
        p = deleteiontRightBalance(p,shorter);  // right balancing
    }
    return p;
}

struct Node *deletionRightSubtreeCheck(struct Node *p, int *shorter)
{
    switch(p->balance)
    {
    case 0:     // Case R_1: was balanced
        p->balance = 1;  // now left heavy
        *shorter = FALSE;
        break;
    case -1:    // Case L_2: was right heavy
        p->balance = 0; // now balanced
        break;
    case 1:   // Case L_3: was right heavy
        p = deleteionLeftBalance(p,shorter); // left balancing
    }
    return p;
}

struct Node *deleteiontRightBalance(struct Node *p, int *shorter)
{
    struct Node *a, *b;

    a = p->rchild;
    if(a->balance == 0)   // Case L_3A
    {
        p->balance = -1;
        a->balance = 1;
        *shorter = FALSE;
        p = rotateLeft(p);
    }
    else if(a->balance == -1)   // Case L_3B
    {
        p->balance = 0;
        a->balance = 0;
        p = rotateLeft(p);
    }
    else                // Case L_3C  right-left imbalance
    {
        b = a->lchild;
        switch(b->balance)
        {
        case 0:  // Case L_3C1
            p->balance = 0;
            a->balance = 0;
            break;
        case 1:  // Case L_3C2
            p->balance = 0;
            a->balance = -1;
            break;
        case -1:  // Case L_3C3
            p->balance = 1;
            a->balance = 0;
        }
        b->balance = 0;
        p->rchild = rotateRight(a);
        p = rotateLeft(p);
    }
    return p;
}

struct Node *deleteionLeftBalance(struct Node *p, int *shorter)
{
    struct Node *a, *b;

    a = p->lchild;
    if(a->balance == 0)    // Case R_3A
    {
        p->balance = 1;
        a->balance = -1;
        *shorter = FALSE;
        p = rotateRight(p);
    }
    else if(a->balance == 1)   // Case R_3B
    {
        p->balance = 0;
        a->balance = 0;
        p = rotateRight(p);
    }
    else            // Case R_3C left-right imbalance
    {
        b = a->rchild;
        switch(b->balance)
        {
        case 0:    // Case R_3C1
            p->balance = 0;
            a->balance = 0;
            break;
        case -1:   // Case R_3C2
            p->balance = 0;
            a->balance = 1;
        case 1:    // Case R_3C3
            p->balance = -1;
            a->balance = 0;
            break;
        }
        b->balance = 0;
        p->lchild = rotateLeft(a);
        p = rotateRight(p);
    }
    return p;
}
