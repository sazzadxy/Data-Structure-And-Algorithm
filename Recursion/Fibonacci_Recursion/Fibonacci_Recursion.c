#include <stdlib.h>
#include <stdio.h>

long fibonacci(long n)
{
//    if(n == 0)
//        return 0;
//    else if(n == 1)
//        return 1;
    if(n <= 1)
        return n;
    else
        return fibonacci(n-1) + fibonacci(n-2);
}

int main()
{
    long n;
    printf("Enter the number of terms of Fibonacci Number: ");
    scanf("%ld", &n);
    for(int i = 0; i <= n; i++)
        printf("%ld ",fibonacci(i));

    printf("\n");;
    printf("Enter Nth Fibonacci Number: ");
    scanf("%ld", &n);
    printf("The %ldth Fibonacci Number is %ld\n", n, fibonacci(n));

    return 0;
}
