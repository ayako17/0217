#ifndef EASYCLOCK_H
#define EASYCLOCK_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>
#include <QFontDatabase>
#include "mainwindow.h"
class MyLabel;


namespace Ui {
class easyclock;
}

class easyclock : public QWidget
{
    Q_OBJECT

public:
    explicit easyclock(QWidget *parent = nullptr);
    ~easyclock();

    void setSpinBoxData(int n);
    void setComBoxData(QString comboBoxData);
    void paintEvent(QPaintEvent *event);
signals:
    void returnToMain();

private slots:
    void togglePausePlay();
    void updateTimer();
    void updatePauseTimer();
    void resumeMainTimer();
    void showPauseMessageBox();
    void updatePauseMessageBoxText();
    void showFailureMessageBox();
    void onContinueClicked();
    void onRestartClicked();
    void onBackClicked();

private:
    Ui::easyclock *ui;
    QVBoxLayout *mainLayout,*topLayout,*bottomLayout;
    QWidget *topWidget ,*bottomWidget;
    QPushButton *pauseButton;
    QString comboBox;
    MyLabel *timerLabel;
    QTimer *mainTimer;
    QTimer *pauseTimer;
    int remainingTime;
    int remainingPauseTime;
    int completedCycles;
    bool isPaused;
    int rest; // 0: 暂停中，1: 休息中
    QMessageBox *pauseMessageBox;

    void initWindow();
};

#endif // EASYCLOCK_H
