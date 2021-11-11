#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define SIZE 100

typedef struct {
    double item[SIZE];
    int top;
}OperandStack;

void push(OperandStack *, double);
double pop(OperandStack *);
int isEmpty(OperandStack *);
double operate(double leftOpnd, double rightOpnd, char opr);
double evalPrefix(char preFix[]);

void push(OperandStack *s, double value)
{
    if(s->top == SIZE - 1){
        printf("Stack overflow, terminating program\n");
        exit(1);
    }
    s->item[++s->top] = value;
}

double pop(OperandStack *s)
{
    if(isEmpty(s)){
        printf("Stack underflow, terminating program\n");
        exit(1);
    }
    return s->item[s->top--];
}

int isEmpty(OperandStack *s)
{
    return s->top == -1;
}

double operate(double leftOpnd, double rightOpnd, char opr)
{
    double result = 0.0;

    switch(opr){
        case '+': result = rightOpnd + leftOpnd;
                  break;
        case '-': result = rightOpnd - leftOpnd;
                  break;
        case '*': result = rightOpnd * leftOpnd;
                  break;
        case '/': result = rightOpnd / leftOpnd ;
                  break;
        case '$': result = pow(rightOpnd,leftOpnd);
                  break;
        default: printf("%c is not a valid operator\n", opr);
                 exit(1);
    }
    return result;
}

double evalPrefix(char preFix[])
{
    OperandStack stack;
    stack.top = -1;
    int i = strlen(preFix) - 1;
    while(preFix[i] != 0){
        char token = preFix[i];

        if(token >= '0' && token <= '9'){
            int v = token - '0';
            push(&stack, (double)v);
        }
        else if(token == '+' || token == '-' || token == '*' || token == '/' || token == '$'){
            double op1 = pop(&stack);
            double op2 = pop(&stack);
            double result = operate(op2,op1,token);
            push(&stack,result);
        }
        else{
            printf("Invalid symbol encountered\n");
            exit(1);
        }
        --i;
    }
    return pop(&stack);
}

int main()
{
    char prefix[SIZE];
    printf("Input prefix expression: ");
    scanf("%s", prefix);
    double result = evalPrefix(prefix);
    printf("Result %lf\n",result);
    return 0;
}
