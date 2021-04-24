#include "mainwindow.h"
#include <QPainter>
#include <QTimer>
#include <board.h>
#include <QMessageBox>

mainWindow::mainWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Snake");
    flag = 0;
    isPress = false;
    //初始化定时器
    board = new Board(20);
    timer = new QTimer(this);
    timer->setInterval(board->atime);

    connect(timer, &QTimer::timeout, this, &mainWindow::timerEvent);

    timer->start();

}

void mainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(Qt::lightGray);
    //p.drawPixmap(rect(), QPixmap("../Image/grass.jpeg"));//绘制封面背景
    //地图
    p.setBrush(Qt::white);
    for(int i=0; i<=board->length+1; i++)
    {
        p.drawPixmap(0*20, i*20, 20, 20, QPixmap("../Image/grass.jpeg"));
        p.drawPixmap((board->length+1)*20, i*20, 20, 20, QPixmap("../Image/grass.jpeg"));
        p.drawPixmap(i*20, 0*20, 20, 20, QPixmap("../Image/grass.jpeg"));
        p.drawPixmap(i*20, (board->length+1)*20, 20, 20, QPixmap("../Image/grass.jpeg"));
    }

    //绘制蛇身
    p.setBrush(Qt::white);
    for(int i=0; i<board->snake->len; i++)
        p.drawRect(board->snake->s[i][1]*20, board->snake->s[i][0]*20, 20, 20);

    //绘制蛇头
    p.drawPixmap(board->snake->s[board->snake->len][1]*20,
            board->snake->s[board->snake->len][0]*20, 20, 20, QPixmap("../Image/head.png"));

    //绘制食物
    p.drawPixmap(board->foodY*20, board->foodX*20, 20, 20, QPixmap("../Image/apple1.png"));

    //绘制分数信息
    QFont font;
    font.setPointSize(26);
    p.setFont(font);
    p.setPen(Qt::blue);

    char s[10];

    sprintf(s, "%3d", board->score);
    p.drawText((board->length+3)*20+60, 16*20, "分数");
    p.drawText((board->length+3)*20+60, 18*20, s);

}

void mainWindow::timerEvent()
{
    timer->setInterval(board->atime);
    timer->start();
    if(board->isEnd())
    {
        timer->stop();
        timer->setInterval(board->atime);
        if(QMessageBox::Yes ==  QMessageBox::question(this, tr("You lose"), tr("try again?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
        {
            board = new Board(20);
            timer->setInterval(board->atime);
            timer->start();
        }
        else
        {
            exit(1);
        }
    }
    isPress = false;
    this->update();
}

void mainWindow::keyPressEvent(QKeyEvent *event)
{




    if(event->key() == Qt::Key_Up)
    {
        if(!(board->snake->dx == 1 && board->snake->dy == 0))
        {
            board->snake->turnUp();
            isPress = true;
        }
    }
    else if(event->key() == Qt::Key_Down)
    {
        if(!(board->snake->dx == -1 && board->snake->dy == 0))
        {
            board->snake->turnDown();
            isPress = true;
        }
    }
    else if(event->key() == Qt::Key_Left)
    {
        if(!(board->snake->dx == 0 && board->snake->dy == 1))
        {
            board->snake->turnLeft();
            isPress = true;
        }
    }
    else if(event->key() == Qt::Key_Right)
    {
        if(!(board->snake->dx == 0 && board->snake->dy == -1))
        {
            board->snake->turnRight();
            isPress = true;
        }
    }

    //更新界面
    this->update();
}
