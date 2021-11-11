#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

void fillRandomData(int arr[], int n);
int isSorted(int arr[], int n, int order);
void inputDataFromConsole(int arr[], int n);
void printDataToConsole(int arr[], int n);
void adjust(int heapArray[], int i, int n);
void heapify(int arr[], int n);
void heapSort(int arr[], int n);
float timediff(struct timeval start, struct timeval end);

void fillRandomData(int arr[], int n)
{
    srand((unsigned)time(NULL));

    for(int i = 1; i <= n; i++)
        arr[i] = rand() % 10000; // fill array with numbers from 0-9999
}

int isSorted(int arr[], int n, int order)
{
    int sorted = 1;
    for(int i = 1; i <= n-1 && sorted; i++){
        // if order is not 0, we should check for ascending
        // order sorting, in this case if current ith element is greater than
        // the next one, then the array is not sorted in ascending.
        if(order != 0 && arr[i] > arr[i+1])
            sorted = 0;

        // if order is 0, we should check for descending order checking, so
        // if ith element is less than the next, then no more in descending order,
        // we should terminate checking.
        if(order == 0 && arr[i] < arr[i+1])
            sorted = 0;
    }
    return sorted;
}

void inputDataFromConsole(int arr[], int n)
{
    printf("Please input integer numbers\n");
    printf("You will need to input %d integers in total\n\n", n);
    for(int i = 1; i <= n; i++){
        printf("array [%d]: ", i);
        scanf("%d", &arr[i]);
    }
}

void printDataToConsole(int arr[], int n)
{
    printf("Content of the array\n");
    printf("----------------------\n");
    for(int i = 1; i <= n; i++){
        printf("%6d", arr[i]);
        // give a line break after every 10 numbers
        if(i % 10 == 0)
            printf("\n");
    }
    printf("\n\n");
}

void adjust(int heapArray[], int i, int n)
{
    int j = 2 * i;  // left child of i
    int item  = heapArray[i];  // getting the content of the index i in variable item

    // iterate as long as j is valid, that means there is an element at j
    while(j <= n){
        if(j < n && heapArray[j] < heapArray[j+1])  // compare between j and its sibling exists
            j = j + 1;    // move position of j

        if(item >= heapArray[j])  // compare j and its parennt
            break;

        heapArray[j/2] = heapArray[j];   // copy j to parent if j is greater
        j = j * 2;                       // after copying update j
    }
    heapArray[j/2] = item;   //  copy item to updated j/2 position
}


void heapify(int arr[], int n)
{
    for(int i = n/2; i >= 1; --i)
        adjust(arr,i,n);
}

void heapSort(int arr[], int n)
{
    int temp;
    heapify(arr,n); // build the heap calling heapify operation
    for(int i = n; i >= 2; --i){
        temp = arr[1];  // getting the largest element from the root
        arr[1] = arr[i]; // copying the last element from heap into the root
        adjust(arr,1,i-1);  // adjust the heap at root, since we taken out the root, so total elements in heap is i-1
        arr[i] = temp;  // place the largest elements at index i
    }
}

float timediff(struct timeval start, struct timeval end)
{
    return (end.tv_sec - start.tv_sec) * 1000.0f + (end.tv_usec - start.tv_usec) / 1000.0f;
}


int main()
{
    struct timeval start;
    struct timeval end;
    float elapsed;

    int n;
    n = 500000;
    int *array = (int *)malloc(sizeof(int) * (n+1));
    if (array == NULL){
        printf("Unable to allocate dynamic memory\n");
        return 1;
    }
    // fill the array with the elements
    fillRandomData(array, n);

    // uncomment the following if you want to display the array content into console
    //printf("Unsorted array: \n");
    //printDataToConsole(array, n);


    printf("Going to perform heap sort on %d numbers, please wait ...\n", n);
    gettimeofday(&start, 0);
    heapSort(array, n);
    gettimeofday(&end, 0);

    // check if the array is sorted.
    if (isSorted(array, n, 1))
        printf("Sorted in ascending order\n");
    else
        printf("Not sorted in ascending order\n");

    // uncomment the following if you want to display the sorted content of the array
    // into console.

    //printf("Sorted array: \n");
    //printDataToConsole(array, n);

    elapsed = timediff(start, end);
    printf("Time taken to sort %d numbers using heap sort is: %f msec\n", n, elapsed);
    free(array);

    return 0;
}
