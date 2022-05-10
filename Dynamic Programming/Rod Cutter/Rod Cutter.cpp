#include <iostream>
using namespace std;

int RodCutter(int cost[], int n)
{
    int rod[n+1]; // length of the given rod
    int i, j;

    rod[0] = 0;
    for(i = 1; i <= n; i++)
    {
        int maxValue = -1;
        for(j = 1; j <= i; j++)
        {
            maxValue = max(maxValue,cost[j] + rod[i-j]);
        }
        rod[i] = maxValue;
    }
    return rod[n];
}

int main()
{
    int cost[5] = {0, 2, 4, 7, 8};
    int n = sizeof(cost)/sizeof(cost[0]) - 1; // n is always 1 less than cost array length because 0'th element is cost[0]

    cout<<"Maximum value that could be earned by cutting up the rod and selling the pieces of the cost array {0,2,4,7,8} is:"<<RodCutter(cost,n)<<endl;
}
