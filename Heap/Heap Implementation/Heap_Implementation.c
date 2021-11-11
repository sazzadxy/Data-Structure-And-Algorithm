#include <stdio.h>
#include <stdlib.h>

#define LARGE_VALUE 100000
#define SIZE 1000

void insert(int value, int arr[], int *pn);
int deleteRoot(int arr[], int *pn);
void restoreUp(int arr[], int loc);
void restoreDown(int arr[], int i, int size);
void display(int arr[], int n);
void buildHeap_TopDown(int arr[], int n);
void buildHeap_BottomUp(int arr[], int n);
void createArray(int arr[], int n);

void buildHeap_BottomUp(int arr[], int n)
{
    for(int i = n/2; i >= 1; i--)   // if array is a complete binary tree start from first non leaf node index: floor(n/2)
        restoreDown(arr,i,n);       // use restore down form arr[n/2] to arr[1]
}

void buildHeap_TopDown(int arr[], int n)
{
    for(int i = 2; i < n; i++)   // if array is a complete binary tree restore up for all elements form a[2] to a[n]
        restoreUp(arr,i);        // heap adjustment by bottom-up approach
}

void insert(int value, int arr[], int *pn)
{
    (*pn)++;
    arr[*pn] = value;
    restoreUp(arr,*pn); // heap adjustment by top-down approach
}

void restoreUp(int arr[],int i)
{
    int k = arr[i];
    int iparent = i/2;
    while(arr[iparent] < k){  // if do not include No sentinel LARGE_VALUE : while(iparent > 0 or iparent >= 1 && arr[iparent] < k)
        arr[i] = arr[iparent];
        i = iparent;
        iparent = i/2;
    }
    arr[i] = k;
}

int deleteRoot(int arr[], int *pn)
{
    int maxValue = arr[1];  // declare max value at index 1
    arr[1] = arr[*pn];      // assign last value at index 1
    (*pn)--;                // decrease heap size
    restoreDown(arr,1,*pn); // heap adjustment by bottom-up approach
    return maxValue;
}

void restoreDown(int arr[], int i, int n)  // i is the index of  key which violates heap order property
{
    int k = arr[i];
    int lchild = i*2, rchild = lchild + 1;
    while(rchild <= n){
        if(k >= arr[lchild] && k >= arr[rchild]){
            arr[i] = k;
            return;
        }
        else if(arr[rchild] < arr[lchild]){
            arr[i] = arr[lchild];
            i = lchild;
        }
        else{
            arr[i] = arr[rchild];
            i = rchild;
        }
        lchild = i*2;
        rchild = lchild + 1;
    }

    if(lchild == n && k < arr[lchild]){ // if number of nodes is even or have 1 child
            arr[i] = arr[lchild];
            i = lchild;
        }

    arr[i] = k;
}

void display(int arr[], int n)
{
    printf("Heap size: %d\n",n);
    for(int i = 1; i <= n; i++)
        printf("%d ",arr[i]);
    printf("\n");
}

void createArray(int arr[], int n)
{
    printf("Enter size of array: ");
    scanf("%d",&n);

    printf("Enter elements: ");
    for(int i = 1; i <= n; i++)
        scanf("%d",&arr[i]);

    printf("Heapify: Enter T for (Top-Down Approach) or B for (Bottom-Up Approach): ");
    char c;
    scanf(" %c",&c);
    (c == 't' || c == 'T') || (c == 't' || c == 'T') ? buildHeap_TopDown(arr,n) : buildHeap_BottomUp(arr,n);
    display(arr,n);
}

int main()
{
    int n = 0;    // size of heap
    int arr[SIZE];
    arr[0] = LARGE_VALUE;  // Sentinel: All the keys in heap should be less than this value
    int value,choice;

//    int arr1[] = {LARGE_VALUE, 20, 33, 15, 6, 40, 60, 45, 16, 75, 10, 80, 12};
//    int arr2[] = {LARGE_VALUE, 20, 33, 15, 6, 40, 60, 45, 16, 75, 10, 80, 12};
//    buildHeap_BottomUp(arr1,12);
//    buildHeap_TopDown(arr2,12);
//    display(arr1,12);
//    display(arr2,12);

    while(1){
        printf("1.Insert\n");
        printf("2.Delete root\n");
        printf("3.Display\n");
        printf("4.Build Heap\n");
        printf("5.Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        if(choice == 5)
            break;
        switch(choice){
        case 1: printf("Enter the value to be inserted: ");
                scanf("%d",&value);
                insert(value,arr,&n);
                break;
        case 2: if(n==0)
                    printf("Heap is empty\n");
                else{
                    value = deleteRoot(arr,&n);
                    printf("Maximum value is: %d\n",value);
                }
                break;
        case 3: display(arr,n);
                break;
        case 4: createArray(arr,n);
                break;
        default: printf("Wrong choice\n");
        }
    }
    return 0;
}
