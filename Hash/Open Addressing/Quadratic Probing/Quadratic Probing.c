#include <stdio.h>
#include <stdlib.h>

#define TSIZE 19

enum type_of_record {EMPTY, OCCUPIED, DELETED};

struct Student{
    int studentId;
    char studentName[25];
};

struct Record{
    struct Student info;
    enum type_of_record status;
};

void insert(struct Student rec, struct Record table[]);
void del(int key, struct Record table[]);
int search(int key, struct Record table[]);
void display(struct Record table[]);
int hash(int key);
void init(struct Record table[]);

int main()
{
    int choice, key, i;
    struct Record table[TSIZE];
    struct Student rec;

    init(table);

    while(1){
        printf("\t------------------------\t\n");
        printf("\tHash (Quadratic probing)\t\n");
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
            else{
                printf("Key is found at index: %d\n",i);
                printf("%d %s\n",table[i].info.studentId, table[i].info.studentName);
            }
            break;
        case 3:
            printf("Enter a key to be deleted: ");
            scanf("%d",&key);
            del(key,table);
            break;
        case 4:
            display(table);
            break;
        case 5:
            exit(1);
        default: printf("Choose option from 1-5\n");
        }
    }

    return 0;
}

void init(struct Record table[])
{
    for(int i = 0; i < TSIZE; i++)
        table[i].status = EMPTY;
}

int hash(int key)
{
    return (key%TSIZE);
}

void insert(struct Student rec, struct Record table[])
{
    int i, location, h;
    int key = rec.studentId;
    h = hash(key);
    location = h;

    for(i = 0; i < TSIZE; i++){
        if(table[location].status == EMPTY || table[location].status == DELETED){
            table[location].info = rec;
            table[location].status = OCCUPIED;
            printf("Record inserted\n\n");
            return;
        }
        if(table[location].info.studentId == key){
            printf("Duplicate key\n\n");
            return;
        }
        location = (h + i*i) % TSIZE;
    }
    printf("Record can not be inserted : Table overflow\n\n");
}

int search(int key, struct Record table[])
{
    int h, location, i;
    h = hash(key);
    location = h;

    for(i = 0; i < TSIZE; i++){
        if(table[location].status == EMPTY) //table[location].status == EMPTY || table[location].status == DELETED
            return -1;
        if(table[location].info.studentId == key)
            return location;

        location = (h + i*i) % TSIZE;
    }
    return -1;
}

void del(int key, struct Record table[])
{
    int location;
    location = search(key,table);

    if(location == -1)
        printf("Key not found\n\n");
    else
        table[location].status = DELETED;
}

void display(struct Record table[])
{
    for(int i = 0; i < TSIZE; i++){
        printf("[%d] : ",i);
        if(table[i].status == OCCUPIED)
            printf("Occupied: %d %s\n", table[i].info.studentId, table[i].info.studentName);
        else if(table[i].status == DELETED)
            printf("Deleted\n");
        else
            printf("Empty\n");
    }
}

