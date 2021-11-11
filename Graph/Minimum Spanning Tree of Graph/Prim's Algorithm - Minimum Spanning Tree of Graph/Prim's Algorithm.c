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
    int status;
    int predecessor;
    int length;
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

void prims();
int tempVertexMinL();

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

int tempVertexMinL()
{
    int min = INFINITY;
    int v, x = NIL;

    for(v = 0; v < n; v++)
    {
        if(vertexList[v].status == TEMPORARY && vertexList[v].length < min)
        {
            min = vertexList[v].length;
            x = v;
        }
    }
    return x;
}

void prims()
{
    int c, v;
    int edgesInTree = 0;
    int wtTree = 0;
    int root;

    for(v = 0; v < n; v++)
    {
        vertexList[v].status = TEMPORARY;
        vertexList[v].predecessor = NIL;
        vertexList[v].length = INFINITY;
    }

    root = 0; // Make 0 as a root vertex. It can be other vertex
    vertexList[root].length = 0; // Make root vertex length 0

    while(1)
    {
        c = tempVertexMinL();   // Find temporary vertex with minimum path length
        if(c == NIL)
        {
            if(edgesInTree == n-1)   // If no temporary vertex left and all vertices are connected and reachable
                printf("Weight of minimum spanning tree is %d\n",wtTree);
            else                     // Otherwise Some vertices can't reachable from root vertex left with infinite path length
                printf("Graph is not connected, Spanning tree not possible");
            return;
        }

        vertexList[c].status = PERMANENT; // If NIL is not return by tempVertexMinL(), so Vertex C is current vertex

        // Include edge (vertexList[c].predecessor,c) in the tree
        if(c != root)  // Edge only added if current vertex is not root, for root vertex predecessor is NIL
        {
            edgesInTree++;
            //printf("(%s, %s, %d)\n", vertexList[vertexList[c].predecessor].name, vertexList[c].name, adj[vertexList[c].predecessor][c]);
            printf("(%s, %s)\n", vertexList[vertexList[c].predecessor].name, vertexList[c].name);
            wtTree = wtTree + adj[vertexList[c].predecessor][c];
        }

        for(v = 0; v < n; v++)  // Relabeling minimum spanning tree and predecessor
        {
            if(adj[c][v] != 0 && vertexList[v].status == TEMPORARY)
                if(adj[c][v] < vertexList[v].length)
                {
                    vertexList[v].length = adj[c][v];
                    vertexList[v].predecessor = c;
                }
        }
    }
}

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

    insertEdge("0","1",19);
    insertEdge("0","3",14);
    insertEdge("0","4",12);
    insertEdge("1","2",20);
    insertEdge("1","4",18);
    insertEdge("2","4",17);
    insertEdge("2","5",15);
    insertEdge("2","9",29);
    insertEdge("3","4",13);
    insertEdge("3","6",28);
    insertEdge("4","5",16);
    insertEdge("4","6",21);
    insertEdge("4","7",22);
    insertEdge("4","8",24);
    insertEdge("5","8",26);
    insertEdge("5","9",27);
    insertEdge("6","7",23);
    insertEdge("7","8",30);
    insertEdge("8","9",35);

    prims();

    return 0;
}
