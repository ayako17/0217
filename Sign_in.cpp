#include "Sign_in.h"
#include "ui_Sign_in.h"
#include "config.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QMoveEvent>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include<QtSql/QSqlError>
#include<QtSql/QSqlQuery>

 int currentUserID;


Sign_in::Sign_in(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sign_in),
    clock(nullptr) { // 初始化指针为 nullptr
    // 构造函数，初始化登陆界面
    ui->setupUi(this);

    setWindowTitle("登录");
    setWindowIcon(QIcon(ICON));
    int fontId = QFontDatabase::addApplicationFont(ZITI);
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont myFont(fontFamily);
    myFont.setBold(true);
    ui->Password->setEchoMode(QLineEdit::Password);


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




    if (parent) {
        parent->installEventFilter(this);
    }

    connect(ui->yes, &QPushButton::clicked, this, &Sign_in::on_yes_clicked);
    connect(ui->return_2,&QPushButton::clicked, this, &Sign_in::on_return_button_clicked);

}



bool Sign_in::validateAccount() {
    QString account = ui->Account->text(); // 获取账号输入框的内容

    // 验证账号是否为11位数字
    // QRegularExpression re("\\d{11}");
    // QRegularExpressionMatch match = re.match(account);
    // if (!match.hasMatch()) {
    //     QMessageBox::warning(this, "输入错误", "账号必须为11位数字构成的手机号码！", QMessageBox::Ok);
    //     return false;
    // }
    return true;
}

bool Sign_in::validatePassword() {
    QString password = ui->Password->text(); // 获取密码输入框的内容

    //验证密码是否为不超过15个字符的数字、字母、字符的组合
    QRegularExpression re("^[\\w!@#$%^&*()_+\\-=\\[\\]{};':\"\\\\|,.<>/?]{1,15}$");
    QRegularExpressionMatch match = re.match(password);
    if (!match.hasMatch()) {
        QMessageBox::warning(this, "输入错误", "密码必须是不超过15个字符的数字、字母、字符的组合！请输入正确密码！", QMessageBox::Ok);
        return false;
    }
    return true;
}

int Sign_in::getUserId(const QString &username) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Users WHERE username = :username");
    query.bindValue(":username", username);
    if (!query.exec() || !query.next()) {
        return -1; // User not found
    }
    currentUserID=query.value(0).toInt();
    return query.value(0).toInt();
}

bool Sign_in::isUserExists(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Failed to check user:" << query.lastError().text();
        return false;
    }

    if (query.next() && query.value(0).toInt() == 0) {
        return false;  // 用户不存在
    }

    query.prepare("SELECT COUNT(*) FROM Users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Failed to check user:" << query.lastError().text();
        return false;
    }

    if (query.next() && query.value(0).toInt() > 0) {
        return true;  // 用户名和密码匹配
    }

    return false;  // 密码不匹配
}

void Sign_in::on_yes_clicked()
{
    QString username = ui->Account->text();
    QString password = ui->Password->text();

    if (!validateAccount() || !validatePassword()) {
        return; // 如果账号或密码验证失败，直接返回
    }

    if (!isUserExists(username, password)) {
        QMessageBox::warning(this, "登录失败", "该用户名未注册或密码不正确！");
        ui->Account->clear();
        ui->Password->clear();
        return; // 用户不存在或密码不正确，直接返回
    }

    getUserId(username);

    if (clock == nullptr) {
        clock = new Clock(this); // 创建新的 Clock 对象
        connect(clock, &Clock::return1, this, &Sign_in::on_return1_clicked);
        clock->setAttribute(Qt::WA_DeleteOnClose); // 窗口关闭时自动删除
    }

    ui->yes->hide();
    ui->Account->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->Password->hide();
    ui->return_2->hide();
    clock->show();
}

void Sign_in::on_return1_clicked(){
    ui->yes->show();
    ui->Account->show();
    ui->label->show();
    ui->label_2->show();
    ui->Password->show();
    ui->return_2->show();
}

void Sign_in::on_return_button_clicked() {
    emit returnToMain(); // 发射自定义信号

    close(); // 关闭注册界面
}

Sign_in::~Sign_in() {
    delete ui;
}
