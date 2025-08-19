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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartMenu
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *startButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *StartMenu)
    {
        if (StartMenu->objectName().isEmpty())
            StartMenu->setObjectName("StartMenu");
        StartMenu->resize(800, 600);
        centralwidget = new QWidget(StartMenu);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName("startButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamilies({QString::fromUtf8("URW Bookman [urw]")});
        startButton->setFont(font);

        horizontalLayout->addWidget(startButton);

        StartMenu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(StartMenu);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        StartMenu->setMenuBar(menubar);
        statusbar = new QStatusBar(StartMenu);
        statusbar->setObjectName("statusbar");
        StartMenu->setStatusBar(statusbar);

        retranslateUi(StartMenu);

        QMetaObject::connectSlotsByName(StartMenu);
    } // setupUi

    void retranslateUi(QMainWindow *StartMenu)
    {
        StartMenu->setWindowTitle(QCoreApplication::translate("StartMenu", "MainWindow", nullptr));
        startButton->setText(QCoreApplication::translate("StartMenu", "Start game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartMenu: public Ui_StartMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTMENU_H
