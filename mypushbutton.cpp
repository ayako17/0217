#include "mypushbutton.h"


mypushbutton::mypushbutton(QString normalImg,QString pressImg)
{
    this->normalImgPath=normalImg;
    this->pressedImgPath=pressImg;
    QPixmap pix;
    bool ret =pix.load(this->normalImgPath);
    if(!ret)
    {
        qDebug()<<"加载失败！";
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}

void mypushbutton::room1(){
    QPropertyAnimation* animation1=new QPropertyAnimation(this,"geometry");
    animation1->setDuration(200);
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation1->setEndValue(QRect(this->x()+30,this->y(),this->width(),this->height()));
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();

    QPropertyAnimation* animation2=new QPropertyAnimation(this,"geometry");
    animation2->setDuration(200);
    animation2->setStartValue(QRect(this->x()+30,this->y(),this->width(),this->height()));
    animation2->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation2->setEasingCurve(QEasingCurve::OutBounce);
    animation2->start();
}

void mypushbutton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressedImgPath !="")
    {
        QPixmap pix;
        bool ret =pix.load(this->pressedImgPath);
        if(!ret)
        {
            qDebug()<<"加载失败！";
            return;
        }

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mousePressEvent(e);
}

void mypushbutton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressedImgPath !="")
    {
        QPixmap pix;
        bool ret =pix.load(this->normalImgPath);
        if(!ret)
        {
            qDebug()<<"加载失败！";
            return;
        }

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
