#ifndef START_TASK_H
#define START_TASK_H

#include <QWidget>
#include <QComboBox>
#include<QMessageBox>
#include <QSpinBox>
#include "Clock.h"
#include<QtSql/QSqlDatabase>
#include "mainClock.h"

#include<QtSql/QSqlError>


namespace Ui {
class start_task;
}

class start_task : public QWidget
{
    Q_OBJECT

public:
    explicit start_task(QWidget *parent = nullptr);
    ~start_task();

    std::unique_ptr<mainClock> mainclock;
    bool isMUSIC2;
    bool isMUSIC3;


signals:
    void returnToClock();

    void on_comboBox_textActivated(const QString &arg1);
    // public slots:

    //     void onUserLoggedIn(int userId);
private slots:


    void on_pushButton_2_clicked();
    //void on_pushButton_2_clicked();
    void on_start_clicked();
    void on_comboBox_editTextChanged(const QString &arg1);
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_spinBox_valueChanged(int arg1);
    void on_pushButton_clicked();
    void on_return_to_start_task1();
    void on_return_to_start_task2();


private:
    Ui::start_task *ui;
    QSqlDatabase db;
    QString comboBoxData;
    //int currentUserId;
    int m;
    int tomatoCount;
    bool updateTomatoCount(int userId, int tomatoCount);
    void addTaskLabelIfNotExists(const QString &label,int userID);
    void addundefinition(int userId);

};

#endif // START_TASK_H
