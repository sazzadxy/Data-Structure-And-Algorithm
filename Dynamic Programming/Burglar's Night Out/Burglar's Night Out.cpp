#include <iostream>
using namespace std;

int robHouses(int houses[], int n)
{
    if(n == 0)
        return 0;

    int max_money[n+1];

    // base case
    max_money[n] = 0;
    max_money[n-1] = houses[n-1];

    for(int i = n-2; i >= 0; i--)
        max_money[i] = max(houses[i]+max_money[i+2], houses[i+1]);

    return max_money[0];
}

int main()
{
    int houses[] = {3,8,10,4,1,7,2};
    int n = sizeof(houses)/sizeof(houses[0]);

    cout<<robHouses(houses,n);
}
