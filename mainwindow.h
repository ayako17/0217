#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QtSql/QSqlDatabase>
class start_task;
class Sign_in;
class Register;
class easyclock;

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

    void initWindow();
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;
    std::unique_ptr<Sign_in> sign_in;
    std::unique_ptr<Register> register_;
    easyclock* Easyclock;


private slots:
    void on_sign_in_clicked();
    void on_register_clicked();
    void on_return_to_main();
    void easy_return_to_main();
    void on_visitor_clicked();
};
#endif // MAINWINDOW_H
