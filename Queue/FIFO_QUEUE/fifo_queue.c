#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct{
    int item[SIZE];
    int rear, front;
}Queue;

void initQueue(Queue *);
void enqueue(Queue *, int v);
int dequeue(Queue *);

void initQueue(Queue *qp)
{
    qp->front = 0;
    qp->rear = 0;
}

void enqueue(Queue *qp, int v)
{
    if(qp->rear == SIZE){
        printf("Queue Overflow\n");
        return;
    }
    qp->item[qp->rear] = v;
    qp->rear = qp->rear + 1;
}

int dequeue(Queue *qp)
{
    if(qp->rear == qp->front){
        return -9999;
    }
    int v = qp->item[qp->front];
    qp->front = qp->front+1;
    return v;
}

int main()
{
    Queue qp;
    initQueue(&qp);

    enqueue(&qp,1);
    enqueue(&qp,2);
    enqueue(&qp,3);
    enqueue(&qp,4);
    enqueue(&qp,5);

    printf("%d\n",dequeue(&qp));
    printf("%d\n",dequeue(&qp));
    printf("%d\n",dequeue(&qp));
    printf("%d\n",dequeue(&qp));
    printf("%d\n",dequeue(&qp));
    printf("%d\n",dequeue(&qp));

    return 0;
}
