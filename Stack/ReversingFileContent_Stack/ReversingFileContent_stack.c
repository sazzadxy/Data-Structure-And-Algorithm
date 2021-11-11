#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char *item;
    int size;
    int top;
}Stack;

void init(Stack *, int);
void dealloc(Stack *);
void push(Stack *, char);
char pop(Stack *);
int getSize(Stack *);
int isOverflow(Stack *);
int isUnderflow(Stack *);

void init(Stack *s, int size)
{
    s->top = -1;
    s->item = (char *) malloc(sizeof(char) * size);
    if(s->item == NULL){
        printf("Unable to allocate memory\n");
        exit(1);
    }
    s->size = size;
}

int isOverflow(Stack *s)
{
    return s->top == s->size - 1;
}

int isUnderflow(Stack *s)
{
    return s->top == -1;
}

int getSize(Stack *s)
{
    return s->size;
}

void push(Stack *s, char ch)
{
    if(isOverflow(s)){
        char *temp = (char *) malloc(sizeof(char) * s->size * 2);

        if(temp == NULL){
            printf("Stack Overflow!\n");
            return;
        }

        for(int i = 0; i < s->size; i++){
            temp[i] = s->item[i];
        }
        free(s->item);
        s->item = temp;
        s->size *= 2;
    }
    s->top++;
    s->item[s->top] = ch;
}

char pop(Stack *s)
{
    if(isUnderflow(s)){
        printf("Stack Underflow!\n");
        return '\0';
    }
    char value;
    value = s->item[s->top];
    s->top--;
    return value;
}

void dealloc(Stack *s)
{
    if(s->item != NULL)
        free(s->item);
    s->size = 0;
    s->top = -1;
}

int reverseIt(char *source, char *dest)
{
    FILE *fps, *fpd;
    const int SIZE = 50;

    fps = fopen(source,"r");
    if(fps == NULL){
        printf("Error opening file %s\n",source);
        return 0;
    }

    fpd = fopen(dest,"w");
    if(fpd == NULL){
        printf("Error opening file %s\n",dest);
        return 0;
    }

    Stack s;
    init(&s,SIZE);

    char buff;
    buff = fgetc(fps);
    while(!feof(fps)){
        push(&s,buff);
        buff = fgetc(fps);
    }

    while(!isUnderflow(&s)){
        fputc(pop(&s),fpd);
    }
    fclose(fps);
    fclose(fpd);
    dealloc(&s);
    return 1;
}

int main()
{
    int f = reverseIt("input.txt","reverse.txt");

    if(f) printf("File copied successfully\n");
    else printf("Error -- copy failed\n");

    return 0;
}


