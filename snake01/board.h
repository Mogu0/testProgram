#ifndef BOARD_H
#define BOARD_H

#include "snake.h"

class Board
{
public:
    int score;//当前分数
    int atime;//每次下落的间隔时间
    int length;//地图边长
    int foodX;//食物坐标
    int foodY;
    int map[100][100];//保存地图信息;
    Snake* snake;
    Board(int);
    void makeFood();
    bool isEnd();
};

#endif // BOARD_H
