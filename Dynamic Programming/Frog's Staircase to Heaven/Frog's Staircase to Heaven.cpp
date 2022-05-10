#include <iostream>
using namespace std;

int staircase(int n)
{
    int ways[n+1]; // ways[n]
    int i;
    ways[0] = 1;  // staircase of height 0
    ways[1] = 1;  // staircase of height 1

    for(i = 2; i <= n; i++)
        ways[i] = ways[i-1] + ways[i-2];

    return ways[n];  // last element
}

int main()
{
    int n;
    cout<<"Enter number of the staircase"<<endl;
    cin>>n;
    cout<<staircase(n);
}
