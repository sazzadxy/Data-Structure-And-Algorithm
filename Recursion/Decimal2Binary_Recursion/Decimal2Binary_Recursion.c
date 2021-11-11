#include <stdio.h>
#include <stdlib.h>

void DecToBin(unsigned int n)
{
    if(n == 1){
        printf("1");
        return;
    }
    else if(n == 0){
        printf("0");
        return;
    }
    else{
        DecToBin(n/2);
        printf("%d", n%2);
    }
}

//void DecToBin(unsigned int n)
//{
//    unsigned stack[32];
//    unsigned top = -1;
//
//    while(n>0){
//        stack[++top] = n%2;
//        n /= 2;
//    }
//
//    for(int i = top; i >= 0; i--)
//        printf("%d",stack[i]);
//}

int main()
{
    int n;
    printf("Enter an integer in decimal number system\n");
    scanf("%d", &n);
    printf("%d in binary number system is:\n",n);
    DecToBin(n);
    return 0;
}
