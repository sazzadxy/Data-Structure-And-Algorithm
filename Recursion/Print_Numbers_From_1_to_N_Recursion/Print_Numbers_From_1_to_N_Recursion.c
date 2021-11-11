#include <stdlib.h>
#include <stdio.h>

void print1(long n)
{
    if(n == 0)
        return;

    printf("%ld ", n);
    print1(n-1);
}

void print2(long n)
{
    if(n == 0)
        return;

    print2(n-1);
    printf("%ld ", n);

}

long series(long n)
{
    long sum;
    if(n == 0)
        return 0;

    sum = n + series(n-1);
    printf("%ld + ", n);
    return sum;

}

int main()
{
    long n;
    printf("Enter Nth Number to print : ");
    scanf("%ld", &n);
    printf("Unwinding phase ");
    print1(n);
    printf("\n");
    printf("Winding phase " );
    print2(n);
    printf("\n");
    printf("Sum of series up to %ld th is: ", n);
    printf("\b\b= %ld",series(n));
    return 0;
}
