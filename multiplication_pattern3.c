#include <stdio.h>

void main()
{
  int ans;
  int n = 1;
  for (int i = 1; i < 10 ; i++)
    for (int j = n; j < n+3; j++){
      ans = i*j;
      if (ans<10)
      {
        printf("%d x %d =  %d\t",j,i,ans);
      }else{
        printf("%d x %d = %d\t",j,i,ans);
      }
      (j%3==0)?printf("\n"):0;
      if (j==9 && i==9){
        break;
      }
      if (j%3==0 && i==9){
        printf("\n\n");
        n += 3;
        i = 1;
      }
    }
}
