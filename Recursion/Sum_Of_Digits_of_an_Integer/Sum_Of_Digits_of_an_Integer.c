#include <stdio.h>
#include <stdlib.h>

//int iterativesumOfInt(int n)
//{
//    if(n == 1)
//        return 1;
//
//    int rem, sum = 0;
//
//    while(n != 0){
//        rem = n%10;
//        sum += rem ;
//        n = n/10;
//    }
//    return sum;
//}

int recursiveSumofInt(int n)
{
    if(n == 0) // n/10
        return 0;

    return n%10 + recursiveSumofInt(n/10);

}


int main()
{
//    printf("%d",iterativesumOfInt(1234));
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Sum of digits: %d",recursiveSumofInt(n));
    return 0;
}
