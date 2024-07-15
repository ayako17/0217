#include "usercenter.h"
#include "ui_usercenter.h"
#include "config.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QDate>
#include <QScrollArea>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include<QPainter>
extern int currentUserID;

usercenter::usercenter(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::usercenter)
    , stackedWidget(new QStackedWidget(this))
    , accountInfoPage(new QWidget(this))
    , personalAchievementsPage(new QWidget(this))
    , historyStatisticsPage(new QWidget(this))
    , likeStatistiPage(new QWidget(this))
    ,theme(0)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("47.98.109.159");
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("1234567890");
    db.setPort(3306);

    if (!db.open()) {
        qDebug() << "Failed to connect to database:" << db.lastError().text();
    } else {
        qDebug() << "Connected to database";
    }

    // 设置窗口属性
    setWindowTitle("个人中心");
    setWindowIcon(QIcon(ICON));

    // 左侧按钮
    QPushButton *btnAccountInfo = new QPushButton("市民基本信息", this);
    QPushButton *btnPersonalAchievements = new QPushButton("个人成就", this);
    QPushButton *btnHistoryStatistics = new QPushButton("本周财富", this);
    QPushButton *btnLikeStatistics = new QPushButton("番茄偏好", this);

    // 右侧页面
    stackedWidget = new QStackedWidget(this);
    accountInfoPage = new QWidget(this);
    personalAchievementsPage = new QWidget(this);
    historyStatisticsPage = new QWidget(this);
    likeStatistiPage = new QWidget(this);
    QSqlQuery query(db);

    accountInfoPage->setStyleSheet("background-color:rgba(255,255,255,128);");
    // 个人成就页面布局
    QScrollArea *personalAchievementsScrollArea = new QScrollArea(personalAchievementsPage);
    QWidget *achievementContent = new QWidget();
    QVBoxLayout *achievementLayout = new QVBoxLayout(achievementContent);

    struct Achievement {
        int threshold;
        QString title;
        QString description;
    };

    Achievement achievements[] = {
        {1, "小试牛刀", "获得1个番茄"},
        {5, "小有成就", "获得5个番茄      解锁背景音乐 巴黎咖啡馆"},
        {10, "坚持不懈", "获得10个番茄"},
        {15, "毅力可嘉", "获得15个番茄"},
        {20, "学无止境", "获得20个番茄"},
        {100,"番茄首富","获得100个番茄    解锁背景音乐 沙滩海浪"}
    };

    query.prepare("SELECT username, password, tomato_count FROM Users WHERE user_id = :userID");
    query.bindValue(":userID", currentUserID);
    if (query.exec()) {
        if (query.next()) {
            tomatoCount = query.value(2).toInt();
        }
    }

    for (const auto& achievement : achievements) {
        QLabel *label = new QLabel(achievement.title + ": " + achievement.description, achievementContent);

        if (tomatoCount >= achievement.threshold) {
            label->setAutoFillBackground(false); // 透明背景
        } else {
            QPalette palette = label->palette();
            palette.setColor(QPalette::Window, Qt::gray);
            label->setAutoFillBackground(true);
            label->setPalette(palette); // 灰色背景
        }

        achievementLayout->addWidget(label);
    }

    achievementContent->setLayout(achievementLayout);
    personalAchievementsScrollArea->setWidget(achievementContent);
    personalAchievementsScrollArea->setWidgetResizable(true);

    QVBoxLayout *achievementMainLayout = new QVBoxLayout(personalAchievementsPage);
    achievementMainLayout->addWidget(personalAchievementsScrollArea);
    personalAchievementsPage->setLayout(achievementMainLayout);
    QSize fixedSize(600, 400);
    personalAchievementsPage->setFixedSize(fixedSize);

    // 账户基本信息页面布局
    QVBoxLayout *accountInfoLayout = new QVBoxLayout(accountInfoPage);

    // 加头像
    QLabel *imageLabel = new QLabel;
    QPixmap pix(":/touxiang.jpg");
    imageLabel->setPixmap(pix);
    accountInfoLayout->addWidget(imageLabel);

    query.prepare("SELECT username, password, tomato_count FROM Users WHERE user_id = :userID");
    query.bindValue(":userID", currentUserID);
    if (query.exec()) {
        if (query.next()) {
            QString username = query.value(0).toString();
            QString password = query.value(1).toString();
            int tomatoCount = query.value(2).toInt();

            // 设置字体大小
            QFont font;
            font.setPointSize(24); // 设置字体大小为16

            QLabel *usernameLabel = new QLabel("账号：" + username, accountInfoPage);
            usernameLabel->setFont(font);
            accountInfoLayout->addWidget(usernameLabel);

            QLabel *passwordLabel = new QLabel("密码：" + password, accountInfoPage);
            passwordLabel->setFont(font);
            accountInfoLayout->addWidget(passwordLabel);

            QLabel *tomatoCountLabel = new QLabel("现有番茄数：" + QString::number(tomatoCount), accountInfoPage);
            tomatoCountLabel->setFont(font);
            accountInfoLayout->addWidget(tomatoCountLabel);

            for (const auto& achievement : achievements) {
                QLabel *label = new QLabel;
                label->setFont(font); // 设置成大字体
                if (tomatoCount >= achievement.threshold) {
                    label->setText("称号:" + achievement.title);
                    accountInfoLayout->addWidget(label);
                }
            }
        }
    }

    accountInfoLayout->addSpacerItem(new QSpacerItem(50, 50, QSizePolicy::Minimum, QSizePolicy::Expanding));



    // 本周统计页面布局
    QScrollArea *historyScrollArea = new QScrollArea(historyStatisticsPage);
    QWidget *historyContent = new QWidget();
    QVBoxLayout *historyLayout = new QVBoxLayout(historyContent);
    QMap<QDate, int> weeklyData;

    query.prepare("SELECT task_date, COUNT(*) as count FROM History "
                  "WHERE task_date >= :start_date AND task_date <= :end_date "
                  "GROUP BY task_date");
    QDate endDate = QDate::currentDate();
    QDate startDate = endDate.addDays(-6); // 最近一周
    query.bindValue(":start_date", startDate.toString("yyyy-MM-dd"));
    query.bindValue(":end_date", endDate.toString("yyyy-MM-dd"));

    if (query.exec()) {
        while (query.next()) {
            QDate date = query.value(0).toDate();
            int count = query.value(1).toInt();
            weeklyData[date] = count;
        }
    }

    for (int i = 0; i < 7; ++i) {
        QDate date = startDate.addDays(i);
        if (!weeklyData.contains(date)) {
            weeklyData[date] = 0;
        }
    }

    // 计算本周总番茄数
    int totalTomatoes = 0;
    for (int count : weeklyData.values()) {
        totalTomatoes += count;
    }

    // 根据总番茄数生成建议文本
    QString suggestion;
    if (totalTomatoes < 10) {
        suggestion = "本周番茄数低于10个，要努力哦！";
    } else if (totalTomatoes < 15) {
        suggestion = "本周番茄数在10到15个之间，继续加油！";
    } else {
        suggestion = "本周番茄数超过15个，做得很棒，继续保持！";
    }

    // 使用Qt Charts显示柱状图
    QBarSet *set = new QBarSet("番茄钟数");
    QStringList categories;

    for (int i = 0; i < 7; ++i) {
        QDate date = startDate.addDays(i);
        *set << weeklyData[date];
        categories << date.toString("MM-dd");
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("最近一周番茄钟数");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, *std::max_element(weeklyData.begin(), weeklyData.end()) + 1);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 创建并添加建议文本标签
    QLabel *suggestionLabel = new QLabel(suggestion);
    suggestionLabel->setAlignment(Qt::AlignCenter);
    historyLayout->addWidget(suggestionLabel);

    historyLayout->addWidget(chartView);
    historyContent->setLayout(historyLayout);
    historyScrollArea->setWidget(historyContent);
    historyScrollArea->setWidgetResizable(true);

    QVBoxLayout *historyMainLayout = new QVBoxLayout(historyStatisticsPage);
    historyMainLayout->addWidget(historyScrollArea);
    historyStatisticsPage->setLayout(historyMainLayout);

    // 番茄偏好页面布局
    QScrollArea *likeScrollArea = new QScrollArea(likeStatistiPage);
    QWidget *likeContent = new QWidget();
    QVBoxLayout *likeLayout = new QVBoxLayout(likeContent);

    QPieSeries *pieSeries = new QPieSeries();

    query.prepare("SELECT label_name, COUNT(*) as count FROM tasklabels "
                  "GROUP BY label_name");

    if (query.exec()) {
        while (query.next()) {
            QString tomatoType = query.value(0).toString();
            int count = query.value(1).toInt();
            pieSeries->append(tomatoType, count);
        }
    } else {
        qDebug() << "Failed to execute query:" << query.lastError().text();
    }

    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    pieChart->setTitle("番茄偏好统计");

    QChartView *pieChartView = new QChartView(pieChart);
    pieChartView->setRenderHint(QPainter::Antialiasing);

    likeLayout->addWidget(pieChartView);

    likeContent->setLayout(likeLayout);
    likeScrollArea->setWidget(likeContent);
    likeScrollArea->setWidgetResizable(true);

    QVBoxLayout *likeMainLayout = new QVBoxLayout(likeStatistiPage);
    likeMainLayout->addWidget(likeScrollArea);
    likeStatistiPage->setLayout(likeMainLayout);
    likeStatistiPage->setFixedSize(fixedSize);


    // 添加页面到stackedWidget
    stackedWidget->addWidget(accountInfoPage);
    stackedWidget->addWidget(personalAchievementsPage);
    stackedWidget->addWidget(historyStatisticsPage);
    stackedWidget->addWidget(likeStatistiPage);

    // 主布局
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->addWidget(new QLabel("个人中心"));
    leftLayout->addWidget(btnAccountInfo);
    leftLayout->addWidget(btnPersonalAchievements);
    leftLayout->addWidget(btnHistoryStatistics);
    leftLayout->addWidget(btnLikeStatistics);
    leftLayout->addStretch();

    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(stackedWidget);
    setLayout(mainLayout);

    // 设置信号和槽
    connect(btnAccountInfo, &QPushButton::clicked, this, &usercenter::showAccountInfo);
    connect(btnPersonalAchievements, &QPushButton::clicked, this, &usercenter::showPersonalAchievements);
    connect(btnHistoryStatistics, &QPushButton::clicked, this, &usercenter::showHistoryStatistics);
    connect(btnLikeStatistics, &QPushButton::clicked, this, &usercenter::showLikdeStatistics);
    connect(ui->return_2, &QPushButton::clicked, this, &usercenter::on_return_2_clicked);
    connect(ui->returnto1, &QPushButton::clicked, this,  &usercenter::emitreturn);

    // 默认显示账户基本信息页面
    stackedWidget->setCurrentWidget(accountInfoPage);
}

