#include <stdio.h>
#include <stdlib.h>

#define TSIZE 10

struct Student{
    int studentId;
    char studentName[25];
};

struct Node{
    struct Student info;
    struct Node *next;
};

void insert(struct Student rec, struct Node *table[]);
void del(int key, struct Node *table[]);
int search(int key, struct Node *table[]);
void displayTable(struct Node *table[]);
int hash(int key);
void rehash();

int hash(int key)
{
    return (key % TSIZE);
}

void insert(struct Student rec, struct Node *table[])
{
    int h, key, size = 0;
    float n = 0.0; /* n => Load Factor, keeps check on whether rehashing is required or not (Optional) */
    struct Node *newNodePtr;
    key = rec.studentId;

    if(search(key,table) != -1){
        printf("Duplicate key\n");
        return;
    }

    h = hash(key);

    // Insert beginning of the list h
    newNodePtr = (struct Node*)malloc(sizeof(struct Node));
    newNodePtr->info = rec;
    newNodePtr->next = table[h];
    table[h] = newNodePtr;
    size++;
    
    // Optional
    //Calculating Load factor
    //N = S/T. S = number of record, T = size of table
    n = (1.0 * size) / TSIZE;
    if (n >= 0.75){
        //rehashing
        printf("going to rehash\n");
        rehash(table);
    }
}

// (Optional)
void rehash(struct Node *table[])
{
    struct Node *p;
    int i = 0, n = TSIZE;
    n = 2 * n;
    /*
     *array variable is assigned with newly created Hash Table
     *with double of previous array size
    */

    p = (struct Node*)malloc(n * sizeof(struct Node));

//    for(i = 0; i< TSIZE; i++)
//        table[i] = NULL;

    for (i = 0; i < TSIZE; i++){
        /* Extracting the Linked List at position i of Hash Table array */
        p = table[i];
        if (p == NULL){
            /* if there is no Linked List, then continue */
            continue;
        }else{
            /*
             *Presence of Linked List at i
             *Keep moving and accessing the Linked List item until the end.
             *Get one key and value at a time and add it to new Hash Table array.
            */
            while (p != NULL)
            {
                insert(p->info, table);
                p = p->next;
            }
        }
    }
}

int search(int key, struct Node *table[])
{
    int h = hash(key);
    struct Node *p = table[h];

    while(p != NULL){
        if(p->info.studentId == key){
            printf("%d %s\n", p->info.studentId, p->info.studentName);
            return h;
        }
        p = p->next;
    }
    return -1;
}

void del(int key, struct Node *table[])
{
    int h;
    struct Node *temp, *p;
    h = hash(key);

    if(table[h] == NULL){
        printf("Key %d not found\n",key);
        return;
    }

    if(table[h]->info.studentId == key){
        temp = table[h];
        table[h] = temp->next;
        free(temp);
        return;
    }

    p = table[h];
    while(p != NULL){
        if(p->next->info.studentId == key){
            temp = p->next;
            p->next = temp->next;
            free(temp);
            return;
        }
        p = p->next;
    }
}

void displayTable(struct Node *table[])
{
    int i;
    struct Node *p;

    for(i = 0; i < TSIZE; i++){
        printf("\n[%d]",i);

        if(table[i] != NULL){
            p = table[i];
            while(p != NULL){
                printf("%d %s\t", p->info.studentId, p->info.studentName);
                p = p->next;
            }
        }
    }
    printf("\n");
}

int main()
{
    int choice, key, i;
    struct Node *table[TSIZE];
    struct Student rec;

    for(i = 0; i< TSIZE; i++)
        table[i] = NULL;

    while(1){
        printf("\t------------------------\t\n");
        printf("\tHash (Separate Chaining)\t\n");
        printf("\t------------------------\t\n");
        printf("1. Insert a record\n");
        printf("2. Search a record\n");
        printf("3. Delete a record\n");
        printf("4. Display table\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice){
        case 1:
            printf("Enter student id: ");
            scanf("%d",&rec.studentId);
            printf("Enter student name: ");
            scanf("%s",rec.studentName);
            insert(rec,table);
            break;
        case 2:
            printf("Enter a key to be searched: ");
            scanf("%d",&key);
            i = search(key,table);
            if(i == -1)
                printf("Key not found\n");
            else
                printf("Key is found at chain: %d\n",i);
            break;
        case 3:
            printf("Enter a key to be deleted: ");
            scanf("%d",&key);
            del(key,table);
            break;
        case 4:
            displayTable(table);
            break;
        case 5:
            exit(1);
        default: printf("Choose option from 1-5\n");
        }
    }

    return 0;
}
