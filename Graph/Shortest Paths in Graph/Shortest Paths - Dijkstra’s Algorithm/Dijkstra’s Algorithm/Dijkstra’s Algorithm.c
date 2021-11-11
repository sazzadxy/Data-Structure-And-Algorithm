#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30
#define TEMPORARY 1
#define PERMANENT 2
#define NIL -1
#define INFINITY 99999

struct Vertex
{
    char name[50];
    int predecessor;
    int state;
    int pathLength;
};

struct Vertex vertexList[MAX];

int adj[MAX][MAX];  // Adjacency Matrix
int n = 0; //  number of vertices in the graph
int e = 0; //  number of edges in the graph

int getIndex(char s[]);
void insertVertex(char s[]);
void deleteVertex(char s[]);
void insertEdge(char s1[], char s2[], int wt);
void deleteEdge(char s1[], char s2[]);

void findPaths(char s[]);
void dijkstra(int s);
void findPath(int s, int v);
int tempVertexMinPL();

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

    insertEdge("0","3",2);
    insertEdge("0","1",5);
    insertEdge("0","4",8);
    insertEdge("1","4",2);
    insertEdge("2","1",3);
    insertEdge("2","5",4);
    insertEdge("3","4",7);
    insertEdge("3","6",8);
    insertEdge("4","5",9);
    insertEdge("4","7",4);
    insertEdge("5","1",6);
    insertEdge("6","7",9);
    insertEdge("7","3",5);
    insertEdge("7","5",3);
    insertEdge("7","8",5);
    insertEdge("8","5",3);

    findPaths("0");

    return 0;
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
void insertEdge(char s1[], char s2[], int wt)
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
        adj[u][v] = wt;
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

void dijkstra(int s)
{
    int v, c;

    for(v = 0; v < n; v++)
    {
        vertexList[v].state = TEMPORARY;
        vertexList[v].predecessor = NIL;
        vertexList[v].pathLength = INFINITY;
    }

    vertexList[s].pathLength = 0;

    while(1)
    {
        c = tempVertexMinPL();  // Find temporary vertex with minimum path length

        if(c == NIL)
            return;

        vertexList[c].state = PERMANENT;  // Make temporary vertex permanent

        for(v = 0; v < n; v++)
        {
            if(adj[c][v] != 0 && vertexList[v].state == TEMPORARY)
                if(vertexList[c].pathLength + adj[c][v] < vertexList[v].pathLength)
                {
                    vertexList[v].predecessor = c;
                    vertexList[v].pathLength = vertexList[c].pathLength + adj[c][v];
                }
        }
    }
}

int tempVertexMinPL()
{
    int min = INFINITY;
    int v, x = NIL;

    for(v = 0; v < n; v++)
    {
        if(vertexList[v].state == TEMPORARY && vertexList[v].pathLength < min)
        {
            min = vertexList[v].pathLength;
            x = v;   // Assign vertex with minimum path length
        }
    }
    return x;
}

void findPaths(char source[])
{
    int s, v;

    s = getIndex(source);

    if(s == -1)
        return;

    dijkstra(s);
    printf("Source vertex : %s\n\n",source);

    for(v = 0; v < n; v++)
    {
        printf("Destination vertex : %s \n", vertexList[v].name);
        if(vertexList[v].pathLength == INFINITY)
            printf("There is no path from  %s to %s\n\n",source, vertexList[v].name);
        else
            findPath(s,v);
    }
}

void findPath(int s, int v)
{
    int i, u;
    int count = 0; // number of vertices in shortest path
    int path[MAX]; // Path from source to destination
    int sd = 0;    // shortest distance from source to destination

    while(v != s)
    {
        count++;
        path[count] = v;
        u = vertexList[v].predecessor;
        sd += adj[u][v];
        v = u;
    }
    count++;
    path[count] = s;

    printf("Shortest path is: ");
    for(i = count; i >= 1; i--)
        printf("%s ",vertexList[path[i]].name);
    printf("\nShortest distance is : %d\n\n", sd);
}
