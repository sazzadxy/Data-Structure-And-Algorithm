
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

char stack[MAX];
int top;

void initializeStack();
int isEmpty();
int isFull();
void push(char);
char pop();

int isValid(char expr[]);
int matchParentheses(char leftPar, char rightPar);

void initializeStack()
{
    top = -1;
}

int isEmpty()
{
    return (top == -1) ? 1 : 0;
}

int isFull()
{
    return (top == MAX-1) ? 1 : 0;
}


void push(char x)
{
    if(isFull())
    {
        printf("Stack Overflow\n");
        return;
    }
    top = top+1;
    stack[top] = x;
}

char pop()
{
    char x;
    if(isEmpty())
    {
        printf("Stack Underflow\n");
        exit(1);
    }
    x = stack[top];
    top = top-1;

    return x;
}

int matchParentheses(char leftPar, char rightPar)
{
    if(leftPar == '[' && rightPar == ']')
        return 1;
    if(leftPar == '{' && rightPar == '}')
        return 1;
    if(leftPar == '(' && rightPar == ')')
        return 1;

    return 0;
}

int isValid(char expr[])
{
    int i;
    char ch;

    for(i = 0; i < strlen(expr); i++)
    {
        if(expr[i] == '[' || expr[i] == '{' || expr[i] == '(')
            push(expr[i]);

        if(expr[i] == ']' || expr[i] == '}' || expr[i] == ')')
        {
            if(isEmpty())
            {
                printf("Right parentheses are more than left parentheses\n");
                return 0;
            }
            else
            {
                ch = pop();
                if(!matchParentheses(ch,expr[i]))
                {
                    printf("Mismatched parentheses are: ");
                    printf("%c and %c\n",ch,expr[i]);
                    return 0;
                }
            }
        }
    }

    if(isEmpty())
    {
        printf("Balanced parentheses\n");
        return 1;
    }
    else
    {
        printf("Left parentheses are more than right parentheses\n");
        return 0;
    }
}

int main()
{
    char expression[MAX];
    char choice = 'y';

    while(choice == 'y')
    {
        printf("Enter an expression with parentheses: ");
        gets(expression);

        initializeStack();

        if(isValid(expression))
            printf("Valid expression\n");
        else
            printf("Invalid expression\n");

        printf("\nWant to check another expression (Enter 'y' for yes): ");
        scanf("%c",&choice);
        fflush(stdin);
    }

    return 0;
}
