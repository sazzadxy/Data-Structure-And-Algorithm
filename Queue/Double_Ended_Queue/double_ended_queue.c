#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

typedef struct{
    int item[SIZE];
    int rear, front;
}Queue;

void initQueue(Queue *);
void ins_at_rear(Queue *, int v);
void ins_at_front(Queue *, int v);
int del_from_rear(Queue *);
int del_from_front(Queue *);
void menu();

void initQueue(Queue *qp)
{
    qp->front = 0;
    qp->rear = -1;
}

void ins_at_rear(Queue *qp, int v)
{
    if(qp->rear == SIZE - 1){
        printf("Unable to insert at rear end\n");
        return;
    }

    qp->rear++; // qp->rear = qp->rear+1;
    qp->item[qp->rear] = v;
}

void ins_at_front(Queue *qp, int v)
{
    if(qp->front == 0){
        printf("Unable to insert at front end\n");
        return;
    }
    qp->front--; // qp->front = qp->front - 1;
    qp->item[qp->front] = v;
}

int del_from_rear(Queue *qp)
{
    if(qp->front > qp->rear){
        //printf("Queue is underflow\n");
        return -9999;
    }
    int v = qp->item[qp->rear];
    qp->rear--; // qp->rear = qp->rear - 1;
    return v;
}

int del_from_front(Queue *qp)
{
    if(qp->front > qp->rear){
        //printf("Queue underflow\n");
        return -9999;
    }
    int v = qp->item[qp->front];
    qp->front++; // qp->front = qp->front + 1;
    return v;
}

void menu(){
  printf("----------FIFO Queue Operations----------\n");
  printf("-----------------------------------------\n");
  printf("1. Insert at rear\n");
  printf("2. Insert at front\n");
  printf("3. Delete from rear\n");
  printf("4. Delete from front\n");
  printf("5. Quit\n");
  printf("-----------------------------------------\n\n");
}

int main()
{
    Queue qp;
    initQueue(&qp);
    menu();

    int quit = 0;
    int value;

    while(!quit){
        int choice;
        printf("Input your option: ");
        scanf("%d",&choice);

        switch(choice){
        case 1:
            printf("Input value to insert at rear: ");
            scanf("%d",&value);
            ins_at_rear(&qp,value);
            break;
        case 2:
            printf("Input value to insert at front: ");
            scanf("%d",&value);
            ins_at_front(&qp,value);
            break;
        case 3:
            value = del_from_rear(&qp);
            if(value == -9999)
                printf("Queue underflow\n");
            else
                printf("Deleted from rear, value %d\n", value);
            break;
        case 4:
            value = del_from_front(&qp);
            if(value == -9999)
                printf("Queue underflow\n");
            else
                printf("Deleted from front, value %d\n", value);
            break;
        case 5:
            quit = 1;
            break;
        default: printf("Invalid choice, valid options are 1 - 5\n");
        }
    }

    return 0;
}



