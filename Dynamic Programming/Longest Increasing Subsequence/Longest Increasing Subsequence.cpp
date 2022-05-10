#include <iostream>
#include<vector>
using namespace std;

int LongestIncreasingSubSequence(int nums[], int n)
{
    int i, j;
    int maxLength = 0;
    vector<int> LIS(n,1);   // Initializing LIS array and filling them all with 1

    for(i = 1; i <= n-1; i++)
    {
        for(j = 0; j <= i-1; j++)
        {
            if(nums[i] > nums[j] && LIS[i] < LIS[j]+1)
                LIS[i] = LIS[j]+1;
        }
    }
    for(i = 0; i <= n-1; i++)
        if(maxLength < LIS[i])
            maxLength = LIS[i];
    return maxLength;

}

int main()
{
    int nums[5] = {11, 23, 10, 37, 21};
    int n = sizeof(nums)/sizeof(nums[0]);

    cout<<"The length of longest increasing subsequence for the array [11, 23, 10, 37, 21] is :"<<LongestIncreasingSubSequence(nums,n);
}
