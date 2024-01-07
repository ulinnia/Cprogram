#include<stdio.h>
#include<stdint.h>

#define MAX 8
#define RANGE (MAX-1)

uint16_t cheese[MAX]={0};       //棋盤從左到右(unsign integer 16bit(每兩個代表一個座標狀態(0、1、2)))，從上到下(0~MAX)

void Push(int color, int x, int y){
    cheese[y] = cheese[y]&~(3<<((RANGE-x)*2));//清空該座標狀態(3 bin = 11)not運算(任何狀態和00 and 都等於00)，其他不變(跟1 and)
    cheese[y] += (color<<((RANGE-x)*2));       //位移該狀態到該座標位置，把他加上去
}

void Pull(int x, int y){
    int color = (cheese[y]&(3<<((RANGE-x)*2)))>>((RANGE-x)*2);//提出該座標狀態(bin)，並將他位移到整數的起點(2^0)
    printf("color=%d\n", color);                              //輸出該狀態
}

int main(){
    Push(1, 5, 6);                                              //範例修改座標(5,6)狀態為(1)
    Pull(5,6);                                                  //提出並印出
    return 0;                                                   //這樣只需要16*8 = 128(bits)來儲存棋盤
}                                                               //對比之前需要int 8*8是(4*8)*8*8 = 2048(bits)