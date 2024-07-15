#include "start_task.h"
//#include "qsqlquery.h"
#include<QtSql/QSqlQuery>
#include "ui_start_task.h"
#include "config.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QMoveEvent>
#include<QDebug>
#include <memory>

extern int currentUserID;
int curLabel_id=0;
extern bool isFinished;

start_task::start_task(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::start_task),
    mainclock(nullptr)
{
    ui->setupUi(this);

    //初始化comboBox
    ui->comboBox->setEditable(false);


    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("47.98.109.159");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("1234567890");
    db.setPort(3306);

    if (!db.open()) {
        qDebug() << "Failed to connect to database:" << db.lastError().text();
    }
    else
        qDebug()<<"already connected to database";

    addundefinition(currentUserID);
    //load user's labels
    QSqlQuery query;
    query.prepare("SELECT label_name FROM TaskLabels WHERE user_id = :user_id");
    query.bindValue(":user_id", currentUserID);

    if (!query.exec()) {
        qDebug() << "Failed to load user labels:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QString labelName = query.value(0).toString();
        ui->comboBox->addItem(labelName);
    }




    setWindowTitle("任务设置");
    setWindowIcon(QIcon(ICON));



    //ui->comboBox->addItem("学习");
    //ui->comboBox->addItem("未命名");
    ui->comboBox->setCurrentText("未选择标签");
    //ui->comboBox->setEditable(true);

    ui->spinBox->setValue(0);


    // ComboBox槽函数
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &start_task::on_comboBox_currentTextChanged);
    connect(ui->comboBox,&QComboBox::editTextChanged,this,&start_task::on_comboBox_editTextChanged);

    // QSpinBox槽函数
    connect(ui->spinBox, &QSpinBox::valueChanged, this, &start_task::on_spinBox_valueChanged);

    //connect(ui->pushButton_2, &QPushButton::clicked, this, &start_task::on_pushButton_2_clicked1);

    connect(ui->start,&QPushButton::clicked,this,&start_task::on_start_clicked);

    connect(ui->pushButton,&QPushButton::clicked,this,&start_task::on_pushButton_clicked);



}


start_task::~start_task()
{
    delete ui;
    db.close();
}


void start_task::on_pushButton_2_clicked()
{
    emit returnToClock();
    close();
}


void start_task::on_comboBox_editTextChanged(const QString &arg1)
{

    //ui->comboBox->setEditable(true);
    ui->comboBox->setCurrentText(arg1);

}


void start_task::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->comboBox->setCurrentText(arg1);
}


void start_task::on_spinBox_valueChanged(int arg1)
{
    ui->spinBox->setValue(arg1);
}


void start_task::addundefinition(int userID)
{
    QSqlQuery query;
    query.prepare("SELECT label_id FROM TaskLabels WHERE label_name = :label_name AND user_id = :user_id");
    query.bindValue(":label_name", "未选择标签");
    query.bindValue(":user_id", userID);

    if (!query.exec()) {
        qDebug() << "Failed to check task label:" << query.lastError().text();
        return;
    }

    if (!query.next()) {
        // 如果标签不存在，插入新的标签
        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO TaskLabels (label_name, user_id) VALUES (:label_name, :user_id)");
        insertQuery.bindValue(":label_name", "未选择标签");
        insertQuery.bindValue(":user_id", userID);

        if (!insertQuery.exec()) {
            qDebug() << "Failed to insert new task label:" << insertQuery.lastError().text();
        } else {
            qDebug() << "New task label inserted successfully.";
        }
    }

}

//添加新任务标签
void start_task::on_pushButton_clicked()
{
    QString newLabel = ui->lineEdit->text();
    qDebug()<<"用户ID："<<currentUserID;

    if (!newLabel.isEmpty()) {
        addTaskLabelIfNotExists(newLabel,currentUserID);
        ui->comboBox->addItem(newLabel);
        ui->lineEdit->clear();
    }
}

//检查标签是否存在并添加到数据库
void start_task::addTaskLabelIfNotExists(const QString &label,int userID) {
    QSqlQuery query;
    query.prepare("SELECT label_id FROM TaskLabels WHERE label_name = :label_name AND user_id = :user_id");
    query.bindValue(":label_name", label);
    query.bindValue(":user_id", userID);

    if (!query.exec()) {
        qDebug() << "Failed to check task label:" << query.lastError().text();
        return;
    }

    if (!query.next()) {
        // 如果标签不存在，插入新的标签
        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO TaskLabels (label_name, user_id) VALUES (:label_name, :user_id)");
        insertQuery.bindValue(":label_name", label);
        insertQuery.bindValue(":user_id", userID);

        if (!insertQuery.exec()) {
            qDebug() << "Failed to insert new task label:" << insertQuery.lastError().text();
        } else {
            qDebug() << "New task label inserted successfully.";
        }
    } else {
        // 标签已存在，显示提示信息
        QMessageBox::information(this, "标签已存在", "该标签已存在，请输入其他标签。");
        qDebug() << "Task label already exists for this user.";
    }
}

