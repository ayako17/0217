#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QDialog>
#include <QWidget>
#include<QIcon>
#include"Clock.h"

namespace Ui{
class Sign_in;
}

class Sign_in: public QWidget {
    Q_OBJECT

public:
    explicit Sign_in(QWidget *parent = nullptr);
    ~Sign_in();

    Clock *clock;

protected:
    // 事件过滤器，用于处理窗口移动事件
    bool eventFilter(QObject *obj, QEvent *event) override;
    // 显示事件处理，用于调整窗口位置
    void showEvent(QShowEvent *event) override;

private:
    Ui::Sign_in *ui; // 指向UI界面的指针

signals:
    void returnToMain();

private slots:
    void on_return_button_clicked();
    void on_yes_clicked();
};

#endif // SIGN_IN_H
