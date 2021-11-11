#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

#define M 5 /* order of B tree */
#define MAX (M-1) /* Maximum number of keys allowed in a node */

#if M%2==0
#define CEIL_MDIV2 (M/2)
#else
#define CEIL_MDIV2 ((M+1)/2)
#endif

#define MIN (CEIL_MDIV2-1) /* Minimum number of keys allowed in a node except root */

struct Node{
    int numKeys;
    int key[M];
    struct Node *child[M];
};

void inorder(struct Node *p);
void display(struct Node *p, int blanks);

struct Node *search(int x, struct Node *p);
int searchNode(int x, struct Node *p, int *n);

struct Node *insert(int x, struct Node *p);
int recInsert(int x, struct Node *p, int *ikey, struct Node **ikeyRchild);

void insertByShift(struct Node *p, int n, int ikey, struct Node *ikeyRchild);
void split(struct Node *p, int n, int *ikey, struct Node **ikeyRchild);

struct Node *Delete(int x, struct Node *root);
void recDelete(int x, struct Node *p);
void deleteByShift(struct Node *p, int n);
void restore(struct Node *p, int n);
void borrowLeft(struct Node *p, int n);
void borrowRight(struct Node *p, int n);
void combine(struct Node *p, int m);

int main()
{
    struct Node *root = NULL, *ptr;
    int x, choice;

    while(1){
        printf("\n\n");
        printf("\t B Tree\t\n");
        printf("\t ======\t\n");
        printf("1.Search\n");
        printf("2.Insert\n");
        printf("3.Delete\n");
        printf("4.Display tree\n");
        printf("5.Inorder traversal\n");
        printf("6.Quit\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            printf("Enter the key to be searched: \n");
            scanf("%d",&x);
            if((ptr = search(x,root)) == NULL)
                printf("Key not present in the tree\n");
            else
                printf("Key present in node %p\n",ptr);
            break;
        case 2:
            printf("Enter the key to be inserted: \n");
            scanf("%d",&x);
            root = insert(x,root);
            break;
        case 3:
            printf("Enter the key to be deleted: \n");
            scanf("%d",&x);
            root = Delete(x,root);
            break;
        case 4:
            printf("\n\n");
            display(root,0);
            printf("\n\n");
            break;
        case 5:
            inorder(root);
            printf("\n\n");
            break;
        case 6:
            exit(1);
        default:
            printf("Wrong choice\n");
            break;
        }
    }

    return 0;
}

void inorder(struct Node *p)
{
    int i;
    if(p == NULL)
        return;

    for(i = 0; i < p->numKeys; i++)
    {
        inorder(p->child[i]);
        printf("%d\t",p->key[i+1]);
    }
    inorder(p->child[i]); /* print the right most subtree of node */
}

void display(struct Node *p, int blanks)
{
    int i;
    if(p == NULL)
        return;

    for(i = 1; i <= blanks; i++)
        printf(" ");


    for(i = 1; i <= p->numKeys; i++)
        printf("%d ",p->key[i]);

    printf("\n");

    for(i = 0; i <= p->numKeys; i++)
        display(p->child[i],blanks+10);
}

struct Node *search(int x, struct Node *p)
{
    int n;

    if(p == NULL) /* key x not present in the tree */
        return NULL;
    n = 0;
    if(searchNode(x,p,&n)) /* key x is found in node p */
        return p;

    return search(x,p->child[n]);  /* search in node p->child[n] (N th child) */
}

int searchNode(int x, struct Node *p, int *n)
{
    if(x < p->key[1]){  // if the key is less than the leftmost
        *n = 0;         // child (0th) of the node than the key is not present
        return FALSE;
    }

    *n = p->numKeys;   // if key is not less than leftmost key
    while((x < p->key[*n]) && *n > 1)  // search linearly
        (*n)--;

    if(x == p->key[*n])
        return TRUE;
    else
        return FALSE;
}

struct Node *insert(int x,struct Node *root)
{
    int ikey = 0, taller;
    struct Node *ikeyRchild = NULL, *temp;

    taller = recInsert(x, root, &ikey, &ikeyRchild); // return True if root node has to be split

