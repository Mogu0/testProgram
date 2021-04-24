#include "board.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

Board::Board(int _length):length(_length)
{
    srand((unsigned)time(NULL));
    atime = 150;//初始化时间间隔
    score = 0;//初始化分数
    memset(map, 0, sizeof(map));

    //初始化地图
    for(int i = 0; i <= length + 1; i++)
        for(int j = 0; j <= length + 1; j++)
        {
            if(i == 0 || i == length + 1)
                map[i][j] = 1;
            if(j == 0 || j == length + 1)
                map[i][j] = 1;
        }

    snake = new Snake(this);

    foodX = foodY = 0;
    while(map[foodX][foodY] != 0)
    {
        foodX = rand() % length + 1;
        foodY = rand() % length + 1;
    }
    map[foodX][foodY] = 2;

}

void Board::makeFood()
{
    foodX = foodY = 0;
    while(map[foodX][foodY] != 0)
    {
        foodX = rand() % length + 1;
        foodY = rand() % length + 1;
    }
    map[foodX][foodY] = 2;

}

bool Board::isEnd()
{
    int type = snake->detect();
    if(type == 1)
        snake->toNext();
    else if(type == 2)
    {
        snake->eat();
        makeFood();
        score += 5;
        if(atime > 5)
            atime -= 5;
        //cout<<atime<<endl;
    }
    else
    {    //游戏结束
        return true;
    }
    return false;
}


