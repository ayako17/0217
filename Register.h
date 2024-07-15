#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include<QMessageBox>
#include<QtSql/QSqlDatabase>
#include<QFontDatabase>
namespace Ui{
class Register;
}

class Register : public QWidget
{
    Q_OBJECT
public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();


private:
    Ui::Register *ui; // 指向UI界面的指针
    QSqlDatabase db;  // 数据库连接

    bool validateAccount();//账号合法性验证函数
    void showAgreement();//用户协议函数
    bool validatePasswords();  // 验证密码函数
    void enableInputFields(bool enable); // 启用或禁用输入字段
    bool isUserExists(const QString &username);  // 检查用户是否存在
    void addUserToDatabase(const QString &username, const QString &password);  // 将用户添加到数据库

signals:
    void returnToMain();

private slots:
    void on_return_button_clicked();
    void on_yes_clicked();


};

#endif // REGISTER_H
