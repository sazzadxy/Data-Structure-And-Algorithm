#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

struct Vertex{
    char name[50];
};

struct Vertex vertexList[MAX];

int adj[MAX][MAX];  // Adjacency Matrix
int n = 0; //  number of vertices in the graph
int e = 0; //  number of edges in the graph

void display();
int getIndex(char s[]);
int isAdjacent(char s1[], char s2[]);
void insertVertex(char s[]);
void deleteVertex(char s[]);
void insertEdge(char s1[], char s2[]);
void deleteEdge(char s1[], char s2[]);
int degree(char s[]);


int main()
{
    int choice, x;
    char s1[50], s2[50];

//    insertVertex("AA");
//    insertVertex("BB");
//    insertVertex("CC");
//    insertVertex("DD");
//    insertVertex("EE");
//
//    insertEdge("AA","BB");
//    insertEdge("AA","CC");
//    insertEdge("CC","DD");
//    insertEdge("DD","AA");
//    insertEdge("CC","AA");
//    insertEdge("BB","EE");

    while(1)
    {
        printf("\tUndirected Graph (Adjacency Matrix)\t\n");
        printf("\t-----------------------------------\t\n");
        printf("1.Display Adjacency Matrix\n");
        printf("2.Insert a vertex\n");
        printf("3.Remove a vertex\n");
        printf("4.Insert an edge\n");
        printf("5.Delete an edge\n");
        printf("6.Display degree of a vertex\n");
        printf("7.Check if there is an edge between two vertice\n");
        printf("8.Exit\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            display();
            break;
        case 2:
            printf("Enter a vertex name: ");
            scanf("%s",s1);
            insertVertex(s1);
            break;
        case 3:
            printf("Enter a vertex name: ");
            scanf("%s",s1);
            deleteVertex(s1);
            break;
        case 4:
            printf("Enter start and end vertices: ");
            scanf("%s",s1);
            scanf("%s",s2);
            insertEdge(s1,s2);
            break;
        case 5:
            printf("Enter start and end vertices: ");
            scanf("%s",s1);
            scanf("%s",s2);
            deleteEdge(s1,s2);
            break;
        case 6:
            printf("Enter vertex name: ");
            scanf("%s",s1);
            x = degree(s1);
            if(x == -1)
                printf("Vertex name not present in the graph\n\n");
            else
                printf("Degree is: %d\n\n",x);
            break;
        case 7:
            printf("Enter the name of first vertex: ");
            scanf("%s",s1);
            printf("Enter the name of second vertex: ");
            scanf("%s",s2);
            x = isAdjacent(s1,s2);
            if(x == -1)
                printf("Vertex name not present in the graph\n\n");
            else if(x == 0)
                printf("There is no edge from %s to %s\n\n",s1,s2);
            else
                printf("There is an edge from %s to %s\n\n",s1,s2);
            break;
        case 8:
            exit(1);
        default:
            printf("Wrong choice\n\n");
            break;
        }
    }

    return 0;
}

void display()
{
    int i, j;

    printf("Adjacency Matrix - \n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            printf("%4d",adj[i][j]);
        printf("\n");
    }

    printf("\nVertices - ");
    for(i = 0; i < n; i++)
        printf("%s ",vertexList[i].name);

    printf("\nEdges - ");
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if(adj[i][j] != 0)
                printf("(%s,%s) ", vertexList[i].name,vertexList[j].name);
    printf("\n\n");
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

int isAdjacent(char s1[], char s2[])
{
    int u, v;
    u = getIndex(s1);
    v = getIndex(s2);

    if(u == -1 || v == -1)
        return -1;

    return adj[u][v];
}

int degree(char s[])
{
    int v;
    int u = getIndex(s);
    int deg = 0;

    if(u == -1)
        return -1;

    for(v = 0; v < n; v++)
        if(adj[u][v] != 0)
            deg++;

    return deg;
}
