#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include "Sign_in.h"
#include "Register.h"

#include <QIcon>
#include <QApplication>
#include <QString>
#include <QScreen>
#include <QGuiApplication>
#include <QPushButton>
#include <memory> // 包含智能指针的头文件

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sign_in(nullptr)
    , register_(nullptr)
{
    ui->setupUi(this);
    initWindow();

    //将登陆界面按钮与登陆界面连接
    connect(ui->sign_in_button, &QPushButton::clicked, this, &MainWindow::on_sign_in_clicked);
    connect(ui->register_button, &QPushButton::clicked, this, &MainWindow::on_register_clicked);
}

MainWindow::~MainWindow()
{
    // 自动释放资源，无需手动 delete
}

void MainWindow::initWindow() {
    // 获取屏幕大小
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int width = screenGeometry.width();
    int height = screenGeometry.height();

    // 设置窗口大小为屏幕大小
    setGeometry(0, 0, width, height);

    // 设置窗口的标题
    setWindowTitle(TITLE);

    // 设置窗口的图标
    setWindowIcon(QIcon(ICON));

    // 调用 update 函数，强制窗口重绘，确保背景被正确加载和显示
    update();
}

void MainWindow::on_sign_in_clicked() {
    // 使用智能指针管理 sign_in 对象
    if (!sign_in) {
        sign_in = std::make_unique<Sign_in>(this);
        connect(sign_in.get(), &Sign_in::returnToMain, this, &MainWindow::on_return_to_main);
    }
    sign_in->show();

    ui->sign_in_button->hide();
    ui->register_button->hide();
}

void MainWindow::on_register_clicked() {
    // 使用智能指针管理 register_ 对象
    if (!register_) {
        register_ = std::make_unique<Register>(this);
        connect(register_.get(), &Register::returnToMain, this, &MainWindow::on_return_to_main);
    }
    register_->show();

    ui->sign_in_button->hide();
    ui->register_button->hide();
}

void MainWindow::on_return_to_main() {
    ui->sign_in_button->show();
    ui->register_button->show();
    update();
}


