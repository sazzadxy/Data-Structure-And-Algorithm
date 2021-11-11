#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 100

typedef struct{
    char item[SIZE];
    int top;
}OperatorStack;

void opr_push(OperatorStack *, char);
char opr_pop(OperatorStack *);
int isEmpty(OperatorStack *);
int prec(char left, char right);
void convert(char infix[], char postfix[]);

int isEmpty(OperatorStack *s)
{
    return s->top == -1;
}

void push(OperatorStack *s, char v)
{
    if(s->top == SIZE - 1){
        printf("Stack overflow, terminating program\n");
        exit(1);
    }
    s->item[++s->top] = v;
}

char pop(OperatorStack *s)
{
    if(isEmpty(s)){
        printf("Stack underflow, terminating program\n");
        exit(1);
    }
    return s->item[s->top--];
}

/*
    prcd(op, '(') = FALSE
    prcd('(', op) = FALSE
    prcd(op, ')') = TRUE, except op = '('
    prcd('(',')') = FALSE, instead of push will pop
*/
int prcd(char left, char right)
{
    if(left == '(' || right == '(')
        return 0;
    if(right == ')')
        return 1;

    if(left == '*' || left == '/'){
        if(right == '*' || right == '/' || right == '+' || right == '-')
            return 1;
        else
            return 0;
    }

    if(left == '+' || left == '-'){
        if(right == '+' || right == '-')
            return 1;
        else
            return 0;
    }

    if(left == '$')
        return 1;
    else
        return 0;
}

void convert(char infix[], char postfix[])
{
    OperatorStack stack;
    stack.top = -1;
    int i, j = 0;

    while(infix[i] != '\0'){
        char token = infix[i];
            // if token is a operand
            if(token >= '0' && token <= '9'){
                postfix[j++] = token;
            }
            // if token is a operator
            else if(token == '+' || token == '-' || token == '*' || token == '/' || token == '$' || token == '(' || token == ')'){
                while(stack.top != -1 && prcd(stack.item[stack.top], token)){
                    char top_opr = pop(&stack);
                    postfix[j++] = top_opr;
                }
                if(token == ')')
                    pop(&stack);
                else
                    push(&stack,token);
            }
            else{
                printf("invalid symbol %c encountered \n", token);
                exit(1);
            }
        i++;
    } // end of the outer while

    while(stack.top != -1){
        char top_opr = pop(&stack);
        postfix[j++] = top_opr;
    }
    postfix[j] = '\0';
}

int main()
{
    char infix[SIZE];
    char postfix[SIZE];

    printf("Input infix: ");
    scanf("%s",infix);

    convert(infix,postfix);

    printf("The equivalent postfix %s\n", postfix);
    return 0;
}
