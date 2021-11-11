#include <stdio.h>
#include <stdlib.h>

void print(int n)
{
    if(n <= 0)
        return;

    printf("hello world %d\n",n);
    print(n-1);
    printf("hello world %d\n",n); //deep call

}

int main()
{
    print(5);
    return 0;
}
