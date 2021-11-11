#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void recursiveJugglerSequence(int n)
{
    if(n == 1 || n == 0){
        printf("%4d",n);
        return;
    }


    printf("%4d",n);

//    if(n % 2 == 0)
//        n = (int)(pow(n,0.5));
//    else
//        n = (int)(pow(n,1.5));

//    recursiveJugglerSequence(n);

    recursiveJugglerSequence(n % 2 != 0 ? (int)(pow(n,1.5)) : (int)(pow(n,0.5)));
}


//void iterativeJugglerSequence(int n)
//{
//    int m = n;
//    printf("%d ",m);
//
//    while(m != 0 && m != 1){
//        if(m % 2 == 0)
//            m = floor(sqrt(m));
//        else
//            m = floor(sqrt(m*m*m));
//
//        //n = m;
//        printf("%d ",m);
//    }
//}

int main()
{
    int n;
    printf("Enter a number for Juggler Sequence: ");
    scanf("%d",&n);
    printf("Juggler Sequence of %d: ",n);
    //iterativeJugglerSequence(n);
    recursiveJugglerSequence(n);
    return 0;

}
