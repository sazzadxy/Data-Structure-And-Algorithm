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

int getIndex(char s[]);
void insertVertex(char s[]);
void deleteVertex(char s[]);
void insertEdge(char s1[], char s2[]);
void deleteEdge(char s1[], char s2[]);
void warshalls();


int main()
{
//    int choice;
//    char s1[50], s2[50];

    insertVertex("Zero");
    insertVertex("One");
    insertVertex("Two");
    insertVertex("Three");

    insertEdge("Zero","One");
    insertEdge("Zero","Three");
    insertEdge("One","Two");
    insertEdge("Two","One");
    insertEdge("Three","Zero");
    insertEdge("Three","Two");

    warshalls();


//    while(1)
//    {
//        printf("\tPath Matrix By Warshall's Algorithm\t\n");
//        printf("\t-----------------------------------\t\n");
//        printf("1.Insert a vertex\n");
//        printf("2.Remove a vertex\n");
//        printf("3.Insert an edge\n");
//        printf("4.Delete an edge\n");
//        printf("5.Display Path matrix\n");
//        printf("6.Exit\n");
//
//        printf("Enter your choice: ");
//        scanf("%d",&choice);
//
//        switch(choice)
//        {
//        case 1:
//            printf("Enter a vertex name: ");
//            scanf("%s",s1);
//            insertVertex(s1);
//            break;
//        case 2:
//            printf("Enter a vertex name: ");
//            scanf("%s",s1);
//            deleteVertex(s1);
//            break;
//        case 3:
//            printf("Enter start and end vertices: ");
//            scanf("%s",s1);
//            scanf("%s",s2);
//            insertEdge(s1,s2);
//            break;
//        case 4:
//            printf("Enter start and end vertices: ");
//            scanf("%s",s1);
//            scanf("%s",s2);
//            deleteEdge(s1,s2);
//            break;
//        case 5:
//            warshalls();
//            break;
//        case 6:
//            exit(1);
//        default:
//            printf("Wrong choice\n\n");
//            break;
//        }
//    }

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

void warshalls()
{
    /* Warshall’s Algorithm
    IF P(k-1)[i][j] IS 1
        THEN P(k)[i][j] = 1
    ELSE
        IF BOTH P(k-1)[i][k] AND P(k-1)[k][j] ARE 1
            THEN P(k)[i][j] = 1
        ELSE
            P(k)[i][j] = 0

    // P(k)[i][j] = P(k-1)[i][j] || (P(k-1)[i][k] && P(k-1)[k][j])
    */

    int i, j, k, p[MAX][MAX];

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            p[i][j] = adj[i][j];

    for(k = 0; k < n; k++)
    {
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                p[i][j] = (p[i][j] || (p[i][k] && p[k][j]));
    }

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            printf("%d ",p[i][j]);
        printf("\n");
    }
    printf("\n");
}


