#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
class Sign_in; // 前向声明
class Register; // 前向声明

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initWindow();//初始化窗口

    void signinWindow();//展示登陆界面

    void startTiming();//开始计时

    void endTiming();//结束计时

    void showScene();//显示场景选择

    void closeScene();//关闭场景选择

    void playMusic();//播放音乐

    void showMusic();//显示音乐选择

    void closeMusic();//关闭音乐选择

    void changeScene();//切换场景

    void changeMusic();//切换音乐


private:
    Ui::MainWindow *ui;
    std::unique_ptr<Sign_in> sign_in; // 使用智能指针
    std::unique_ptr<Register> register_; // 使用智能指针


private slots:
    void on_sign_in_clicked();
    void on_register_clicked();
    void on_return_to_main();
};
#endif // MAINWINDOW_H
