#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QFontDatabase>
#include "Clock.h"



namespace Ui {
class Sign_in;
}

class Sign_in : public QWidget {
    Q_OBJECT

public:
    explicit Sign_in(QWidget *parent = nullptr);
    ~Sign_in();

signals:
    void userLoggedIn(int userId);
    void returnToMain();

protected:
    //bool eventFilter(QObject *obj, QEvent *event) override;
    //void showEvent(QShowEvent *event) override;

private slots:
    void on_return_button_clicked();
    void on_yes_clicked();
    void on_return1_clicked();

private:
    Ui::Sign_in *ui;
    Clock *clock;
    QSqlDatabase db;

    bool validateAccount();
    bool validatePassword();
    int getUserId(const QString &username);
    bool isUserExists(const QString &username, const QString &password);};

#endif // SIGN_IN_H
