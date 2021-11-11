
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

#define INITIAL 0
#define VISITED 1
#define FINISHED 2

struct Vertex
{
    char name[50];
    int state;
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

void dfsTraversal();
void dfs(int v);
void dfsTraversalAll();

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
    insertVertex("12");
    insertVertex("13");
    insertVertex("14");

    insertEdge("0","1");
    insertEdge("0","3");
    insertEdge("1","2");
    insertEdge("1","3");
    insertEdge("1","4");
    insertEdge("3","4");
    insertEdge("5","6");
    insertEdge("5","7");
    insertEdge("5","8");
    insertEdge("7","8");
    insertEdge("9","10");
    insertEdge("9","11");
    insertEdge("9","12");
    insertEdge("9","13");
    insertEdge("10","12");
    insertEdge("11","13");
    insertEdge("11","14");

    dfsTraversal();
    dfsTraversalAll();
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

void dfs(int v)
{
    int i;

    vertexList[v].state = VISITED;
    printf("%s ",vertexList[v].name);

    for(i = 0; i < n; i++)
        if(adj[v][i] && vertexList[i].state == INITIAL)
            dfs(i);

    vertexList[v].state = FINISHED;
}

void dfsTraversal()
{
    int u, v;
    char s[50];

    printf("Enter starting vertex for Depth First Search: ");
    scanf("%s",s);

    u = getIndex(s);

    if(u == -1)
        return;

    for(v = 0; v < n; v++)
        vertexList[v].state = INITIAL;

    dfs(u);
    printf("\n");
}

void dfsTraversalAll()
{
    int u, v;
    char s[50];

    printf("Enter starting vertex for Depth First Search: ");
    scanf("%s",s);

    u = getIndex(s);

    if(u == -1)
        return;

    for(v = 0; v < n; v++)
        vertexList[v].state = INITIAL;

    dfs(u);

    for(v = 0; v < n; v++)
        if(vertexList[v].state == INITIAL)
            dfs(v);

    printf("\n");
}

