#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

#define INITIAL 0
#define VISITED 1

struct Vertex
{
    char name[50];
    int state;
    int predecessor;
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

void dfs(int v);
void dfsTreeEdges();

int stack[MAX];
int top;

void initializeStack();
int isFull();
int isEmpty();
void push(int x);
int pop();

int main()
{
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

    insertEdge("0","1");
    insertEdge("0","3");
    insertEdge("1","2");
    insertEdge("1","4");
    insertEdge("1","5");
    insertEdge("2","5");
    insertEdge("2","7");
    insertEdge("3","6");
    insertEdge("4","3");
    insertEdge("5","3");
    insertEdge("5","6");
    insertEdge("5","8");
    insertEdge("7","8");
    insertEdge("7","10");
    insertEdge("8","11");
    insertEdge("9","6");
    insertEdge("11","9");

    dfsTreeEdges();
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
        e--;
    }
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
    if(top == MAX-1)
        return 1;
    else
        return 0;
}

void push(int x)
{
    if(isFull())
    {
        printf("Stack Overflow\n");
        return;
    }
    top = top + 1;
    stack[top] = x;
}

int pop()
{
    int x;
    if(isEmpty())
    {
        printf("Stack Underflow\n");
        return -1;
    }
    x = stack[top];
    top = top - 1;
    return x;
}

void dfs(int v)
{
    int i;
    initializeStack();
    push(v);

    while(!isEmpty())
    {
        v = pop();
        if(vertexList[v].state == INITIAL)
        {
            printf("%s ",vertexList[v].name);
            vertexList[v].state = VISITED;
        }

        for(i = n-1; i >= 0; i--)
            if(adj[v][i] != 0 && vertexList[i].state == INITIAL)
            {
                push(i);
                vertexList[i].predecessor = v;  // Set Vertex i as predecessor of Vertex v
            }
    }
    printf("\n");
}

void dfsTreeEdges()
{
    int u, v;
    char s[50];

    printf("Enter starting vertex for Depth First Search: ");
    scanf("%s",s);

    u = getIndex(s);
    if(u == -1)
        return;

    for(v = 0; v < n; v++)
    {
        vertexList[v].state = INITIAL;
        vertexList[v].predecessor = -1;
    }

    dfs(u);

    for(v = 0; v < n; v++)
        if(vertexList[v].state == INITIAL)
            dfs(v);

    printf("Tree Edges: \n");
    for(v = 0; v < n; v++)
    {
        u = vertexList[v].predecessor;
        if(u != -1)
            printf("(%s %s)\n", vertexList[u].name, vertexList[v].name);
    }
}
