/********************************************************************************
** Form generated from reading UI file 'startmenu.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTMENU_H
#define UI_STARTMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_startmenu
{
public:
    QPushButton *pushButton;

    void setupUi(QDialog *startmenu)
    {
        if (startmenu->objectName().isEmpty())
            startmenu->setObjectName("startmenu");
        startmenu->resize(749, 488);
        pushButton = new QPushButton(startmenu);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(270, 150, 121, 31));

        retranslateUi(startmenu);

        QMetaObject::connectSlotsByName(startmenu);
    } // setupUi

    void retranslateUi(QDialog *startmenu)
    {
        startmenu->setWindowTitle(QCoreApplication::translate("startmenu", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("startmenu", "Start game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class startmenu: public Ui_startmenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTMENU_H
