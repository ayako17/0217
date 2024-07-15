#ifndef USERCENTER_H
#define USERCENTER_H

#include <QWidget>
#include <QSqlDatabase>
#include <QPushButton>
#include <QStackedWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QComboBox>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include"Clock.h"

namespace Ui {
class usercenter;
}

class usercenter : public QWidget
{
    Q_OBJECT

public:
    explicit usercenter(QWidget *parent = nullptr);
    ~usercenter();
    void paintEvent(QPaintEvent *event);
    void emitreturn();

private slots:
    void on_return_2_clicked();
    void showAccountInfo();
    void showPersonalAchievements();
    void showHistoryStatistics();
    void showLikdeStatistics();

private:
    Ui::usercenter *ui;
    QSqlDatabase db;
    int tomatoCount;
    QPushButton *btnAccountInfo;
    QPushButton *btnPersonalAchievements;
    QPushButton *btnHistoryStatistics;
    QStackedWidget *stackedWidget;
    QWidget *accountInfoPage;
    QWidget *personalAchievementsPage;
    QWidget *historyStatisticsPage;
    QWidget *likeStatistiPage;
    QScrollArea *personalAchievementsScrollArea;
    QVBoxLayout *achievementLayout;
    QScrollArea *historyScrollArea;
    QVBoxLayout *historyLayout;
    QVBoxLayout *accountInfoLayout;
    int theme;
    void loadAccountInfo();
    void loadAchievements();
    void loadHistoryStatistics();

signals:
    void returnToClock();
    void returnTo1();
};

#endif // USERCENTER_H
