#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include<QPushButton>
#include<QPropertyAnimation>
class mypushbutton : public QPushButton
{
    Q_OBJECT
public:
    //explicit mypushbutton(QWidget *parent = nullptr);

    mypushbutton(QString normalImg,QString pressImg ="");
    QString normalImgPath;
    QString pressedImgPath;
    void room1();
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);


signals:

public slots:

};

#endif // MYPUSHBUTTON_H
