#include "easyclock.h"
#include "ui_easyclock.h"

#include "mylabel.h"
#include "config.h"

easyclock::easyclock(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::easyclock),
    mainLayout(new QVBoxLayout(this)),
    topLayout(new QVBoxLayout(this)),
    bottomLayout(new QVBoxLayout(this)),
    topWidget(new QWidget(this)),
    bottomWidget(new QWidget(this)),
    pauseButton(new QPushButton(this)),
    timerLabel(new MyLabel(this)),
    mainTimer(new QTimer(this)),
    pauseTimer(new QTimer(this)),
    remainingTime(1500), // 初始时间为25分钟（1500秒）
    remainingPauseTime(300), // 暂停时间为5分钟（300秒）
    isPaused(0),
    rest(0),
    completedCycles(0),
    pauseMessageBox(nullptr)
{
    ui->setupUi(this);

    setWindowTitle(TITLE);
    setWindowIcon(QIcon(ICON));

    int fontId = QFontDatabase::addApplicationFont(ZITI);
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont myFont(fontFamily);
    myFont.setBold(true);

    initWindow();
    togglePausePlay();
}

easyclock::~easyclock() {
    delete ui;

}
void easyclock::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap pixmap(":/theme0.background1.jpg");
    painter.drawPixmap(0, 0, width(), height(), pixmap);
}
//初始化窗口
void easyclock::initWindow() {

    setLayout(mainLayout);
    topWidget->setLayout(topLayout);
    mainLayout->addWidget(topWidget);
    bottomWidget->setLayout(bottomLayout);
    mainLayout->addWidget(bottomWidget);//布局修改


    timerLabel->setFixedSize(240, 220);
    topLayout->addWidget(timerLabel, 0, Qt::AlignCenter);

    //QPushButton *pauseButton = new QPushButton;
    pauseButton->setText("▶");
    pauseButton->setFixedSize(80, 80);
    pauseButton->setStyleSheet("font-size: 30px; color: #800000; background-color: #FFFACD; border-radius: 40px;");
    bottomLayout->addWidget(pauseButton, 0, Qt::AlignCenter);

    timerLabel->setText("25:00");
    timerLabel->setTime(remainingTime);
    timerLabel->setStyleSheet("font-size: 36px; color: #800000;");


    connect(pauseButton, &QPushButton::clicked, this, &easyclock::togglePausePlay);
    connect(mainTimer, &QTimer::timeout, this, &easyclock::updateTimer);
    connect(pauseTimer, &QTimer::timeout, this, &easyclock::updatePauseTimer);
    connect(ui->exitButton, &QPushButton::clicked, this, &easyclock::onBackClicked);
}

void easyclock::togglePausePlay() {
    if (!isPaused) {
        // 开始或继续计时
        pauseButton->setText("||");
        mainTimer->start(1000);
        if (pauseMessageBox) {
            pauseMessageBox->hide();
        }
    } else {
        // 暂停计时器
        mainTimer->stop();
        pauseButton->setText("▶");
        showPauseMessageBox();
    }
    isPaused = !isPaused;
}

void easyclock::updateTimer() {

    if (remainingTime > 0) {
        remainingTime--;

        int minutes = remainingTime / 60;
        int seconds = remainingTime % 60;
        timerLabel->setText(QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0')));
        timerLabel->setTime(remainingTime);
    } else {
        // 计时结束
        mainTimer->stop();
        isPaused = true;
        pauseButton->setText("▶");

        // 进入5分钟休息
        rest = 1;
        remainingPauseTime = 300;
        showPauseMessageBox();
        remainingTime = 1500;
    }
}

void easyclock::updatePauseTimer() {
    if (remainingPauseTime > 0) {
        remainingPauseTime--;
        updatePauseMessageBoxText();
    } else {
        pauseTimer->stop();
        if (pauseMessageBox) {
            pauseMessageBox->close();
            delete pauseMessageBox;
            pauseMessageBox = nullptr;
        }

        if (rest == 0) {
            showFailureMessageBox();
        } else {
            onRestartClicked();
        }
    }
}

void easyclock::resumeMainTimer() {
    mainTimer->start(1000);
    isPaused = false;
    pauseButton->setText("||");
}

void easyclock::showPauseMessageBox() {
    if (!pauseMessageBox) {
        pauseMessageBox = new QMessageBox(this);

        QString styleSheet = QString("QLabel {"
                                     "min-width: 400px;"
                                     "min-height: 250px; "
                                     "font-size: 36px;"
                                     "color: #800000;"
                                     "}");

        pauseMessageBox->setStyleSheet(styleSheet);

        if (rest == 0) {
            pauseMessageBox->setWindowTitle("暂停中");
        } else {
            remainingPauseTime = 300;
            pauseMessageBox->setWindowTitle("休息中");
        }

        QPushButton *continueButton = new QPushButton("继续", pauseMessageBox);
        continueButton->setFixedSize(80, 60);
        continueButton->setStyleSheet("font-size: 26px; color: #800000;");
        pauseMessageBox->addButton(continueButton, QMessageBox::AcceptRole);

        connect(continueButton, &QPushButton::clicked, this, &easyclock::onContinueClicked);
    }

    updatePauseMessageBoxText();
    pauseTimer->start(1000);
    pauseMessageBox->show();
}

void easyclock::updatePauseMessageBoxText() {
    if (pauseMessageBox) {
        if (rest == 0) {
            pauseMessageBox->setText(QString("暂停倒计时: %1:%2").arg(remainingPauseTime / 60, 2, 10, QChar('0')).arg(remainingPauseTime % 60, 2, 10, QChar('0')));
        } else {
            pauseMessageBox->setText(QString("出去走一走吧！\n休息倒计时: %1:%2").arg(remainingPauseTime / 60, 2, 10, QChar('0')).arg(remainingPauseTime % 60, 2, 10, QChar('0')));
        }
    }
}

void easyclock::showFailureMessageBox() {
    QMessageBox *failureMessageBox = new QMessageBox(this);
    failureMessageBox->setFixedSize(2400, 2400);
    failureMessageBox->setWindowTitle("专注失败");
    failureMessageBox->setText("暂停时间结束，番茄爆炸啦！请选择你接下下来的操作");

    QPushButton *restartButton = new QPushButton("重新开始", failureMessageBox);
    failureMessageBox->addButton(restartButton, QMessageBox::AcceptRole);

    QPushButton *backButton = new QPushButton("回到登录界面", failureMessageBox);
    failureMessageBox->addButton(backButton, QMessageBox::RejectRole);

    failureMessageBox->setStandardButtons(QMessageBox::NoButton);
    failureMessageBox->setWindowFlags(failureMessageBox->windowFlags() & ~Qt::WindowCloseButtonHint);

    connect(restartButton, &QPushButton::clicked, this, &easyclock::onRestartClicked);
    connect(backButton, &QPushButton::clicked, this, &easyclock::onBackClicked);

    failureMessageBox->exec();
}

void easyclock::onContinueClicked() {
    if (pauseMessageBox) {
        pauseMessageBox->close();
        pauseMessageBox = nullptr;
    }
    pauseTimer->stop();
    resumeMainTimer();
}

void easyclock::onRestartClicked() {

    remainingTime = 1500; // 重置时间为25分钟
    timerLabel->setText("25:00");
    remainingPauseTime = 300;
    rest = 0; // Reset rest status
    resumeMainTimer();

}

void easyclock::onBackClicked() {
    emit returnToMain();
}
