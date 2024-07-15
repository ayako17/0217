#ifndef MYLABEL_H
#define MYLABEL_H

#include <QObject>
#include <QLabel>
#include <QPainter>
class MyLabel : public QLabel
{
    Q_OBJECT

public:
    MyLabel(QWidget *parent = Q_NULLPTR);
    ~MyLabel();
public:
    //计时器更新 倒计时
    void setTime(int second);
    //画计时器
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);
    virtual bool event(QEvent *e);
    void drawTimer(QPainter *);
private:

private:
    int m_time;//倒计时时间
};



#endif // MYLABEL_H
