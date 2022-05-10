#include <iostream>
using namespace std;

void KnapSack(int n, int W, int wt[], int profit[])
{
    int dp[n+1][W+1];  // creating dp table
    int i,j;

    for(i = 0; i <= n; i++)
    {
        for(j = 0; j <= W; j++)
        {
            if(i==0 || j==0)
                dp[i][j] = 0;
            else if(wt[i-1] > j)         // if amount is greater than weight
                dp[i][j] = dp[i-1][j];   // Retain previous row's value
            else
                dp[i][j] = max(dp[i-1][j],dp[i-1][j-wt[i-1]]+profit[i-1]);
        }
    }

    cout<<"Maximum profit:"<<dp[n][W];
}

int main()
{
    int n = 4;
    int wt[4] = {2,3,4,5};
    int profit[4] = {10,50,30,20};
    int W = 5;

    KnapSack(n,W,wt,profit);

}

