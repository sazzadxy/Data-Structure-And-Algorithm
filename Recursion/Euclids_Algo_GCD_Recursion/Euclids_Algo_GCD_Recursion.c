#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b)
{
    if(b == 0) // n==0
        return a;
    return  gcd(b, a%b);
}

int lcm(int a, int b)
{
//    int max = (a<b) ? b:a;
//    int LCM = max;
//    for(;LCM <= a*b;LCM++){
//        if(LCM%a == 0 && LCM%b == 0)
//            break;
//    }
//    return LCM;

    static int temp = 1;

    if(temp%a == 0 && temp%b == 0)
        return temp;
    else{
        temp++;
        lcm(a,b);
        return temp;
    }
}

int main()
{
    int x, y;
    printf("Enter 2 numbers: ");
    scanf("%d %d", &x, &y);

    printf("GCD of %d and %d is: %d and lcm is: %d\n",x,y,gcd(x,y),lcm(x,y));
    return 0;
}