    if(taller)  /* Height increased by one, new root node has to be created */
    {
        temp = (struct Node*) malloc(sizeof(struct Node));
        temp->numKeys = 1;
        temp->child[0] = root;
        temp->key[1] = ikey;   // ikey is actually median key got after splitting the root node
        temp->child[1] = ikeyRchild;
        root = temp;
    }
    return root;
}

int recInsert(int x, struct Node *p, int *ikey, struct Node **ikeyRchild)
{
    int n, flag;

    if(p == NULL) /* First Base Case : key not found so insert it*/
    {
        *ikey = x;
        *ikeyRchild = NULL;
        return TRUE; // Insertion is not over
    }

    n = 0;
    if(searchNode(x,p,&n))  /* second Base Case : key found */
    {
        printf("Duplicate keys are not allowed\n");
        return FALSE; /* No need to insert the key */
    }

    flag = recInsert(x,p->child[n],ikey,ikeyRchild);  // Insert N th child of node found by searchNode(x,p,&n) function

    if(flag)
    {
        if(p->numKeys < MAX)
        {
            insertByShift(p,n,*ikey,*ikeyRchild);
            return FALSE; /* Insertion over */
        }
        else
        {
            split(p,n,ikey,ikeyRchild);
            return TRUE; /* Insertion not over : Median key yet to be inserted in the parent node */
        }
    }
    return FALSE;
}

void insertByShift(struct Node *p, int n, int ikey, struct Node *ikeyRchild)
{
    int i;
    for(i = p->numKeys; i > n; i--) // shift keys and children adjacent to the right
    {
        p->key[i+1] = p->key[i];
        p->child[i+1] = p->child[i];
    }

    p->key[n+1] = ikey;
    p->child[n+1] = ikeyRchild;
    p->numKeys++;

}

void split(struct Node *p, int n, int *ikey, struct Node **ikeyRchild)
{
    int i, j, medianKey, lastKey, d;
    struct Node *lastChild, *newNode;

    if(n == MAX)      // inserted key is largest
    {
        lastKey = *ikey;
        lastChild = *ikeyRchild;
    }
    else
    {
        lastKey = p->key[MAX];
        lastChild = p->child[MAX];
        for(i = p->numKeys-1; i > n; i--)
        {
            p->key[i+1] = p->key[i];
            p->child[i+1] = p->child[i];
        }
        p->key[i+1] = *ikey;
        p->child[i+1] = *ikeyRchild;
    }

    d = CEIL_MDIV2;
    medianKey = p->key[d];

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->numKeys = M - d;   //  number of keys move to new node

    newNode->child[0] = p->child[d];
    for(i = 1, j = d+1; j <= MAX; i++, j++)  // all keys and children to right of d th  are move to new node
    {
        newNode->key[i] = p->key[j];
        newNode->child[i] = p->child[j];
    }

    newNode->key[i] = lastKey;
    newNode->child[i] = lastChild;

    p->numKeys = d-1;  // number keys in original node

    *ikey = medianKey;  // median key is the new key has to be inserted
    *ikeyRchild = newNode;
}

struct Node *Delete(int x, struct Node *root)
{
    struct Node *temp;

    if(root == NULL)
    {
        printf("Tree is empty\n");
        return NULL;
    }

    recDelete(x,root);

    if(root != NULL && root->numKeys == 0) // Height of tree decreased by 1
    {   // if there is no key left in root node, update root node
        temp = root;
        root = root->child[0];
        free(temp);
    }
    return root;
}

void recDelete(int x, struct Node *p)
{
    int n = 0;
    struct Node *s;

    if(searchNode(x,p,&n)) // key x found in node p
    {
        if(p->child[n] == NULL) // node p is a leaf node
        {
            deleteByShift(p,n);
            return;
        }
        else // node p is a non leaf node, find  successor key
        {
            s = p->child[n]; // point to the right subtree
            while(s->child[0] != NULL) // move down till leaf node arrives
                s = s->child[0];    // leftmost first key of leaf node of right subtree is successor key

            p->key[n] = s->key[1]; // copy successor key to deleted node
            recDelete(s->key[1],p->child[n]);   // successor key deleted from leaf node
        }
    }
    else    // key x not found in node p
    {
        if(p->child[n] == NULL) // if p is a leaf node
        {
            printf("Value %d not present in the tree\n",x);
            return;
        }
        // p is a non-leaf node
        recDelete(x,p->child[n]);
    }
    if(p->child[n]->numKeys < MIN)  // check underflow in p->child[n]
        restore(p,n);
}

