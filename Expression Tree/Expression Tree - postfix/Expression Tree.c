#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Node{
    struct Node *lchild, *rchild;
    char info;
};

int isOperator(char c);
struct Node *getNode(int x);
struct Node *buildTree(char postfix[], struct Node *root);
void prefix(struct Node *root);
void preorder(struct Node *p);
void postfix(struct Node *root);
void postorder(struct Node *p);
void parenthesizedInfix(struct Node *root);
void inorder(struct Node *p);
void display(struct Node *p, int level);
int value(struct Node *root);
int evaluate(struct Node *p);

#define MAX 100
struct Node *stack[MAX];
int top;

void initializeStack();
int isEmpty();
int isFull();
void push(struct Node *x);
struct Node *pop();

int main()
{
    struct Node *root = NULL;
    char postfixArr[] = "54+12*3*-";

    root = buildTree(postfixArr,root);
    display(root,0);
    printf("\n");

    printf("Prefix: ");
    prefix(root);

    printf("Postfix: ");
    postfix(root);

    printf("Infix: ");
    parenthesizedInfix(root);

    printf("Value: %d\n",value(root));
    return 0;
}

int isOperator(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
        return 1;
    else
        return 0;
}

struct Node *getNode(int x)
{
    struct Node *p = (struct Node*) malloc(sizeof(struct Node));
    p->info = x;
    p->lchild = p->rchild = NULL;
    return p;
}

struct Node *buildTree(char postfix[], struct Node *root)
{
    struct Node *t;
    initializeStack();

    for(int i = 0; i < strlen(postfix); i++){    // scan left to right, if encounter an operand allocate a new tree for
        t = getNode(postfix[i]);                 // scanned operands, push this to single node tree on stack
        if(isOperator(postfix[i])){              // if encounter an operator allocate a new tree, operator as root node
            t->rchild = pop();                   // pop 2 trees from the stack 1st popped tree is right child
            t->lchild = pop();                   // and 2nd popped tree is left child
        }
        push(t);                                 // push reference to this new tree on the stack
    }
    root = pop();                                // pop out all as a tree
    return root;
}

void initializeStack()
{
    top = -1;
}

int isEmpty()
{
    if(top == -1)
        return 1;
    else
        return 0;
}

int isFull()
{
    if(top == MAX - 1)
        return 1;
    else
        return 0;
}

void push(struct Node *x)
{
    if(isFull()){
        printf("Stack overflow\n");
        return;
    }

    top = top + 1;
    stack[top] = x;
}

struct Node *pop()
{
    struct Node *x;
    if(isEmpty()){
        printf("Stack underflow\n");
        exit(1);
    }

    x = stack[top];
    top = top - 1;
    return x;
}

void prefix(struct Node *root)
{
    preorder(root);
    printf("\n");
}

void preorder(struct Node *p)
{
    if(p == NULL)
        return;

    printf("%c",p->info);
    preorder(p->lchild);
    preorder(p->rchild);
}

void postfix(struct Node *root)
{
    postorder(root);
    printf("\n");
}

void postorder(struct Node *p)
{
    if(p == NULL)
        return;

    postorder(p->lchild);
    postorder(p->rchild);
    printf("%c",p->info);
}

void parenthesizedInfix(struct Node *root)
{
    inorder(root);
    printf("\n");
}

void inorder(struct Node *p)
{
    if(p == NULL)
        return;

    if(isOperator(p->info))
        printf("(");

    inorder(p->lchild);
    printf("%c",p->info);
    inorder(p->rchild);

    if(isOperator(p->info))
        printf(")");
}

void display(struct Node *p, int level)
{
    if(p == NULL)
        return;

    display(p->rchild,level+1);
    printf("\n");

    for(int i = 0; i < level; i++)
        printf("  ");

    printf("%c",p->info);
    display(p->lchild,level+1);
}

int value(struct Node *root)
{
    if(root == NULL)
        return 0;

    return evaluate(root);
}

int evaluate(struct Node *p)
{
    int leftValue, rightValue;

    if(!isOperator(p->info))
        return p->info - 48; // '0'

    leftValue = evaluate(p->lchild);
    rightValue = evaluate(p->rchild);

    if(p->info == '+')
        return leftValue + rightValue;
    else if(p->info == '-')
        return leftValue - rightValue;
    else if(p->info == '*')
        return leftValue * rightValue;
    else if(p->info == '/')
        return leftValue / rightValue;
    else
        return pow(leftValue,rightValue);
}

