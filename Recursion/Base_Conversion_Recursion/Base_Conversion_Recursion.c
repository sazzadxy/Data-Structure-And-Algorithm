#include <stdio.h>
#include <stdlib.h>

void convertBase(int n, int base)
{
    int rem;
    if(n==0)
        return;
    convertBase(n/base,base);

    rem = n%base;
    if(rem<10)
        printf("%d",rem);
    else
        printf("%c",rem-10+'A');
}

void printNumReverse(unsigned n)
{
    if(n==0)
        return;
    printf("%u\n",n);
    printNumRev(n-1);  //tail recursion
}

void printNumForward(unsigned n)
{
    if(n==0)
        return;
    printNumRev(n-1);
    printf("%u\n",n);
}

long factorial(unsigned n)
{
    if(n <= 1)
        return 1L;
    return n * factorial(n-1); // not tail recursion
}

int main()
{
    unsigned int n;

    printf("Enter an positive decimal number: ");
    scanf("%d", &n);
    printf("Binary form: "); convertBase(n,2); printf("\n");
    printf("Octal form: "); convertBase(n,8); printf("\n");
    printf("Hexadecimal form: "); convertBase(n,16); printf("\n");
    return 0;
}
