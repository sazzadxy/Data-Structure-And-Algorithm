#include<iostream>
using namespace std;

int fibo(int n)
{
    int dp[n];
    dp[0] = 0;
    dp[1] = 1;

    for(int i = 2; i <= n; i++)
        dp[i] = dp[i-1] + dp[i-2];

    return dp[n];  // last element
}

int main()
{
    cout<<fibo(4)<<endl;
    for(int i = 0; i <= 4; i++)
        cout<<" "<<fibo(i);
}
