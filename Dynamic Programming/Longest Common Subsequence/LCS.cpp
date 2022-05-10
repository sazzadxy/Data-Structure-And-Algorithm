#include <iostream>
#include <string>
using namespace std;

void lcs(string s1, string s2)
{
    int dp[s1.length()+1][s2.length()+1];
    unsigned int i,j;

    for(i = 0; i <= s1.length(); i++)
    {
        for(j = 0; j <= s2.length(); j++)
        {
            if(i==0 || j==0)
                dp[i][j] = 0;
            else if(s1[i-1] == s2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
        }
    }

    //return dp[s1.length()][s2.length()];
    cout<<"The length of the LCS "<<dp[s1.length()][s2.length()]<<endl;

    int index = dp[s1.length()][s2.length()];
    char lcsLength[index+1];
    lcsLength[index] = '\0';

    int m = s1.length();
    int n = s2.length();

    while(m > 0 && n > 0){
        if(s1[m-1] == s2[n-1]){
            lcsLength[index-1] = s1[m-1];
            m--;
            n--;
            index--;
        }
        else if(dp[m-1][n] > dp[m][n-1])
            m--;
        else
            n--;
    }

    cout<<"String 1:"<<" "<<s1<<", "<<"String 2:"<<" "<<s2<<", "<<"LCS:"<<" "<<lcsLength<<endl;
}

int main()
{
    //int result;
    string s1 = "abcdefx";
    string s2 = "bdaex";
    lcs(s1,s2);
}



//#include <iostream>
//#include <string.h>
//using namespace std;
//
//void lcs(char *s1, char *s2)
//{
//    int dp[strlen(s1)+1][strlen(s2)+1];
//    unsigned int i,j;
//
//    for(i = 0; i <= strlen(s1); i++)
//    {
//        for(j = 0; j <= strlen(s2); j++)
//        {
//            if(i==0 || j==0)
//                dp[i][j] = 0;
//            else if(s1[i-1] == s2[j-1])
//                dp[i][j] = 1 + dp[i-1][j-1];
//            else
//                dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
//        }
//    }
//
//    //return dp[s1.length()][s2.length()];
//    cout<<"The length of the LCS "<<dp[strlen(s1)][strlen(s2)]<<endl;
//
//    int index = dp[strlen(s1)][strlen(s2)];
//    char lcsLength[index+1];
//    lcsLength[index] = '\0';
//
//    int m = strlen(s1);
//    int n = strlen(s2);
//
//    while(m > 0 && n > 0){
//        if(s1[m-1] == s2[n-1]){
//            lcsLength[index-1] = s1[m-1];
//            m--;
//            n--;
//            index--;
//        }
//        else if(dp[m-1][n] > dp[m][n-1])
//            m--;
//        else
//            n--;
//    }
//
//    cout<<"String 1:"<<s1<<endl<<"String 2:"<<s2<<endl<<"LCS:"<<lcsLength<<endl;
//}
//
//int main()
//{
//    //int result;
//    char s1[] = "abcdxpqr";
//    char s2[] = "xbdcp";
//    lcs(s1,s2);
//}

