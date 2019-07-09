#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
//#include <QEvent>
#include <QKeyEvent>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
//    void keyPressEvent(QKeyEvent * pEvent);
//    bool event(QEvent *event);
    ~Widget();
};

#endif // WIDGET_H
