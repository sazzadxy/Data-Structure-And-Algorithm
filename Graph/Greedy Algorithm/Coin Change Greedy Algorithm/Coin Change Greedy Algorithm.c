#include <stdio.h>
#include <stdlib.h>

void coin_chage_greedy(int n)
{
    int coins[] = {20,10,5,2,1};  //start by having the values of the coins in an array in reverse sorted order
    int i = 0;

    printf("Coins are needed for making %d:\n",n);

    while(n)  // Until value is not 0
    {
        if(coins[i] > n)  // starting from the 0th element (element with the largest value) and checking if can use this coin or not
            i++;          // if the value of this coin is greater than the value to be made, then moving to the next coin
        else              // If the value of the coin is not greater than the value to be made, then we can take this coin.
        {
            printf("%d\t",coins[i]);    // just print the value right here to indicate to take it
            n = n - coins[i];           // the value to be made is reduced by coins[i]  i.e 25 = 25 - 20 = 5, 5 - 5 = 0
        }
        //printf("\n");
    }

}

int main()
{
//    int i;
//    for(i = 1; i <= 20; i++)
//        coin_chage_greedy(i);

    coin_chage_greedy(117);
    printf("\n");
    coin_chage_greedy(16);


    /*
    When does the above greedy algorithm fail?
    coins[] = {25,20,10,5}
    value = 40
    The greedy solution will be 25+10+5 [3 coins].
    But the optimal solution will be 20+20 [2 coins].
    */

    return 0;
}
