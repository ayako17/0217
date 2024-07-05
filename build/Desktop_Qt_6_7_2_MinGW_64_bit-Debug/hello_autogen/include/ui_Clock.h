/********************************************************************************
** Form generated from reading UI file 'Clock.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLOCK_H
#define UI_CLOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Clock
{
public:
    QCheckBox *checkBox;

    void setupUi(QWidget *Clock)
    {
        if (Clock->objectName().isEmpty())
            Clock->setObjectName("Clock");
        Clock->resize(400, 300);
        checkBox = new QCheckBox(Clock);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(70, 150, 241, 91));

        retranslateUi(Clock);

        QMetaObject::connectSlotsByName(Clock);
    } // setupUi

    void retranslateUi(QWidget *Clock)
    {
        Clock->setWindowTitle(QCoreApplication::translate("Clock", "Form", nullptr));
        checkBox->setText(QCoreApplication::translate("Clock", "CheckBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Clock: public Ui_Clock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLOCK_H
