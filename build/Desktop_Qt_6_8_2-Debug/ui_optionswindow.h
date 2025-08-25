/********************************************************************************
** Form generated from reading UI file 'optionswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSWINDOW_H
#define UI_OPTIONSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionsWindow
{
public:

    void setupUi(QWidget *OptionsWindow)
    {
        if (OptionsWindow->objectName().isEmpty())
            OptionsWindow->setObjectName("OptionsWindow");
        OptionsWindow->resize(1080, 680);

        retranslateUi(OptionsWindow);

        QMetaObject::connectSlotsByName(OptionsWindow);
    } // setupUi

    void retranslateUi(QWidget *OptionsWindow)
    {
        OptionsWindow->setWindowTitle(QCoreApplication::translate("OptionsWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OptionsWindow: public Ui_OptionsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSWINDOW_H
