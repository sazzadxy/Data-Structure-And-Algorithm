#include <iostream>
#include <vector>
using namespace std;

int numberSplitting(int N)
{
    int INF = 99999;
    vector <int> max_product(N+1,-INF); // Initializing max_product and filling all with -INF

    // Base Case
    max_product[1] = 0;
    max_product[2] = 1;

    for(int i = 3; i <= N; i++)   // 'i' is for setting the number to be split
        for(int j = 1; j <= i-1; j++)   // 'j' fixes the first split to be made
            max_product[i] = max(j*max_product[i-j], max(j*(i-j),max_product[i]));

    return max_product[N];
}

int main()
{
    int N;
    cout<<"Enter a number:"<<endl;
    cin>>N;
    cout<<numberSplitting(N);
}
