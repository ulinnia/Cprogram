#include<stdio.h>
#include<assert.h>
#define SIZE 8

int test[SIZE][SIZE];

void inputArray(){
    for (int i=0; i<SIZE; i++)
        for (int j=0; j<SIZE; j++){
            scanf("%d", &(test[i][j]));
            assert(test[i][j]==0 || test[i][j]==1 || test[i][j]==2);
        }
}

void spacetoput(int x, int y, int dx, int dy){
    for(int i=2; i<8; i++){
        int targetx = x + i*dx;
        int targety = y + i*dy;
        if (targetx<8 && targetx>=0 && targety<8 && targety>=0){
            if (test[targetx][targety]==test[x][y]){
                break;
            }else if (test[targetx][targety]==0){
                printf("(%d , %d)",targetx,targety);
                break;
            }
        }
    }
}

void coor(int x,int y){
    for (int dx=-1; dx<=1; dx++)
        for (int dy=-1; dy<=1; dy++){
            if (!(dx==0 && dy==0)){
                if (!(test[x+dx][y+dy]==0 || test[x+dx][y+dy]==test[x][y])){
                    spacetoput(x,y,dx,dy);
                }
            }
        }
    
}

int main(){
    int x,y;
    setbuf(stdout,NULL);
    printf("give me the coordinate:");
    scanf("%d%d",&x,&y);
    assert(x<8 && y<8);

    printf("give me the array:");
    inputArray();
    printf("color %d\n", test[x][y]);
    printf("can put at: ");
    (test[x][y]==0)? printf("nowhere to put"):coor(x,y);
}