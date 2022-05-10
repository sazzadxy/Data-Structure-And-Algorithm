#include <iostream>
using namespace std;

int CoinChange(int amount, int coin[], int n)
{
    int dp[n+1][amount+1]; // Creating the dp table
    int i, j;

    for(i = 0; i <= n; i++)
    {
        for(j = 0; j <= amount; j++)
        {
            if(i==0 && j!=0)   // base case (not choosing the coin)
                dp[i][j] = 0;
            else if(j==0)      // base case (not choosing the coin)
                dp[i][j] = 1;
            else if(j<coin[i-1])  // when the amount is lesser than the coin
                dp[i][j] = dp[i-1][j];   // retain the previous row's value
            else
                dp[i][j] = dp[i-1][j] + dp[i][j-coin[i-1]];  // Number of ways = not choosing coin + choosing the coin
        }
    }
    return dp[n][amount];
}

int main()
{
    int n = 3;
    int coin[n] = {1,2,3};
    int amount = 4;
    cout<<"Available ways for changing the coin: "<<CoinChange(amount,coin,n)<<endl;
}
