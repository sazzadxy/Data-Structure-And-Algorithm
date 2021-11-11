
/* BFS Traversal -- Undirected Graph Connected Components */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30
#define INITIAL 0
#define WAITING 1
#define VISITED 2

struct Vertex
{
    char name[50];
    int state;
    int componentNumber;
};

struct Vertex vertexList[MAX];

int adj[MAX][MAX];  // Adjacency Matrix
int n = 0; //  number of vertices in the graph
int e = 0; //  number of edges in the graph

int getIndex(char s[]);
void insertVertex(char s[]);
void deleteVertex(char s[]);
void insertEdge(char s1[], char s2[]);
void deleteEdge(char s1[], char s2[]);

int isConnected();
void bfs(int v, int cN);

int queue[MAX];
int front,rear;
void initialization();
int isFull();
int isEmpty();
void enqueue(int x);
int dequeue();

int main()
{
//    insertVertex("0");
//    insertVertex("1");
//    insertVertex("2");
//    insertVertex("3");
//    insertVertex("4");
//    insertVertex("5");
//    insertVertex("6");
//    insertVertex("7");
//    insertVertex("8");
//    insertVertex("9");
//
//    insertEdge("0","1");
//    insertEdge("0","3");
//    insertEdge("1","2");
//    insertEdge("1","4");
//    insertEdge("1","5");
//    insertEdge("2","3");
//    insertEdge("2","5");
//    insertEdge("3","6");
//    insertEdge("4","5");
//    insertEdge("4","7");
//    insertEdge("5","6");
//    insertEdge("5","8");
//    insertEdge("6","8");
//    insertEdge("6","9");
//    insertEdge("7","8");
//    insertEdge("8","9");

    /* Disconnected Graph */
    insertVertex("0");
    insertVertex("1");
    insertVertex("2");
    insertVertex("3");
    insertVertex("4");
    insertVertex("5");
    insertVertex("6");
    insertVertex("7");
    insertVertex("8");
    insertVertex("9");
    insertVertex("10");
    insertVertex("11");
    insertVertex("12");
    insertVertex("13");
    insertVertex("14");
    insertVertex("15");
    insertVertex("16");

    insertEdge("0","1");
    insertEdge("0","2");
    insertEdge("0","3");
    insertEdge("1","3");
    insertEdge("2","5");
    insertEdge("3","4");
    insertEdge("4","5");
    insertEdge("6","7");
    insertEdge("6","8");
    insertEdge("7","10");
    insertEdge("8","9");
    insertEdge("11","12");
    insertEdge("11","14");
    insertEdge("11","15");
    insertEdge("12","13");
    insertEdge("13","14");
    insertEdge("14","16");

    isConnected();
}

int getIndex(char s[])
{
    int i;

    for(i = 0; i < n; i++)
        if(strcmp(s,vertexList[i].name) == 0)
            return i;

    printf("\nInvalid vertex - %s \n\n",s);
    return -1;
}

void insertVertex(char s[])
{
    int i;

    for(i = 0; i < n; i++)
        if(strcmp(vertexList[i].name,s) == 0)
        {
            printf("Vertex already present\n");
            return;
        }

    strcpy(vertexList[n].name,s);
    n++;
}

void deleteVertex(char s[])
{
    int i, x = getIndex(s), u;

    if(x == -1)
        return;

    u = x;
    while(u < n-1)
    {
        for(i = 0; i < n; i++)   // shift columns to the left
            adj[i][u] = adj[i][u+1];
        for(i = 0; i < n; i++)   // shift rows up
            adj[u][i] = adj[u+1][i];
        u++;
    }

    for(i = x; i < n; i++)
        vertexList[i] = vertexList[i+1];

    n--;
}

// Insert an edge(s1,s2)
void insertEdge(char s1[], char s2[])
{
    int u = getIndex(s1);
    int v = getIndex(s2);

    if(u == -1 || v == -1 || u == v)
    {
        printf("Not a valid edge\n\n");
        return;
    }

    if(adj[u][v] != 0)
        printf("Edge already present\n\n");
    else
    {
        adj[u][v] = 1;
        adj[v][u] = 1;
        e++;
    }
}

void deleteEdge(char s1[], char s2[])
{
    int u = getIndex(s1);
    int v = getIndex(s2);

    if(u == -1 || v == -1)
        return;

    if(adj[u][v] == 0)
        printf("Edge not present\n\n");
    else
    {
        adj[u][v] = 0;
        adj[v][u] = 0;
        e--;
    }
}

void initialization()
{
    front = rear = -1;
}

int isFull()
{
    if(rear == MAX-1)
        return 1;
    else
        return 0;
}

int isEmpty()
{
    if(front == -1 || front == rear+1)
        return 1;
    else
        return 0;
}

void enqueue(int x)
{
    if(isFull())
    {
        printf("Queue Overflow\n");
        return;
    }

    if(front == -1)
        front = 0;

    rear = rear+1;
    queue[rear] = x;
}

int dequeue()
{
    int x;
    if(isEmpty())
    {
        printf("Queue Underflow\n");
        exit(1);
    }

    x = queue[front];
    front = front+1;
    return x;
}

void bfs(int v, int cN)  // Represents only those vertices that are reachable from starting vertex
{
    int i;
    initialization();
    enqueue(v);
    vertexList[v].state = WAITING;

    //printf("Reachable vertices from the starting vertex %s: ", vertexList[v].name);
    while(!isEmpty())
    {
        v = dequeue();
        //printf("%s ", vertexList[v].name);
        vertexList[v].state = VISITED;
        vertexList[v].componentNumber = cN;

        for(i = 0; i < n; i++)
            if(adj[v][i] != 0 && vertexList[i].state == INITIAL)
            {
                enqueue(i);
                vertexList[i].state = WAITING;
            }
    }
    printf("\n");
}

int isConnected()
{
    int cN, v;

    for(v = 0; v < n; v++)
        vertexList[v].state = INITIAL;

    cN = 1;
    bfs(0,cN); // Can be any other vertex

    for(v = 0; v < n; v++)
        if(vertexList[v].state == INITIAL)
        {
            cN++;
            bfs(v,cN);
        }

    if(cN == 1)
    {
        printf("Connected Graph\n");
        return 1;
    }
    else
    {
        printf("Graph is not connected, it has %d components\n", cN);
        for(v = 0; v < n; v++)
        {
            printf("Vertex - Component Group\n");
            printf("%s \t\t%d\n", vertexList[v].name, vertexList[v].componentNumber);
        }

        return 0;
    }
}



