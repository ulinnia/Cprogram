#include<stdio.h>
#include<assert.h>
#include <stdbool.h>
#define SIZE 8
#define ZONE(x,y) (x<8 && x>=0 && y<8 && y>=0)

int ChessArray[SIZE][SIZE];                     //chessboard
int SpaceCanPut[SIZE][SIZE];                    //store where the player can put

void InputArray(){
    int initialChessArray[SIZE][SIZE] = {       //initial chessboard
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 2, 0, 0, 0},
        {0, 0, 0, 2, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            ChessArray[i][j] = initialChessArray[i][j];
        }
    }
}



void PrintFunction(){
    printf("It's black(1) turn....\n");            //print ChessArray
    printf(" ");
    for (int i=0; i<9; i++)
        for (int j=0; j<8; j++){
            if ((i-1)<0){
                printf(" ");
                printf("%d",j);
            }else{
                if(j==0){
                    printf("%d",i-1);
                }
                printf(" %d",ChessArray[j][i-1]);
                /*
                if (ChessArray[j][i-1]==0){
                    printf("  ");
                }else{
                    printf(" %d",ChessArray[j][i-1]);
                }            //print space not print 0
                */
            }
            if (j==7){
                printf("\n");
            }
        }

    printf("You can put at:  ");                    //print where I can put
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++){
            if (SpaceCanPut[j][i]==1){
                printf("(%d, %d)",j,i);
            }
        }
    printf("\n");
}

int InTheLine(int x, int y, int dx, int dy, int color, bool findspace, bool flip){
    int SpaceAcross=0;      //(dx,dy)direction     //color = player  //use findspace function or not 
    for(int i=2; i<8; i++){                     //flip do the same check like findspace
        int target_x = x + i*dx;
        int target_y = y + i*dy;
        if (ZONE(target_x,target_y)){
            if (ChessArray[target_x][target_y]==0 && ((!findspace)|flip)){
                break;               //SpaceAcross Flip function if it is space, break 
            }else if (ChessArray[target_x][target_y]==color){
                if (findspace){     //find the space 0
                    break;
                }else{
                    if(flip){       //find the color equal to player
                        for (int s=0; s<i; s++){
                            ChessArray[x+(s*dx)][y+(s*dy)]=color;
                        }
                        break;
                    }else{          //find how much chess I can eat
                        SpaceAcross=(i-1);
                        break;
                    }
                }
            }else if (ChessArray[target_x][target_y]==0 && findspace){
                SpaceCanPut[target_x][target_y] = color;
                break;
            }
        }
    }
    return SpaceAcross;
}

int CoorEightNeighbor(int x, int y, int color, bool findspace, bool flip){
    int SpaceAcross=0;
    for (int dx=-1; dx<=1; dx++)        //eight blocks check
        for (int dy=-1; dy<=1; dy++)
            if (ZONE(x+dx,y+dy))
                if (dx|dy)              //not equal to the original block
                    if (!(flip)){       //no flip function
                        if (ChessArray[x+dx][y+dy]==(3-color)){
                            if(findspace){
                                int temp = InTheLine(x,y,dx,dy, color, findspace, flip);
                            }else{      //find how much chess I can eat
                                SpaceAcross += InTheLine(x,y,dx,dy, color, findspace, flip);
                            }
                        }
                    }else{              //flip function
                        if (ChessArray[x+dx][y+dy]==(3-color)){
                            int temp = InTheLine(x, y, dx, dy, color, findspace, flip);
                        }
                    } 
    return SpaceAcross;
}

void FlipChess(int x,int y, int color){     //x,y = where I want to put,and flip
    int temp = CoorEightNeighbor(x, y, color, false, true);
}

void LongestDistance(){
    int x,y,SpaceAcross;
    int Longest=0;
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            if (SpaceCanPut[j][i]==2){      //computer replace the longest way till
                SpaceAcross=CoorEightNeighbor(j, i, 2, false, false);   //the all posibility had tried
                if(SpaceAcross>Longest){
                    x=j;
                    y=i;
                    Longest=SpaceAcross;
                }
            }
        }
    }
    FlipChess(x, y, 2);
    printf("Computer put at: (%d,%d)\n",x,y);
}

bool JudgeTheChess(int player){
    for (int i=0; i<8; i++)         //initial SpaceArray
        for (int j=0; j<8; j++)
            SpaceCanPut[j][i]=0;
    bool CanPut=0;                  //judge whether the player can put the chess
    for (int i=0; i<8; i++)
        for (int j=0; j<8; j++){
            if (ChessArray[i][j]==player){
                int temp = CoorEightNeighbor(i, j, player, true, false);
            }                       //findspace function check.record on SpaceCanPut
        }
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            if (SpaceCanPut[j][i]==player){
                CanPut=1;
                break;              //check you can 
            }
    if (CanPut==1){
        if (player==1){
            PrintFunction();        //print for human
        }
    }
    return CanPut;
}

void WinnerJudge(){
    int black_num=0;
    int white_num=0;
    for (int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if (ChessArray[j][i]==1){
                black_num += 1;
            }else if (ChessArray[j][i]==2){
                white_num += 1;
            }
        }                           //count the black and white by ChessArray
    }
    if(black_num>white_num){
        printf("Black(You) is Winner\n%d : %d",black_num,white_num);
    }else if (white_num>black_num){
        printf("White(Computer) is Winner\n%d : %d",white_num,black_num);
    }else{
        printf("It's Draw\n%d : %d",white_num,black_num);
    }
    
}

int main(){
    int player = 1;                  //start at black(me)
    InputArray();
    bool white=1;
    bool black=1;
    while (true){
        if (player==1){
            black=JudgeTheChess(player);
        }else if (player==2){
            white=JudgeTheChess(player);
        }
        
        if((player==1)? black:white){   //if you can't put then skip
            if (player==1) {
                int x,y;
                printf("You want to put at(Please input like this:x(KeaboardSpace)y): ");
                scanf("%d%d",&x,&y);
                FlipChess(x, y, 1);
            }else{
                LongestDistance();
            }
        }
        if (!(black|white)){            //Both can't put
            break;
        }
        player=(player==1)? 2:1;        //player change
    }
    WinnerJudge();
    return 0;
}
