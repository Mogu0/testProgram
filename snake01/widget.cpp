#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QPainter>
#include "mainwindow.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle(tr("贪吃蛇"));
    QFont ft("STKaiti", 25, 75);//设置标题字体大小
    ui->label->setFont(ft);//设置标题字体大小
    QPalette titleColor;//设置标题颜色
    titleColor.setColor(QPalette::WindowText, Qt::white);//设置标题颜色
    ui->label->setPalette(titleColor);//设置标题颜色
    ui->pushButton->setText(tr("start！"));//设置开始按键文本
    ui->pushButton_2->setText(tr("quit"));//设置结束按键文本

    connect(ui->pushButton, &QPushButton::released, this, &Widget::changeToMainWindow);//设置开始按钮中断
    connect(ui->pushButton_2, &QPushButton::released, this, &QWidget::close);//设置结束按钮中断

    //mw.setWindowTitle(tr("贪吃蛇"));//设置副窗口标题

}

void Widget::changeToMainWindow()//切换到主窗口
{
    mainWindow* mw = new mainWindow();
    mw->resize(width(), height());
    hide();
    mw->show();
}


void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(rect(), QPixmap("../Image/snake.jpeg"));//绘制封面背景图
}

Widget::~Widget()
{
    delete ui;
}
