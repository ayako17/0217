/********************************************************************************
** Form generated from reading UI file 'Register.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QPushButton *yes;
    QPushButton *return_2;
    QTextEdit *textEditAgreement;

    void setupUi(QWidget *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName("Register");
        Register->setEnabled(true);
        Register->resize(800, 800);
        label = new QLabel(Register);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 280, 60, 30));
        QFont font;
        font.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font.setPointSize(18);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(Register);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 330, 60, 30));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(Register);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(60, 380, 200, 30));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);
        lineEdit = new QLineEdit(Register);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(260, 280, 300, 30));
        lineEdit_2 = new QLineEdit(Register);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setEnabled(true);
        lineEdit_2->setGeometry(QRect(260, 330, 300, 30));
        lineEdit_2->setAutoFillBackground(false);
        lineEdit_2->setEchoMode(QLineEdit::Password);
        lineEdit_3 = new QLineEdit(Register);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(260, 380, 300, 30));
        lineEdit_3->setEchoMode(QLineEdit::Password);
        yes = new QPushButton(Register);
        yes->setObjectName("yes");
        yes->setGeometry(QRect(360, 470, 120, 60));
        QFont font1;
        font1.setPointSize(20);
        yes->setFont(font1);
        return_2 = new QPushButton(Register);
        return_2->setObjectName("return_2");
        return_2->setGeometry(QRect(30, 10, 100, 50));
        textEditAgreement = new QTextEdit(Register);
        textEditAgreement->setObjectName("textEditAgreement");
        textEditAgreement->setGeometry(QRect(210, 110, 400, 150));

        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QWidget *Register)
    {
        Register->setWindowTitle(QCoreApplication::translate("Register", "Form", nullptr));
        label->setText(QCoreApplication::translate("Register", "\350\264\246\345\217\267", nullptr));
        label_2->setText(QCoreApplication::translate("Register", "\345\257\206\347\240\201", nullptr));
        label_3->setText(QCoreApplication::translate("Register", "\345\206\215\346\254\241\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        yes->setText(QCoreApplication::translate("Register", "\347\241\256\350\256\244", nullptr));
        return_2->setText(QCoreApplication::translate("Register", "\350\277\224\345\233\236", nullptr));
        textEditAgreement->setHtml(QCoreApplication::translate("Register", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:700;\">\347\224\250\346\210\267\346\263\250\345\206\214\351\241\273\347\237\245</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">1.\346\202\250\350\276\223\345\205\245\347\232\204\350\264\246\345\217\267\351\234"
                        "\200\344\270\272\346\234\254\344\272\272\346\211\213\346\234\272\345\217\267\347\240\201\357\274\214\347\224\261\345\215\201\344\270\200\344\275\215\346\234\211\346\225\210\346\225\260\345\255\227\346\236\204\346\210\220</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">2.\346\202\250\346\211\200\350\256\276\347\275\256\347\232\204\350\264\246\346\210\267\345\257\206\347\240\201\344\270\215\345\276\227\350\266\205\350\277\20715\344\270\252\345\255\227\347\254\246\357\274\210\345\257\206\347\240\201\345\217\257\345\214\205\345\220\253\346\225\260\345\255\227\343\200\201\345\244\247\345\260\217\345\206\231\345\255\227\346\257\215\343\200\201\345\255\227\347\254\246\357\274\211</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
