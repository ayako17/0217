#include "mainwindow.h"
#include <QScreen>
#include <QApplication>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlError>
#include<QSqlDatabase>
#include <QApplication>
#include <QFontDatabase>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    int fontId = QFontDatabase::addApplicationFont(QStringLiteral(":/mingkai.ttf"));
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    if (fontFamilies.size() > 0)
    {
        QFont font;
        font.setFamily(fontFamilies[0]);//设置全局字体
        a.setFont(font);
    }
    QSqlDatabase db;


    MainWindow w;
    w.show();

    db.close();
    return a.exec();
}
