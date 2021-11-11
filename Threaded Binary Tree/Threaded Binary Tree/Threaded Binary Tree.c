#include <stdio.h>
#include <stdlib.h>

typedef enum {False,True} boolean;

struct Node{
struct Node *left, *right;
boolean leftThread, rightThread;
int info;
};

struct Node *inorderPredecessor(struct Node *p);
struct Node *inorderSuccessor(struct Node *p);
void inorder(struct Node *root);
struct Node *getNode(int x);
struct Node *insertNode(struct Node *root,int x);
struct Node *deleteNode(struct Node *root,int x);

struct Node *inorderPredecessor(struct Node *p)
{
    if(p->leftThread == True)        // if left link of p is thread
        return p = p->left;          // in-order successor of p

    p = p->left;                     // if left thread of p is false, means p has left child
    while(p->rightThread == False)   // go to the right most node of left child
        p = p->right;                // Rightmost node in left subtree is in-order Predecessor
    return p;
}

struct Node *inorderSuccessor(struct Node *p)
{
    if(p->rightThread == True)       // if right link of p is thread
        return p = p->right;         // in-order successor of p

    p = p->right;                    // if right thread of p is false, means p has right child
    while(p->leftThread == False)    // go to the left most node of right child
        p = p->left;                 // Leftmost node in right subtree is in-order Successor
    return p;                        // Leftmost node in right subtree is in-order Successor
}

void inorder(struct Node *root)
{
    struct Node *p;
    if(root == NULL){
        printf("Tree is empty\n");
        return;
    }

    // Find the Leftmost node of the tree
    p = root;
    while(p->leftThread == False)    // move left until get a node with left child
        p = p->left;                 // Leftmost node node with no left child

    while(p != NULL)         // process stop when right node is null
    {
        printf("%d ",p->info);
        if(p->rightThread == True)  // getting in-order successor directly by right link
            p = p->right;
        else
        {
            p = p->right;                       // if right thread of p is false, means p has right child
            while(p->leftThread == False)       // go to the leftmost node of right child
                p = p->left;                    // Leftmost node in right subtree is in-order Successor
        }
    }
    printf("\n\n");
}

//void inorderTraversal(struct Node *root)
//{
//    struct Node *p;
//    if(root == NULL)
//    {
//        printf("Tree is empty");
//        return;
//    }
//
//    p = root;
//    /*Find the leftmost node */
//    while(p->leftThread == False)
//        p = p->left;
//
//    while(p != NULL)
//    {
//        printf("%d ",p->info);
//        p = inorderSuccessor(p);
//    }
//    printf("\n\n");
//}

struct Node *getNode(int x)
{
    struct Node *p = (struct Node*)malloc(sizeof(struct Node));
    p->info = x;
    p->left = p->right = NULL;
    p->leftThread = p->rightThread = True;
    return p;
}

struct Node *insertNode(struct Node *root, int x)
{
    struct Node *temp, *par, *p;
    p = root;
    par = NULL;

    while(p != NULL){
        par = p;

        if(x < p->info){
            if(p->leftThread == False)
                p = p->left;
            else
                break;
        }
        else if(x > p->info){
            if(p->rightThread == False)
                p = p->right;
            else
                break;
        }
        else{
            printf("%d already present in the tree\n",x);
            return root;
        }
    }

    temp = getNode(x);

    if(par == NULL)
        root = temp;
    else if(x < par->info){  //inserted as left child
        temp->left = par->left;
        temp->right = par;
        par->left = temp;
        par->leftThread = False;
    }
    else{                    //inserted as right child
        temp->left = par;
        temp->right = par->right;
        par->right = temp;
        par->rightThread = False;
    }
    return root;
}

struct Node *deleteNode(struct Node *root,int x)
{
    /* p - node to be deleted */
    /* par - parent of that node */
    /* ch - child of that node */
    /* for case C */
    /* s - in-order successor of the node to be deleted */
    /* ps - parent of in-order successor*/

    struct Node *p, *par, *ch, *s, *ps, *pred, *succ;

    p = root;
    par = NULL;

    while(p != NULL){
        if(x == p->info)
            break;

        par = p;
        if(x < p->info){
            if(p->leftThread == False)
                p = p->left;
            else
                break;
        }
        else{
            if(p->rightThread == False)
                p = p->right;
            else
                break;
        }
    }

    if(p == NULL || p->info != x){
        printf("%d not found\n",x);
        return root;
    }

    if(p->leftThread == False && p->rightThread == False){  /* Case C: deleted node has 2 children */
        /* Find in-order successor and its parent */
        ps = p;         // Parent of the in-order successor
        s = p->right;   //  Right subtree of the deleted node

        while(s->leftThread == False){
            ps = s;
            s = s->left;   // Leftmost node in right subtree of the deleted node (in-order successor)
        }
        p->info = s->info;
        p = s;
        par = ps;
    }

    /* Case A: no child */
    if(p->leftThread == True && p->rightThread == True){
        if(par == NULL)
            root = NULL;
        else if(p == par->left){
            par->leftThread = True;
            par->left = p->left;
        }
        else{
            par->rightThread = True;
            par->right = p->right;
        }
        free(p);
        return root;
    }

    /* Case B: 1 child */
    if(p->leftThread == False) /* node to be deleted has left child */
        ch = p->left;
    else
        ch = p->right; /* node to be deleted has right child */

    if(par == NULL)    /* Node to be deleted is root node */
        root = ch;
    else if(p == par->left)  /* deleted node is left child of its parent */
        par->left = ch;
    else                     /* deleted node is right child of its parent */
        par->right = ch;

    pred = inorderPredecessor(p);
    succ = inorderSuccessor(p);

    if(p->leftThread == False)  /* if p has left child, right is thread */
        pred->right = succ;
    else                        /* if p has right child, left is thread */
        succ->left = pred;

    free(p);
    return root;
}

int main()
{
    int choice, x;
    struct Node *root = NULL;

    while(1)
    {
        printf("\tThreaded Binary Tree\t\n");
        printf("\t====================\t\n");
        printf("1.Insert a new node\n");
        printf("2.Delete a node\n");
        printf("3.Inorder Traversal\n");
        printf("4.Exit\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            printf("Enter the key to be inserted: \n");
            scanf("%d",&x);
            root = insertNode(root,x);
            break;
        case 2:
            printf("Enter the key to be deleted: \n");
            scanf("%d",&x);
            root = deleteNode(root,x);
            break;
        case 3:
            inorder(root);
            break;
        case 4:
            exit(1);
        default:
            printf("Wrong choice\n");
        }
    }
    return 0;
}
