#include <stdio.h>
#include <stdlib.h>

void print()
{
    //int n = 1; // value of n not updated because its auto variable and allocated again
    static int n = 1; // value of n is updated because it already allocated
    printf("hello world : %d\n", n);
    n++;
    //print();
    if(n <= 10)
        print();
    else
        return;
}

int main()
{
    print();
    return 0;
}
