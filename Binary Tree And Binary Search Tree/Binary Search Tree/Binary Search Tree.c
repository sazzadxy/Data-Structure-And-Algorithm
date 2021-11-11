#include <stdlib.h>
#include <stdio.h>

struct node{
    struct node *lchild, *rchild;
    int info;
};

struct node *getNode(int x);
void display(struct node *p, int level);
struct node *search(struct node *p, int x);
struct node *insertNode(struct node *root, int x);
struct node *deleteNode(struct node *root, int x);
struct node *max(struct node *p);
struct node *min(struct node *p);

int main()
{
    struct node *root = NULL, *p;
    int choice, x;

    while(1)
    {
        printf("*****   BST Operations   *******\n");
        printf("1. Display Tree\n");
        printf("2. Search\n");
        printf("3. Insert a new node\n");
        printf("4. Delete a node\n");
        printf("5. Find minimum\n");
        printf("6. Find maximum\n");
        printf("7. Quit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        if(choice == 7)
            break;

        switch(choice){
        case 1: display(root,0);
                printf("\n");
                break;
        case 2: printf("Enter the key to be search: ");
                scanf("%d",&x);
                p = search(root,x);
                if(p == NULL)
                    printf("Key %d not found\n",x);
                else
                    printf("Key %d found\n",x);
                break;
        case 3: printf("Enter the key to be inserted: ");
                scanf("%d",&x);
                root = insertNode(root,x);
                break;
        case 4: printf("Enter the key to be deleted: ");
                scanf("%d",&x);
                root = deleteNode(root,x);
                break;
        case 5: p = min(root);
                if(p == NULL)
                    printf("Tree is empty\n");
                else
                    printf("Minimum key is %d\n",p->info);
                printf("\n");
                break;
        case 6: p = max(root);
                if(p == NULL)
                    printf("tree is empty\n");
                else
                    printf("Maximum key is %d\n",p->info);
                printf("\n");
                break;
        default: printf("Enter option from 1-7\n");
        }

    }

    return 0;
}

void display(struct node *p, int level)
{
    if(p == NULL){
        return;
    }
    display(p->lchild,level+1);
    printf("\n");

    for(int i = 0; i < level; i++)
        printf(" ");
    printf("%d",p->info);
    display(p->rchild,level+1);
}

struct node *search(struct node *p, int x)
{
    if(p == NULL)
        return NULL;

    if(x < p->info)
        return search(p->lchild,x);
    else if(x > p->info)
        return search(p->rchild,x);
    else
        return p;
}

//struct node *search(struct node *p, int x)
//{
//    while(p != NULL){
//        if(x < p->lchild)
//            p = p->lchild;
//        else if(x > p->rchild)
//            p = p->rchild;
//        else
//            return p;
//    }
//    return NULL;
//}

struct node *getNode(int x)
{
    struct node *p = (struct node*)malloc(sizeof(struct node));
    p->info = x;
    p->lchild = p->rchild = NULL;
    return p;
}

struct node *insertNode(struct node *p, int x)
{
    if(p == NULL)
        p = getNode(x);
    else if(x < p->info)
        p->lchild = insertNode(p->lchild,x);
    else if(x > p->info)
        p->rchild = insertNode(p->rchild,x);
    else
        printf("%d already present in the tree\n",x);

    return p;
}

//struct node *insertNode(struct node *root, int x)
//{
//    struct node *p, *par, *temp;
//    p = root;
//    par = NULL;
//    while(p != NULL){
//        par = p;
//        if(x < p->info)
//            p = p->lchild;
//        else if(x > p->info)
//            p = p->rchild;
//        else{
//            printf("%d already present in the tree\n",x);
//            return root;
//        }
//    }
//
//    temp = getNode(x);
//    if(par == NULL)
//        root = temp;
//    else if(x < par->info)    //inserted as left child
//        par->lchild = temp;
//    else			//inserted as right child
//        par->rchild = temp;
//
//    return root;
//}

struct node *max(struct node *p)
{
    if(p == NULL)
        return NULL;
    if(p->rchild == NULL)
        return p;
    return max(p->rchild);
}

struct node *min(struct node *p)
{
    if(p == NULL)
        return NULL;
    if(p->lchild == NULL)
        return NULL;
    return min(p->lchild);
}

//struct node *min(struct node *p)
//{
//    if(p == NULL)
//        return NULL;
//
//    while(p->lchild != NULL){
//        p = p->lchild;
//        return p;
//    }
//}
//
//struct node *max(struct node *p)
//{
//    if(p == NULL)
//        return NULL;
//
//    while(p->rchild != NULL){
//        p = p->rchild;
//        return p;
//    }
//}

struct node *deleteNode(struct node *p, int x)
{
    struct node *ch, *s;
    if(p == NULL){
        printf("%d not found\n",x);
        return p;
    }

    if(x < p->info)      // delete from the left subtree
        p->lchild = deleteNode(p->lchild,x);
    else if(x > p->info) // delete from the right subtree
        p->rchild = deleteNode(p->rchild,x);
    else{
        // key to be deleted is found
        if(p->lchild != NULL && p->rchild != NULL) // deleted node has 2 children
            {
                s = p->rchild;   // finding in-order successor in the right subtree
                while(s->lchild) // leftmost node of right subtree is in-order successor
                    s = s->lchild;

                p->info = s->info; // copy in-order successor data to deleted target node data
                p->rchild = deleteNode(p->rchild,s->info); // by Case A or B recusive call to delete right child node and inorder successor
            }
        else  // deleted node has 1 child or no child
        {
            if(p->lchild != NULL) // Only left child
                ch = p->lchild;   // Initialize left child pointer
            else                  // Only right child or no child
                ch = p->rchild;   // Initialize right child pointer

            free(p);              // Delete target node
            p = ch;               // Assign child node to deleted node
        }
    }
    return p;
}

//struct node *deleteNode(struct node *root, int x)
//{
//    /* p - node to be deleted */
//    /* par - parent of that node */
//    /* ch - child of that node */
//    /* for case C */
//    /* s - in-order successor of the node to be deleted */
//    /* ps - parent of in-order successor*/
//
//    struct node *p, *par, *ch, s, *ps;
//
//    p = root;
//    par = NULL;
//    while(p != NULL){
//        if(x == p->info)
//            break;
//	  par = p;
//        if(x < p->info)
//            p = p->lchild;
//        else
//            p = p->rchild;
//    }
//    if(p == NULL){
//        printf("%d not found\n",x);
//        return root;
//    }
//
//    /* Case C: deleted node has 2 children */
//    /* Find in-order successor and its parent */
//    if(p->lchild != NULL && p->rchild != NULL){
//        ps = p;            // Parent of the in-order successor
//        s = p->rchild;     //  Right subtree of the deleted node
//        while(s->lchild != NULL){   // keep on moving until doesn't have a left child
//            ps = s;         
//            s = s->lchild;  // Leftmost node in right subtree of the deleted node (inorder successor)
//        }
//        p->info = s->info;  // copy inorder successor data to deleted node data
//        p = s;              // Make inorder successor as deleted node. Delete by Case A or B
//        par = ps;           // Successor parent assign to parent node
//    }
//
//    /* Case B and Case A: 1 or no child */
//    /* Case B: 1 child */
//    if(p->lchild != NULL)  /* node to be deleted has left child */
//        ch = p->lchild; 	
//    else	             /* node to be deleted has right child*/
//        ch = p->rchild; 
//
//    if(par == NULL)     /* Node to be deleted is root node */
//        root = ch;      /* deleted node's child becomes root node */
//    /* Case A: No child, so left and right child both are null */
//    else if(p == par->lchild) /* deleted node is left child of its parent */
//        par->lchild = ch;     /* child of deleted node becomes the child of deleted node's parent */
//    else                      /* deleted node is right child of its parent */
//        par->rchild = ch;     /* child of deleted node becomes the child of deleted node's parent */
//    free(p);
//    return root;
//}


