#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void infixToPrefix(char infix[], char prefix[]);
int precedence(char symbol);
int power(int a, int b);
void reverseStr(char str[]);
double evaluatePrefix(char preFix[]);

long int stack[MAX];
int top = -1;
void push(long int symbol);
long int pop();
int isEmpty();
int isFull();

int main()
{
    char infix[MAX], prefix[MAX];

    printf("Enter infix expression: ");
    gets(infix);

    reverseStr(infix);
    infixToPrefix(infix,prefix);
    reverseStr(prefix);

    printf("Prefix expression is: %s\n",prefix);
    printf("Value of expression: %.2lf\n",evaluatePrefix(prefix));

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

void reverseStr(char str[])
{
    char reverse[strlen(str)+1];
    for(int i = strlen(str)-1, j = 0; i >= 0; i--, j++)
        reverse[j] = str[i];
    reverse[strlen(str)] = '\0';

    for(int i = 0; i < strlen(reverse); i++)
        str[i] = reverse[i];
}

int precedence(char symbol)
{
    switch(symbol)
    {
    case ')':
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

void infixToPrefix(char infix[], char prefix[])
{
    unsigned int p;
    int i;
    char next, symbol;

    p = 0;
    for(i = 0; i < strlen(infix); i++)
    {
        symbol = infix[i];

        if(symbol == ' ' || symbol == '\t') // ignore blanks and tabs
            continue;

        switch(symbol)
        {
        case ')':
            push(symbol);
            break;
        case '(':
            while((next = pop()) != ')')
                prefix[p++] = next;
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
            while(!isEmpty() && precedence(stack[top]) >= precedence(symbol))  // if stack top's precedency is greater than scanned  precedency
                prefix[p++] = pop();
            push(symbol);
            break;
        default:   // Operand
            prefix[p++] = symbol;
        }
    }

    while(!isEmpty())
        prefix[p++] = pop();

    prefix[p] = '\0';  // Add '\0' to make postfix a string
}

double evaluatePrefix(char preFix[])
{
    long int x, y;
    double result;
    int i;

    for(i = strlen(preFix)-1 ; i >= 0; i--)
    {
        if(preFix[i] <= '9' && preFix[i] >= '0')
            push(preFix[i]-'0');
        else
        {
            y = pop();  // 1st operand
            x = pop();  // 2nd operand
            switch(preFix[i])
            {
            case '+':
                push(y+x);
                break;
            case '-':
                push(y-x);
                break;
            case '*':
                push(y*x);
                break;
            case '/':
                push(y/x);
                break;
            case '%':
                push(y%x);
                break;
            case '^':
                push(power(y,x));
            }
        }
    }

    result = pop();
    return result;
}


