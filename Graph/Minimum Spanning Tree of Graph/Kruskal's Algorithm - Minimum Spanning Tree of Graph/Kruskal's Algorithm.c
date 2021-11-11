#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30
#define NIL -1

struct Vertex
{
    char name[50];
    int father;
};

struct Vertex vertexList[MAX];

struct Edge
{
    int u;
    int v;
    int weight;
};

struct QueueNode
{
    struct Edge edge;
    struct QueueNode *next;
};

struct QueueNode *front = NULL;

int adj[MAX][MAX];  // Adjacency Matrix
int n = 0; //  number of vertices in the graph
int e = 0; //  number of edges in the graph

int getIndex(char s[]);
void insertVertex(char s[]);
void deleteVertex(char s[]);
void insertEdge(char s1[], char s2[], int wt);
void deleteEdge(char s1[], char s2[]);

void kruskal();

void insert(struct Edge e);
struct Edge Delete();
int isEmpty();


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
        adj[v][u] = wt;
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

int isEmpty()
{
   return (front == NULL) ?  1 : 0;
}

// Insert an edge in the linked priority queue
void insert(struct Edge e)
{
    struct QueueNode *temp, *p;

    temp = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    temp->edge = e;

    // Queue is empty or edge to be added has weight less than first edge
    if(front == NULL || temp->edge.weight < front->edge.weight)
    {
        temp->next = front;
        front = temp;
    }
    else
    {
        p = front;
        while(p->next != NULL && p->next->edge.weight <= temp->edge.weight)
            p = p->next;

        temp->next = p->next;
        p->next = temp;
    }
}

// Delete an edge from the linked priority queue
struct Edge Delete()
{
    struct QueueNode *temp;
    struct Edge e;

    if(isEmpty())
    {
        printf("Queue Underflow\n");
        exit(1);
    }

    temp = front;
    front = temp->next;
    e = temp->edge;
    free(temp);

    return e;
}

void kruskal()
{
    struct Edge e;
    int u, v, v1, v2, r1, r2, edgesInTree, wtTree;

    for(u = 0; u < n; u++)
        for(v = 0; v < u; v++)
            if(adj[u][v] != 0)
            {
                e.u = u;
                e.v = v;
                e.weight = adj[u][v];
                insert(e);
            }

    for(v = 0; v < n; v++)
        vertexList[v].father = NIL;

    r1 = NIL;  // root vertex of the tree which vertex v1 belongs
    r2 = NIL;  // root vertex of the tree which vertex v2 belongs
    edgesInTree = 0;
    wtTree = 0;

    while(!isEmpty() && edgesInTree < n-1) // Until examine all the edges of the graph and n-1 edges have been included in the tree
    {
        e = Delete();  // gets edge from the priority queue
        v1 = e.u;      // 2 vertices of the edge
        v2 = e.v;

        v = v1;
        while(vertexList[v].father != NIL)  // find root vertex. which vertex father is NIL is the root vertex
            v = vertexList[v].father;
        r1 = v;

        v = v2;
        while(vertexList[v].father != NIL)
            v = vertexList[v].father;
        r2 = v;

        if(r1 != r2)  // Edge (v1,v2) is included. If root of the 2 verties are not same, means they belong to different trees and do not form a cycle
        {
            edgesInTree++;
            //printf("(%s, %s)\n",vertexList[v1].name, vertexList[v2].name);
            printf("(%s, %s, %d)\n",vertexList[v1].name, vertexList[v2].name, e.weight);
            wtTree += e.weight;  // weight of the minimum spanning tree
            vertexList[r2].father = r1;  // make one vertex as the father of other vertex
        }
    }

    if(edgesInTree < n-1)
        printf("Graph is not connected, Spanning tree not possible\n");
    else
        printf("Weight of Minimum Spanning Tree is %d\n",wtTree);
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

    kruskal();

    return 0;
}
