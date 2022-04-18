#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node *left, *right;
}Node;

void menu();
void insert(Node **, int);
void inorder(Node *);
void preorder(Node *);
void postorder(Node *);
void display(Node *,int);
Node *binar_search(Node *,int);

int main()
{
    int choice, quit = 0, key, target;
    Node *root= NULL;
    Node *target_node;
    menu();

//    insert(&root,10);
//    insert(&root,5);
//    insert(&root,2);
//    insert(&root,8);
//    insert(&root,20);
//    insert(&root,15);
//    insert(&root,30);

    while(!quit){
        printf("Enter your option: ");
        scanf("%d",&choice);
        switch(choice){
            case 1: printf("Insert key: ");
                    scanf("%d",&key);
                    insert(&root,key);
                    break;
            case 2: inorder(root);
                    printf("\n");
                    break;
            case 3: preorder(root);
                    printf("\n");
                    break;
            case 4: postorder(root);
                    printf("\n");
                    break;
            case 5: printf("Enter target: ");
                    scanf("%d",&target);
                    target_node = binar_search(root,target);
                    if(target_node == NULL)
                        printf("Target %d doest not exist\n",target);
                    else
                        printf("Target %d exists\n",target);
                    break;
            case 6: menu();
                    break;
            case 7: display(root,0);
                    printf("\n");
                    break;
            case 8: quit = 1;
                    break;
            default: printf("Enter option from 1-7\n");
        }
    }
    return 0;

}

void menu()
{
    printf("*****   BST Operations   *******\n");
    printf("1. Insert\n");
    printf("2. In-order Traversal\n");
    printf("3. Pre-order Traversal\n");
    printf("4. Post_order Traversal\n");
    printf("5. Search\n");
    printf("6. Commands\n");
    printf("7. Display\n");
    printf("8. Quit\n");
    printf("********************************\n");
}

void insert(Node **rtp, int key)
{
    if(*rtp == NULL){
        *rtp = (Node*)malloc(sizeof(Node));

        if(*rtp == NULL){
            printf("Error -- Unable to allocate memory\n");
            exit(1);
        }

        (*rtp)->key = key;
        (*rtp)->left = (*rtp)->right = NULL;
    }
    else if(key > (*rtp)->key)    // use here kl<k0<kr or can use kl>k0>kr
        insert(&((*rtp)->right),key);
    else if(key < (*rtp)->key)
        insert(&((*rtp)->left),key);
    else{
        printf("Duplicate key found -- insertion aborted\n");
        return;
    }
}

void display(Node *rt, int level)
{
    if(rt == NULL)
        return;
    display(rt->left,level+1);
    printf("\n");

    for(int i = 0; i < level; i++)
        printf("  ");
    printf("%d",rt->key);
    display(rt->right,level+1);
}

void inorder(Node *rt)
{
    if(rt != NULL){
        inorder(rt->left);
        printf("%4d",rt->key);
        inorder(rt->right);
    }else
        return;
}

void preorder(Node *rt)
{
    if(rt != NULL){
        printf("%4d",rt->key);
        preorder(rt->left);
        preorder(rt->right);
    }else
        return;
}

void postorder(Node *rt)
{
    if(rt != NULL){
        postorder(rt->left);
        postorder(rt->right);
        printf("%4d",rt->key);
    }else
        return;
}

Node *binar_search(Node *rt, int target)
{
    if(rt == NULL)
        return NULL;

    if(target > rt->key)
        return binar_search(rt->right,target);
    else if(target < rt->key)
        return binar_search(rt->left,target);
    else
        return rt;
}

