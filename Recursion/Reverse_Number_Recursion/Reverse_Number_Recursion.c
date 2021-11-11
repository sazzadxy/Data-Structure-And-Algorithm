#include <stdlib.h>
#include <stdio.h>

long reverse(long n)
{

    /* Iterative way */
//    int rem = 0;
//
//    if(n == 0)
//        return 0;
//
//    while(n != 0){
//        rem = rem * 10;
//        rem = rem + n%10;
//        n = n/10;
//    }

    /* Recursive way */

    static long rem = 0;
    if(n == 0)
        return 0;

    rem = rem * 10;
    rem = rem + n%10;
    reverse(n/10);

    return rem;

}

int main()
{
    long n, r;
    printf("Enter a Number to reverse: ");
    scanf("%ld", &n);
    r = reverse(n);
    printf("After reverse: ");
    printf("%ld\n", r);
    return 0;
}