void usercenter::paintEvent(QPaintEvent *event) {
    QSqlQuery query(db);
    query.prepare("SELECT username, password, tomato_count, skin_id FROM Users WHERE user_id = :userID");
    query.bindValue(":userID", currentUserID);
    if (query.exec()) {
        if(query.next())
            theme = query.value(3).toInt();

    }
    QPainter painter(this);
    QString background;
    switch (theme) {
    case 0:
        background=":/theme0.background3.jpg";
        break;
    case 1:
        background=":/background1.jpg";
        break;
    case 2:
        background=":/theme2.background2.png";
        break;
    case 3:
        background=":/theme3.background2.jpg";
    default:
        break;
    }
    QPixmap pixmap(background);
    painter.drawPixmap(0, 0, width(), height(), pixmap);
}


usercenter::~usercenter()
{
    delete ui;
}

void usercenter::on_return_2_clicked()
{
    emit returnToClock();
    close();
}

void usercenter::showAccountInfo()
{
    stackedWidget->setCurrentWidget(accountInfoPage);
}

void usercenter::showPersonalAchievements()
{
    stackedWidget->setCurrentWidget(personalAchievementsPage);
}

void usercenter::showHistoryStatistics()
{
    stackedWidget->setCurrentWidget(historyStatisticsPage);
}

void usercenter::showLikdeStatistics()
{
    stackedWidget->setCurrentWidget(likeStatistiPage);
}

void usercenter::emitreturn(){
    emit returnTo1();
}
