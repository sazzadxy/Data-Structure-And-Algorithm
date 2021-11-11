#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void infixToPostfix(char infix[], char postfix[]);
int precedence(char symbol);
int power(int a, int b);
double evaluatePostfix(char postFix[]);

long int stack[MAX];
int top = -1;
void push(long int symbol);
long int pop();
int isEmpty();
int isFull();

int main()
{
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    gets(infix);

    infixToPostfix(infix,postfix);
    printf("Postfix expression is: %s\n",postfix);
    printf("Value of expression: %.2lf\n",evaluatePostfix(postfix));

    return 0;
}

int isEmpty()
{
    return (top == -1) ? 1 : 0;
}

int isFull()
{
    return (top == MAX-1) ? 1 : 0;
}

void push(long int x)
{
    if(isFull())
    {
        printf("Stack Overflow\n");
        return;
    }
    top++;
    stack[top] = x;
}

long int pop()
{
    long int x;
    if(isEmpty())
    {
        printf("Stack Underflow\n");
        exit(1);
    }
    x = stack[top];
    top--;

    return x;
}

int power(int base, int exponent)
{
//    if(exponent == 0) // base == 0
//        return 1;
//    return base * power(base, exponent-1);
    int i, x = 1;
    for(i = exponent; i > 0; i--)
    {
        x *= base;
    }
    return x;
}

int precedence(char symbol)
{
    switch(symbol)
    {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

void infixToPostfix(char infix[], char postfix[])
{
    unsigned int i, p;
    char next, symbol;

    p = 0;
    for(i = 0; i < strlen(infix); i++)
    {
        symbol = infix[i];

        if(symbol == ' ' || symbol == '\t') // ignore blanks and tabs
            continue;

        switch(symbol)
        {
        case '(':
            push(symbol);
            break;
        case ')':
            while((next = pop()) != '(')
                    postfix[p++] = next;
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
            while(!isEmpty() && precedence(stack[top]) >= precedence(symbol))  // if stack top's precedency is greater than scanned  precedency
                postfix[p++] = pop();
            push(symbol);
            break;
        default:   // Operand
            postfix[p++] = symbol;
        }
    }

    while(!isEmpty())
        postfix[p++] = pop();

    postfix[p] = '\0';  // Add '\0' to make postfix a string
}

double evaluatePostfix(char postFix[])
{
    long int x, y;
    long double result;
    unsigned int i;

    for(i = 0; i < strlen(postFix); i++)
    {
        if(postFix[i] <= '9' && postFix[i] >= '0')
            push(postFix[i]-'0');
        else
        {
            x = pop();  // 2nd operand
            y = pop();  // 1st operand
            switch(postFix[i])
            {
            case '+':
                push(y+x); break;
            case '-':
                push(y-x); break;
            case '*':
                push(y*x); break;
            case '/':
                push(y/x); break;
            case '%':
                push(y%x); break;
            case '^':
                push(power(y,x));
            }
        }
    }

    result = pop();
    return result;
}
