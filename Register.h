#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include<QMessageBox>

namespace Ui{
class Register;
}

class Register : public QWidget
{
    Q_OBJECT
public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

protected:
    // 事件过滤器，用于处理窗口移动事件
    bool eventFilter(QObject *obj, QEvent *event) override;
    // 显示事件处理，用于调整窗口位置
    void showEvent(QShowEvent *event) override;

private:
    Ui::Register *ui; // 指向UI界面的指针

    bool validateAccount();//账号合法性验证函数
    void showAgreement();//用户协议函数
    bool validatePasswords();  // 验证密码函数
    void enableInputFields(bool enable); // 启用或禁用输入字段

signals:
    void returnToMain();

private slots:
    void on_return_button_clicked();
    void on_yes_clicked();

};

#endif // REGISTER_H
