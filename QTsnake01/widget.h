﻿#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    void changeToMainWindow();
    ~Widget();


protected:
    void paintEvent(QPaintEvent*);

private:
    Ui::Widget *ui;
    //mainWindow mw;
};

#endif // WIDGET_H