void deleteByShift(struct Node *p, int n)
{
    int i;
    for(i = n+1; i <= p->numKeys; i++)
    {
        p->key[i-1] = p->key[i];
        p->child[i-1] = p->child[i];
    }
    p->numKeys--;
}

// Called when p->child[n] becomes underflow
void restore(struct Node *p, int n)
{
    if(n != 0 && p->child[n-1]->numKeys > MIN)
        borrowLeft(p,n);
    else if(n != p->numKeys && p->child[n+1]->numKeys > MIN)
        borrowRight(p,n);
    else
    {
        if(n != 0)  // if there is a left sibling
            combine(p,n);  // combine with left sibling. NB: nodeB is underflow node, nodeA is left sibling (in combine() method)
        else
            combine(p, n+1); // combine with right sibling. NB: nodeA is underflow node, nodeB is right sibling (in combine() method)
    }
}

void borrowLeft(struct Node *p, int n)
{
    int i;
    struct Node *underflowNode = p->child[n];
    struct Node *leftSibling = p->child[n-1]; // left sibling of underflow node

    underflowNode->numKeys++;

    // Shift all the keys and children in underflowNode one position right
    for(i = underflowNode->numKeys; i > 0; i--)
    {
        underflowNode->key[i+1] = underflowNode->key[i];
        underflowNode->child[i+1] = underflowNode->child[i];
    }
    underflowNode->child[1] = underflowNode->child[0];

    // Move the separator key form parent node p to underflowNode
    underflowNode->key[1] = p->key[n];

    // Move the rightmost key of leftSibling to the parent node p
    p->key[n] = leftSibling->key[leftSibling->numKeys];

    // Rightmost child of leftSibling becomes leftmost child of underflowNode
    underflowNode->child[0] = leftSibling->child[leftSibling->numKeys];

    leftSibling->numKeys--;
}

void borrowRight(struct Node *p, int n)
{
    int i;
    struct Node *underflowNode = p->child[n];
    struct Node *rightSibling = p->child[n+1]; // right sibling of underflowNode

    // Move the separator key from parent node p to underflowNode
    underflowNode->numKeys++;
    underflowNode->key[underflowNode->numKeys] = p->key[n+1];

    // Leftmost child of rightSibling becomes the rightmost child of underflowNode
    underflowNode->child[underflowNode->numKeys] = rightSibling->child[0];

    // Move the leftmost key from node rightSibling to parent node p
    p->key[n+1] = rightSibling->key[1];
    rightSibling->numKeys--;

    // Shift all the keys and children of node rightSibling one position left
    rightSibling->child[0] = rightSibling->child[1];
    for(i = 1; i <= rightSibling->numKeys; i++)
    {
        rightSibling->key[i] = rightSibling->key[i+1];
        rightSibling->child[i] = rightSibling->child[i+1];
    }
}

void combine(struct Node*p,int m)
{
    int i;
    struct Node *nodeA = p->child[m-1];
    struct Node *nodeB = p->child[m];

    nodeA->numKeys++;

    // Move the separator key from the parent node p to nodeA
    nodeA->key[nodeA->numKeys] = p->key[m]; // copy end of nodeA

    // Shift the keys and children that are after separator key in node one position to the left
    for(i = m; i< p->numKeys; i++)
    {
        p->key[i] = p->key[i+1];
        p->child[i] = p->child[i+1];
    }
    p->numKeys--;

    // Leftmost child of nodeB becomes rightmost child of nodeA
    nodeA->child[nodeA->numKeys] = nodeB->child[0];

    // Insert all the keys and children of nodeB at the end of nodeA
    for(i = 1; i <= nodeB->numKeys; i++)
    {
        nodeA->numKeys++;
        nodeA->key[nodeA->numKeys] = nodeB->key[i];
        nodeA->child[nodeA->numKeys] = nodeB->child[i];
    }
    free(nodeB);
}