void start_task::on_start_clicked()
{

    int spinBoxData=ui->spinBox->value();

    if(spinBoxData !=0)
    {
        comboBoxData=ui->comboBox->currentText();

        // 传递数据
        tomatoCount = spinBoxData;


        // 显示新页面
        if (mainclock == nullptr) {
            mainclock = std::make_unique<mainClock>(this); // 创建新的 mainclock 对象
            mainclock->setAttribute(Qt::WA_DeleteOnClose); // 窗口关闭时自动删除
            connect(mainclock.get(), &mainClock::returntoClockyes, this, &start_task::on_return_to_start_task1);
            connect(mainclock.get(), &mainClock::returntoClockno, this, &start_task::on_return_to_start_task2);

        }
        mainclock->isMusic2=isMUSIC2;
        mainclock->isMusic3=isMUSIC3;
        mainclock->num = tomatoCount;
        ui->pushButton_2->hide();
        ui->comboBox->hide();
        ui->pushButton->hide();
        ui->spinBox->hide();
        ui->label->hide();
        ui->label_2->hide();
        ui->label_3->hide();
        ui->lineEdit->hide();
        ui->start->hide();
        mainclock->show();

        if(isFinished){
            updateTomatoCount (currentUserID,tomatoCount);
        }

    }
    else{
        QMessageBox::information(this, "提醒", "不可以只设置一个番茄钟哦！");
    }

}

//更新Users库中番茄钟数据（累计）
bool start_task::updateTomatoCount(int userId, int tomatoCount) {
    QSqlQuery query;

    // 更新番茄数
    query.prepare("UPDATE Users SET tomato_count = tomato_count + :tomato_count WHERE user_id = :user_id");
    query.bindValue(":tomato_count", tomatoCount);
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError();
        return false;
    }

    // 准备查询语句，获取更新后的番茄数
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT tomato_count FROM Users WHERE user_id = :user_id");
    selectQuery.bindValue(":user_id", userId);

    // 执行查询操作
    if (!selectQuery.exec()) {
        qDebug() << "Select failed:" << selectQuery.lastError();
        return false;
    }

    // 获取查询结果
    if (selectQuery.next()) {
        int updatedTomatoCount = selectQuery.value(0).toInt();
        qDebug() << "Updated tomato count:" << updatedTomatoCount;
        if (updatedTomatoCount < 5) {
            isMUSIC2 = 0;
            isMUSIC3 = 0;
        } else if (updatedTomatoCount < 100) {
            isMUSIC2 = 1;
            isMUSIC3 = 0;
        } else{
            isMUSIC2 = 1;
            isMUSIC3 = 1;
        }
        return true;
    } else {
        qDebug() << "No result found for user_id:" << userId;
        return false;
    }
}

void start_task::on_return_to_start_task1() {
    ui->pushButton_2->show();
    ui->comboBox->show();
    ui->pushButton->show();
    ui->spinBox->show();
    ui->label->show();
    ui->label_2->show();
    ui->label_3->show();
    ui->lineEdit->show();
    ui->start->show();
    mainclock.reset();

    QSqlQuery query;

    //找到label_id
    query.prepare("SELECT label_id FROM TaskLabels WHERE label_name = :label_name AND user_id = :user_id ");
    query.bindValue(":label_name", comboBoxData);
    query.bindValue(":user_id", currentUserID);
    query.exec();
    if(query.next())
    {
        curLabel_id = query.value("label_id").toInt();
        qDebug() << "Current label_id:" << curLabel_id;
    } else {
        qDebug() << "Failed to find label_id for label_name:" << comboBoxData << "and user_id:" << currentUserID;
        return; // 找不到对应的label_id时，直接返回
    }

    //添加到数据库
    query.prepare("INSERT INTO History (user_id, label_id, task_date, task_duration, tomato_count) "
                  "VALUES (:user_id, :label_id, CURRENT_DATE(), :task_duration, :tomato_count)");

    query.bindValue(":user_id", currentUserID);
    query.bindValue(":task_duration", tomatoCount * 25); // 任务持续时间，以分钟为单位
    query.bindValue(":tomato_count", tomatoCount);
    query.bindValue(":label_id", curLabel_id);

    if (!query.exec()) {
        qDebug() << "Failed to insert task data:" << query.lastError().text();
    } else {
        qDebug() << "Task data inserted successfully.";

        // 更新番茄数
        if (!updateTomatoCount(currentUserID, tomatoCount)) {
            qDebug() << "Failed to update tomato count.";
        }
    }

    QMessageBox::information(this, "任务完成", "你已成功完成任务！");
}
void start_task::on_return_to_start_task2(){
    ui->pushButton_2->show();
    ui->comboBox->show();
    ui->pushButton->show();
    ui->spinBox->show();
    ui->label->show();
    ui->label_2->show();
    ui->label_3->show();
    ui->lineEdit->show();
    ui->start->show();
    mainclock.reset();
    isFinished=false;
    if(!isFinished)
    {updateTomatoCount(currentUserID,-tomatoCount);}
    tomatoCount = 0;
    QMessageBox::information(this, "任务失败", "任务失败，再接再厉吧");
}

