#include "Clock.h"
#include "ui_Clock.h"
#include"start_task.h"
#include"usercenter.h"
#include <QIcon>
#include <QApplication>
#include <QString>
#include <QScreen>
#include <QGuiApplication>
#include <QPushButton>
#include<QVBoxLayout>
#include <memory> // 包含智能指针的头文件
#include <QPainter>
extern int currentUserID;


Clock::Clock(QWidget *parent)
    : QWidget{parent},
    Start_task(nullptr),
    Usercenter(nullptr),
    theme(0),
    ui(new Ui::Clock){
    //构造函数，初始化注册界面

    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL");//或者QMYSQL
    db.setHostName("47.98.109.159");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("1234567890");
    db.setPort(3306);
    if (!db.open()) {
        qDebug() << "Failed to connect to database:" << db.lastError().text();
    }





    ui->comboBox->addItem("初始主题");
    ui->comboBox->addItem("chiikawa主题");
    ui->comboBox->addItem("星空主题");
    ui->comboBox->addItem("治愈主题");
    initClock();
    if (parent) {
       parent->installEventFilter(this);
    }
    connect(starttask,&mypushbutton::clicked,this,&Clock::on_start_task_clicked);
    connect(personalcenter,&mypushbutton::clicked,this,&Clock::on_personal_center_clicked);
    connect(ui->comboBox,&QComboBox::currentTextChanged,this,&Clock::on_comboBox_currentTextChanged);
}
void Clock::initClock()
{

    QSqlQuery query(db);
    query.prepare("SELECT username, password, tomato_count, skin_id FROM Users WHERE user_id = :userID");
    query.bindValue(":userID", currentUserID);
    if (query.exec()) {
        if(query.next())
            theme = query.value(3).toInt();

    }
    else{
        qDebug() << "Failed to check skin_id" << db.lastError().text();
    }

    QString but1,but2,but3,but4;
    switch(theme)
    {
    case 0:
        but1=":/theme0.start1.png";
        but2=":/theme0.start2.png";
        but3=":/theme0.personal1.png";
        but4=":/theme0.personal2.png";
        break;
    case 1:
        but1=":/xiaoba.png";
        but2="";
        but3=":/theme0.personal1.png";
        but4=":/theme0.personal2.png";
        break;
    case 2:
        but1=":/theme0.start1.png";
        but2="";
        but3=":/theme0.personal1.png";
        but4=":/theme0.personal2.png";
        break;
    case 3:
        but1=":/theme3.start1.png";
        but2="";
        but3=":/theme0.personal1.png";
        but4=":/theme0.personal2.png";
        break;
    }




    starttask=new mypushbutton(but1,but2);
    starttask->setParent(this);
    starttask->move(this->width()*0.5-starttask->width()*0.5,this->height()*0.35);

    // startlabel=new QLabel;
    // startlabel->setText("开始番茄钟");
    // startlabel->setStyleSheet("16px");
    // startlabel->move(this->width()*0.5-startlabel->width()*0.5,this->height()*0.5-startlabel->height()*0.5);
    // QVBoxLayout layout;
    // layout.addWidget(starttask);
    // layout.addWidget(startlabel);
    personalcenter=new mypushbutton(but3,but4);
    personalcenter->setParent(this);
    personalcenter->move(this->width()*0.1,this->height()*0.1);

   ui->comboBox->setCurrentIndex(theme);

}
void Clock::paintEvent(QPaintEvent *event) {
   QPainter painter(this);
    QString background;
    switch (theme) {
    case 0:
        background=":/theme0.background1.jpg";
        break;
    case 1:
        background=":/background1.jpg";
        break;
    case 2:
        background=":/theme2.background1.png";
        break;
    case 3:
        background=":/theme3.background1.jpg";
    default:
        break;
    }
   QPixmap pixmap(background);
   painter.drawPixmap(0, 0, width(), height(), pixmap);
}


Clock::~Clock(){
    delete ui;
    db.close();
    if(starttask!=NULL)
        delete starttask;
    if(personalcenter!=NULL)
        delete personalcenter;
}

void Clock::on_return_to_Clock() {

    starttask->show();
    personalcenter->show();
    //startlabel->hide();
    ui->comboBox->show();
    update();
}

void Clock::returnTo1(){
    close();
    emit return1();
    delete this;
}


void Clock::on_start_task_clicked()
{
    switch(theme)
    {
    case 1:
      starttask->room1();
        break;
    }
    QTimer::singleShot(500,this,[=](){
        if (!Start_task) {
            Start_task = std::make_unique<start_task>(this);
            connect(Start_task.get(), &start_task::returnToClock, this, &Clock::on_return_to_Clock);
        }
    starttask->hide();
    personalcenter->hide();
    //startlabel->hide();
    ui->comboBox->hide();
    Start_task->show();
    });
}


void Clock::on_personal_center_clicked()
{
    if (!Usercenter) {
        Usercenter = std::make_unique<usercenter>(this);
        connect(Usercenter.get(), &usercenter::returnToClock, this, &Clock::on_return_to_Clock);
        connect(Usercenter.get(), &usercenter::returnTo1, this, &Clock::returnTo1);
    }
    starttask->hide();
    personalcenter->hide();
    //startlabel->hide();
    ui->comboBox->hide();
    Usercenter->show();
}





void Clock::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->comboBox->setCurrentText(arg1);

    if(arg1=="初始主题")
        theme=0;

    else if(arg1=="chiikawa主题")
    {   theme=1;

    }
    else if(arg1=="星空主题")
        theme=2;
    else if(arg1=="治愈主题")
    {  theme=3;
    }
   // themenum=theme;
    QSqlQuery query(db);

    query.prepare("UPDATE users SET skin_id = :theme WHERE user_id = :userID");
    query.bindValue(":userID", currentUserID);
    query.bindValue(":theme", theme); // 将主题值绑定到占位符
    if (query.exec()) {
        qDebug() << "Update successful";
    } else {
        qDebug() << "Error updating: " << query.lastError().text();
    }


    update();

}

