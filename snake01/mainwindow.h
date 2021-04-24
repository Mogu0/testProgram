#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <board.h>
#include <QKeyEvent>

class mainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit mainWindow(QWidget *parent = nullptr);
    int flag;//判断是否暂停
    bool isPress;//控制按键频率
    QTimer* timer;
    Board* board;

    void keyPressEvent(QKeyEvent *event);
protected:
    void paintEvent(QPaintEvent*);

signals:

public slots:
    void timerEvent();
};

#endif // MAINWINDOW_H
