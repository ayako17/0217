#include "mylabel.h"
#include<QDebug>
#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
#pragma execution_character_set("utf-8")
extern int currentUserID;

MyLabel::MyLabel(QWidget *parent)
    :QLabel (parent)
{

}

MyLabel::~MyLabel()
{

}

void MyLabel::setTime(int second)
{
    m_time = second;
    update();
}

//重写paint事件
void MyLabel::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    //设置抗锯齿
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    drawTimer(&painter);
}

bool MyLabel::event(QEvent *e)
{
    return QLabel::event(e);
}

void MyLabel::drawTimer(QPainter *p)
{

    //先设置外矩形的大小用于绘制圆形进度条
    QRect rcOut = this->rect();

    //adjust四个参数：dx1,dy1相对于左上角的点,dx2,dy2相对于右下角的点
    rcOut.adjust(10,10,-10,-10);
    QSize outSize = rcOut.size();
    //获取这个矩形的左上角坐标
    int out_X = rcOut.x();
    int out_Y = rcOut.y();

    //设置内矩形的大小用于绘制时间
    QRect rcInt = this->rect();
    rcInt.adjust(10,45,-10,-45);
    QSize inSize = rcInt.size();
    int in_X = rcInt.x();
    int in_Y = rcInt.y();

    //画内矩形
    int themenum;

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL");//或者QMYSQL
    db.setHostName("47.98.109.159");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("1234567890");
    db.setPort(3306);
    if (!db.open()) {
        qDebug() << "Failed to connect to database:" << db.lastError().text();
    }
    QSqlQuery query(db);
    query.prepare("SELECT username, password, tomato_count, skin_id FROM Users WHERE user_id = :userID");
    query.bindValue(":userID", currentUserID);
    if (query.exec()) {
        if(query.next())
             themenum = query.value(3).toInt();

    }
    else{
        qDebug() << "Failed to check skin_id" << db.lastError().text();
    }

    QString color;
    color="#47add5";

    if(db.isOpen())
    {
    switch(themenum)
    {
    case 0:
        color="#47add5";
        break;
    case 1:
        color="#e0f2fc";
        break;
    case 2:
        color="#0b347d";
        break;
    case 3:
        color="#3d4e9c";
        break;
    }
    }


    //画矩形边框色，同主界面的背景色，不同的话会有出现一个长方形矩形
    p->setPen(QPen(QColor(color), 1, Qt::SolidLine));
    //绘制矩形
    p->drawRect(rcInt);


    //绘制时间
    //设置画笔样式
    QFont font;
    //大小根据主界面label的大小调整
    font.setPointSize(45);
    p->setFont(font);
    QPen pen;
    pen.setColor(QColor("#fff68f"));
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    p->setPen(pen);
    int minutes = m_time / 60;
    int seconds = m_time % 60;
    QString timer = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
    p->drawText(in_X, in_Y, inSize.width(), inSize.height(), Qt::AlignVCenter | Qt::AlignHCenter, timer);

    // 绘制圆形进度条

    QLinearGradient gradient(out_X, out_Y, outSize.height(), out_Y);
    gradient.setColorAt(0, QColor("#FFFFE0"));
    gradient.setColorAt(1.0, QColor("#FFFFF0"));

    int startAngle = 90 * 16;
    int spanAngle = m_time*-360/1500 * 16; // 完整圆形覆盖角度

    QPen penForeground;
    penForeground.setBrush(gradient);
    penForeground.setWidth(15);
    penForeground.setJoinStyle(Qt::RoundJoin);
    penForeground.setCapStyle(Qt::RoundCap);
    p->setPen(penForeground);
    p->drawArc(rcOut, startAngle, spanAngle);

}
