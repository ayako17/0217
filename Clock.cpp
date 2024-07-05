#include "Clock.h"
#include "ui_Clock.h"
#include"config.h"

Clock::Clock(QWidget *parent)
    : QWidget{parent},
    ui(new Ui::Clock){
    //构造函数，初始化注册界面
    ui->setupUi(this);

    setWindowTitle("注册");
    setWindowIcon(QIcon(ICON));


    if (parent) {
        parent->installEventFilter(this);
    }

}
void Clock::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap pixmap(CLOCK);
    painter.drawPixmap(0, 0, width(), height(), pixmap); // 绘制背景图片
}



Clock::~Clock(){
    delete ui;
}
