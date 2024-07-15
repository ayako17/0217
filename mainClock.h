#ifndef MAINCLOCK_H
#define MAINCLOCK_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include<QMouseEvent>
#include<QApplication>
#include <QMessageBox>
#include <QFontDatabase>
#include <QMediaPlayer>
#include <QUrl>
#include <QAudioOutput>
class MyLabel;

namespace Ui {
class mainClock;
}

class mainClock : public QWidget
{
    Q_OBJECT

public:
    explicit mainClock(QWidget *parent = nullptr);
    ~mainClock();

    void setSpinBoxData(int n);
    void setComBoxData(QString comboBoxData);
    bool isMusic2;
    bool isMusic3;
    int num;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void returntoClockyes();
    void returntoClockno();

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
    void playMusic();
    void selectMusic(QString choice);

private:
    Ui::mainClock *ui;
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
    int rest;
    int Music;
    QMessageBox *pauseMessageBox;
    QMediaPlayer *musicPlayer;
    QAudioOutput *audioOutput;



    void initWindow();
    void nextClicked();
};

#endif // MAINCLOCK_H
