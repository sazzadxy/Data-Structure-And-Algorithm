#include <iostream>
using namespace std;

int stairwayToHeaven2(int n, int fee[])
{
    int min_fee[n+1];

    // Base case
    min_fee[0] = 0;
    min_fee[1] = min_fee[2] = fee[0];

    for(int i = 3; i <= n; i++)
        min_fee[i] = min(min_fee[i-1]+fee[i-1],
                            min(min_fee[i-2]+fee[i-2],
                                min_fee[i-3]+fee[i-3]));
    return min_fee[n];
}

int main()
{
    int fee[] = {2,1,3,1,2};
    int n = sizeof(fee)/sizeof(fee[0]);
    cout<<stairwayToHeaven2(n,fee);
}
