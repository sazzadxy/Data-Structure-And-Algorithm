#include <iostream>
using namespace std;

int grid(int m, int n)
{
    int dp[m][n];
    int i,j;

    // initialize the base case for last row-column
    for(i = 0; i < m; i++)
        dp[i][n-1] = 1;  // for row
    for(j = 0; j < n; j++)
        dp[m-1][j] = 1; // for column

    // filling up the dp matrix
    // starting from the second last row-column up to 1st row-column
    for(i = m-2; i >= 0; i--)
    {
        for(j = n-2; j >= 0; j--)
            dp[i][j] = dp[i][j+1]+dp[i+1][j];
    }

    return dp[0][0]; // save result into the first index
}

int main()
{
    int m, n;
    cout<<"Enter the number of columns: ";
    cin>>m;
    cout<<"Enter the number of rows: ";
    cin>>n;
    cout<<"The number of ways to reach from first to last index: ";
    cout<<grid(m,n)<<endl;
}
