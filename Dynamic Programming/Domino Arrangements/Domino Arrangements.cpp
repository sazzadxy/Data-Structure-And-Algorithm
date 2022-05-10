#include <iostream>
using namespace std;

int numberOfArrangement(int n)
{
    int ways[n+1];
    // base case
    ways[0] = 1;  // single vertical line for last element
    ways[1] = 1;  // double horizontal line for last element

    for(int i = 2; i <= n; i++)
        ways[i] = ways[i-1] + ways[i-2];

    return ways[n];
}

int main()
{
    cout<<numberOfArrangement(6);
}
