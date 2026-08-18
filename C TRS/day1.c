#include <stdio.h>
int main () {
    int a,k=1,b=0,i,j;
    scanf ("%d",&a);
    for (i=1;i<=a;i++){
        printf (" %d \n",b);
        j=b+k;
        b=k;
        k=j;
    }
    return 0;
}