
#include <iostream>
using namespace std;

int MaxStockPrice(int Price[], int n)
{
    int i;
    int min_dp[n];
    int profit[n];
    int maxProfit = -1;

    // Form the minimum price array
    min_dp[0] = 0;
    for(i = 1; i < n; i++) // i = 0
        min_dp[i] = min(Price[i], min_dp[i-1]);

    // Maximum profit
    for(i= 0; i < n; i++)
    {
        profit[i] = Price[i] - min_dp[i];
        if(maxProfit < profit[i])
            maxProfit = profit[i];
    }
    return maxProfit;
}

int main()
{
    int n = 5;
    int Price[] = {2,6,1,3,5};
    cout<<MaxStockPrice(Price,n);
}
