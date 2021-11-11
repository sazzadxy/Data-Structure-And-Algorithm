#include <stdio.h>
#include <stdlib.h>

void towerOfHanoi(int n,char source, char temp, char destination)
{
    if(n == 1){
        printf("Move disk %d from %c--->%c\n",1,source,destination);
        return;
    }

    towerOfHanoi(n-1,source,destination,temp);
    printf("Move disk %d from %c--->%c\n",n,source,destination);
    towerOfHanoi(n-1,temp,source,destination);
}

int main()
{
    int n;
    printf("How many disks: ");
    scanf("%d",&n);
    towerOfHanoi(n,'A','B','C');
    return 0;
}
