#include<stdio.h>

void main(){
    int ans;
    for (int i = 1; i < 10; i++)
        for (int j = 1; j < 10; j++){
            ans = i*j;
            if (ans<10)
            {
                printf("%dx%d= %d ",j,i,ans);
            }else{
                printf("%dx%d=%d ",j,i,ans);
            }
            (j==9)?printf("\n"):0;
        }
}