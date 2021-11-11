#include <stdio.h>
#include <stdlib.h>

long power(int n, int p)
{
    if(p == 0) // n==0
        return 1;

    return  n * power(n,p-1);
}

int main()
{
    int n, p;
    printf("Enter number: ");
    scanf("%d", &n);
    printf("Enter power: ");
    scanf("%d", &p);
    printf("%d^%d: %ld\n",n,p,power(n,p));
    return 0;
}
