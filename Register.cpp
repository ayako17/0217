#include "Register.h"
#include "ui_Register.h"
#include "config.h"
#include <QRegularExpression>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    setWindowTitle("注册");
    setWindowIcon(QIcon(ICON));

    // 初始化时禁用输入字段
    enableInputFields(false);

    if (parent)
    {
        parent->installEventFilter(this);
    }

    connect(ui->yes, &QPushButton::clicked, this, &Register::on_yes_clicked);
    connect(ui->return_2, &QPushButton::clicked, this, &Register::on_return_button_clicked);

    //显示用户注册协议
    showAgreement();
}

bool Register::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == parent())
    {
        if (event->type() == QEvent::Move)
        {
            // 处理窗口移动事件
            QWidget *parentWidget = qobject_cast<QWidget *>(parent());
            if (parentWidget)
            {
                QRect parentGeometry = parentWidget->geometry();
                int x = parentGeometry.x() + (parentGeometry.width() - width()) / 2;
                int y = parentGeometry.y() + (parentGeometry.height() - height()) / 2;
                move(x, y);  // 移动窗口以保持居中
            }
        }
    }

    return QWidget::eventFilter(obj, event);  // 返回事件处理结果
}

void Register::showEvent(QShowEvent *event)
{
    // 显示事件处理
    QWidget::showEvent(event);

    // 确保窗口在父窗口居中
    if (parentWidget())
    {
        QRect parentGeometry = parentWidget()->geometry();
        int x = parentGeometry.x() + (parentGeometry.width() - width()) / 2;
        int y = parentGeometry.y() + (parentGeometry.height() - height()) / 2;
        move(x, y);  // 调整位置以居中
    }
}

//新增
bool Register::validateAccount()
{ QString account = ui->lineEdit->text(); // 获取账号输入框的内容

    // 验证账号是否为11位数字
    QRegularExpression re("\\d{11}");
    QRegularExpressionMatch match = re.match(account);
    if (!match.hasMatch())
    {
        QMessageBox::warning(this, "输入错误", "账号必须为11位数字构成的手机号码！", QMessageBox::Ok);
        return false;
    }
    return true;
}

//新增
bool Register::validatePasswords()
{
    QString password1 = ui->lineEdit_2->text();
    QString password2 = ui->lineEdit_3->text();

    if (password1 != password2)
    {
        QMessageBox::warning(this, "输入错误", "两次输入的密码不一致！", QMessageBox::Ok);
        return false;
    }

    if (password1.length() > 15)
    {
        QMessageBox::warning(this, "输入错误", "密码长度不能超过15个字符！", QMessageBox::Ok);
        return false;
    }

    QRegularExpression re("^[a-zA-Z0-9]*$");
    QRegularExpressionMatch match = re.match(password1);
    if (!match.hasMatch())
    {
        QMessageBox::warning(this, "输入错误", "密码只能包含字母和数字！", QMessageBox::Ok);
        return false;
    }

    return true;
}

//新增
void Register::showAgreement()
{
    QMessageBox::information(this, "用户注册协议",
                             "1.您输入的账号需为本人手机号码，由十一位有效数字构成"
                             "2.您所设置的账户密码不得超过15个字符（密码可包含数字、大小写字母、字符）",
                             QMessageBox::Ok);
    // 启用输入字段
    enableInputFields(true);
}

//新增
void Register::enableInputFields(bool enable)
{
    ui->lineEdit->setEnabled(enable);
    ui->lineEdit_2->setEnabled(enable);
    ui->lineEdit_3->setEnabled(enable);
    ui->yes->setEnabled(enable);
}
void Register::on_return_button_clicked() {
    emit returnToMain(); // 发射自定义信号
    close(); // 关闭注册界面
}

void Register::on_yes_clicked()
{
    if (validateAccount() && validatePasswords())
    {
        emit returnToMain();
        close();
    }
}

Register::~Register()
{
    delete ui;
}
