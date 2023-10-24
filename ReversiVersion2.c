#include<stdio.h>
#include<assert.h>
#define SIZE 8

int NowArray[SIZE][SIZE];
int SpaceCanPut[2][SIZE][SIZE];

void PrintFunction(int SpaceCanPut[2][SIZE][SIZE]){
    for (int i=0; i<2; i++){
        (i==0)? printf("Black can put at : "):printf("\nWhite can put at : ");
        for (int j=0; j<8; j++)
            for (int k=0; k<8; k++){
                if (SpaceCanPut[i][k][j]==i+1){
                    printf("(%d, %d)",k,j);
                }
            }
    }
}

void spacetoput(int NowArray[8][8], int x, int y, int dx, int dy, int SpaceCanPut[2][SIZE][SIZE], int n){
    for(int i=2; i<8; i++){
        int targetx = x + i*dx;
        int targety = y + i*dy;
        if (targetx<8 && targetx>=0 && targety<8 && targety>=0){
            if (NowArray[targetx][targety]==NowArray[x][y]){
                break;
            }else if (NowArray[targetx][targety]==0){
                SpaceCanPut[n][targetx][targety]= n+1;
                break;
            }
        }
    }
}

void coor(int NowArray[8][8], int x, int y, int SpaceCanPut[2][SIZE][SIZE], int n){
    for (int dx=-1; dx<=1; dx++)
        for (int dy=-1; dy<=1; dy++){
            if (!(dx==0 && dy==0)){
                if (!(NowArray[x+dx][y+dy]==0 || NowArray[x+dx][y+dy]==NowArray[x][y])){
                    spacetoput(NowArray,x,y,dx,dy,SpaceCanPut, n);
                }
            }
        }
    
}

void main(){        //put the array//
    int NowArray[8][8]={{0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,1,1,1,0,0},
                        {0,0,0,2,1,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0}
                       };
    int n;
    for (int i=0; i<8; i++)
        for (int j=0; j<8; j++){
            if (NowArray[j][i]==1){
                int n = 0;
                coor(NowArray, j, i, SpaceCanPut, n);
            }else if(NowArray[j][i]==2){
                int n = 1;
                coor(NowArray, j, i, SpaceCanPut, n);
            }
        }
    PrintFunction(SpaceCanPut);
}