#include <stdio.h>
#include <stdlib.h>

int factorial(unsigned int n)
{
    if(n == 0)
        return 1;

    return n*factorial(n-1);
}

int sum(unsigned int n)
{
    if(n == 1)
        return 1;

    return n + sum(n-1);

}

int main()
{
    unsigned int n;
    printf("Enter a number for factorial: ");
    scanf("%u",&n);
    printf("Factorial of %u is %u \n",n,factorial(n));
    printf("Sum of 1 to %d is %u ",n,sum(n));
    return 0;
}
