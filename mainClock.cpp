#include "mainClock.h"
#include "mylabel.h"
#include "ui_mainClock.h"

#include "config.h"

bool isFinished=true;

mainClock::mainClock(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::mainClock),
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
    musicPlayer(new QMediaPlayer(this)),
    audioOutput(new QAudioOutput(this)),
    isPaused(0),
    rest(0),
    completedCycles(0),
    Music(0),
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
    ui->MusicBox->setCurrentText("未选择音乐");
    selectMusic("未选择音乐");

    installEventFilter(this);
}

mainClock::~mainClock() {
    delete ui;

}

bool mainClock::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (!this->childAt(mouseEvent->pos()))
            {
                if (qobject_cast<QPushButton*>(this->childAt(mouseEvent->pos())) || qobject_cast<QComboBox*>(this->childAt(mouseEvent->pos())))
                {
                    // 如果点击的是QPushButton或者QComboBox，则不弹出warning弹窗
                    return false;
                }
                else
                {
                    QMessageBox::warning(this, "Warning", "请不要分心哦！");
                    return true;
                }
            }
        }
    }

    return QObject::eventFilter(obj, event);
}


//初始化窗口
void mainClock::initWindow() {

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

    timerLabel->setText("00:15");
    timerLabel->setTime(remainingTime);
    timerLabel->setStyleSheet("font-size: 36px; color: #800000;");


    connect(pauseButton, &QPushButton::clicked, this, &mainClock::togglePausePlay);
    connect(mainTimer, &QTimer::timeout, this, &mainClock::updateTimer);
    connect(pauseTimer, &QTimer::timeout, this, &mainClock::updatePauseTimer);
    connect(ui->exitButton, &QPushButton::clicked, this, &mainClock::onBackClicked);
    connect(ui->MusicBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index) {
                QString choice = ui->MusicBox->itemText(index);
                selectMusic(choice);
            });
}

void mainClock::togglePausePlay() {
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

void mainClock::updateTimer() {

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
        remainingTime = 1500;
        showPauseMessageBox();
    }
}

void mainClock::updatePauseTimer() {
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
            isFinished=false;
            showFailureMessageBox();
        } else {
            nextClicked();
        }
    }
}

void mainClock::nextClicked(){
    if (++completedCycles >= num)
    {
        emit returntoClockyes();
    }
    else
    {
        remainingTime = 1500; // 重置时间为25分钟
        timerLabel->setText("25:00");
        remainingPauseTime = 300;
        rest = 0; // Reset rest status
        resumeMainTimer();
    }
}

void mainClock::resumeMainTimer() {
    mainTimer->start(1000);
    isPaused = false;
    pauseButton->setText("||");
}

void mainClock::showPauseMessageBox() {
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
        connect(continueButton, &QPushButton::clicked, this, &mainClock::onContinueClicked);
    }

    updatePauseMessageBoxText();
    pauseTimer->start(1000);
    pauseMessageBox->show();
}

void mainClock::updatePauseMessageBoxText() {
    if (pauseMessageBox) {
        if (rest == 0) {
            pauseMessageBox->setText(QString("暂停倒计时: %1:%2").arg(remainingPauseTime / 60, 2, 10, QChar('0')).arg(remainingPauseTime % 60, 2, 10, QChar('0')));
        } else {
            pauseMessageBox->setText(QString("出去走一走吧！\n休息倒计时: %1:%2").arg(remainingPauseTime / 60, 2, 10, QChar('0')).arg(remainingPauseTime % 60, 2, 10, QChar('0')));
        }
    }
}

void mainClock::showFailureMessageBox() {
    QMessageBox *failureMessageBox = new QMessageBox(this);
    failureMessageBox->setFixedSize(2400, 2400);
    failureMessageBox->setWindowTitle("专注失败");
    failureMessageBox->setText("暂停时间结束，番茄爆炸啦！请选择你接下下来的操作");

    QPushButton *restartButton = new QPushButton("重新开始", failureMessageBox);
    failureMessageBox->addButton(restartButton, QMessageBox::AcceptRole);

    QPushButton *backButton = new QPushButton("回到上一个界面", failureMessageBox);
    failureMessageBox->addButton(backButton, QMessageBox::RejectRole);

    failureMessageBox->setStandardButtons(QMessageBox::NoButton);
    failureMessageBox->setWindowFlags(failureMessageBox->windowFlags() & ~Qt::WindowCloseButtonHint);

    connect(restartButton, &QPushButton::clicked, this, &mainClock::onRestartClicked);
    connect(backButton, &QPushButton::clicked, this, &mainClock::onBackClicked);

    failureMessageBox->exec();
}

void mainClock::onContinueClicked() {
    if (pauseMessageBox) {
        pauseMessageBox->close();
        pauseMessageBox = nullptr;
    }
    pauseTimer->stop();
    if(rest==0) resumeMainTimer();
    else{
        nextClicked();
    }
}

void mainClock::onRestartClicked() {

    remainingTime = 1500; // 重置时间为25分钟
    timerLabel->setText("25:00");
    remainingPauseTime = 300;
    rest = 0; // Reset rest status
    resumeMainTimer();

}

void mainClock::selectMusic(QString choice){
    if(choice == "林中细雨"){
        Music = 1;
    }
    else if(choice == "巴黎咖啡馆"){
        Music = 2;
    }
    else if(choice == "沙滩海浪"){
        Music = 3;
    }
    else{
        Music = 0;
    }
    playMusic();
};


void mainClock::playMusic(){
    musicPlayer->stop();
    musicPlayer->setAudioOutput(audioOutput);
    switch (Music) {
    case 1:
        musicPlayer->setSource(QUrl(Music1));
        audioOutput->setVolume(30);
        musicPlayer->setLoops(QMediaPlayer::Infinite);
        musicPlayer->play();
        break;
    case 2:
        if (isMusic2 == 1) {
            musicPlayer->setSource(QUrl(Music2));
            audioOutput->setVolume(30);
            musicPlayer->setLoops(QMediaPlayer::Infinite);
            musicPlayer->play();
        } else {
            QMessageBox::warning(nullptr, "Warning", "您还未拥有该背景音,请获取更多番茄解锁成就！");
        }
        break;
    case 3:
        if (isMusic3 == 1) {
            musicPlayer->setSource(QUrl(Music3));
            audioOutput->setVolume(30);
            musicPlayer->setLoops(QMediaPlayer::Infinite);
            musicPlayer->play();
        } else {
            QMessageBox::warning(nullptr, "Warning", "您还未拥有该背景音，请获取更多番茄解锁成就！");
        }
        break;
    default:
        break;
    }
}

void mainClock::onBackClicked() {
    emit returntoClockno();
}




