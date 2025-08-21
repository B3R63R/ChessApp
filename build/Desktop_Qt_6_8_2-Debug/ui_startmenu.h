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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartMenu
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_4;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QPushButton *startButton;
    QPushButton *pushButton;
    QPushButton *startButton_2;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *horizontalSpacer_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *StartMenu)
    {
        if (StartMenu->objectName().isEmpty())
            StartMenu->setObjectName("StartMenu");
        StartMenu->resize(1087, 718);
        centralwidget = new QWidget(StartMenu);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("background-color:  #151515;\n"
""));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setStyleSheet(QString::fromUtf8("color: #151515;\n"
"border: none;"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName("gridLayout_2");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 4, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_7, 0, 0, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_8, 0, 4, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 0, 3, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 2, 3, 1, 1);

        frame = new QFrame(frame_2);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(323, 522));
        frame->setStyleSheet(QString::fromUtf8("\n"
"#frame {\n"
"	border: none;\n"
"	background-color: #151515;\n"
"	background-repeat: no-repeat;\n"
"	background-position: center;\n"
"    background-image: url(:/images/img/startmenubackground.png);\n"
"	\n"
"}\n"
"\n"
""));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);

        gridLayout_2->addWidget(frame, 1, 3, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        startButton = new QPushButton(frame_2);
        startButton->setObjectName("startButton");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy2);
        startButton->setMaximumSize(QSize(400, 125));
        QFont font;
        font.setFamilies({QString::fromUtf8("CARDOT")});
        font.setPointSize(40);
        startButton->setFont(font);
        startButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-family: 'CARDOT';\n"
"    font-size: 40pt;\n"
"    border: none;\n"
"	color: #E0E0E0;\n"
"    background-color: transparent;\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"	padding: 8px 15px; \n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    font-size: 42pt;\n"
"	 color: #FFFFFF;\n"
"	\n"
"	\n"
"}"));

        verticalLayout_2->addWidget(startButton);

        pushButton = new QPushButton(frame_2);
        pushButton->setObjectName("pushButton");
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-family: 'CARDOT';\n"
"    font-size: 40pt;\n"
"    border: none;\n"
"	color: #E0E0E0;\n"
"    background-color: transparent;\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"	padding: 8px 15px; \n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    font-size: 42pt;\n"
"	 color: #FFFFFF;\n"
"}"));

        verticalLayout_2->addWidget(pushButton);

        startButton_2 = new QPushButton(frame_2);
        startButton_2->setObjectName("startButton_2");
        sizePolicy2.setHeightForWidth(startButton_2->sizePolicy().hasHeightForWidth());
        startButton_2->setSizePolicy(sizePolicy2);
        startButton_2->setMaximumSize(QSize(400, 125));
        startButton_2->setFont(font);
        startButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-family: 'CARDOT';\n"
"    font-size: 40pt;\n"
"    border: none;\n"
"	color: #E0E0E0;\n"
"    background-color: transparent;\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"	padding: 8px 15px; \n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    font-size: 42pt;\n"
"	 color: #FFFFFF;\n"
"}"));

        verticalLayout_2->addWidget(startButton_2);


        gridLayout_2->addLayout(verticalLayout_2, 1, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_5, 2, 4, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 2, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 1, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_6, 0, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(200, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 1, 2, 1, 1);


        horizontalLayout->addWidget(frame_2);

        StartMenu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(StartMenu);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1087, 22));
        menubar->setStyleSheet(QString::fromUtf8("background-color:  #151515;"));
        StartMenu->setMenuBar(menubar);
        statusbar = new QStatusBar(StartMenu);
        statusbar->setObjectName("statusbar");
        statusbar->setStyleSheet(QString::fromUtf8("background-color:  #151515;"));
        StartMenu->setStatusBar(statusbar);

        retranslateUi(StartMenu);

        QMetaObject::connectSlotsByName(StartMenu);
    } // setupUi

    void retranslateUi(QMainWindow *StartMenu)
    {
        StartMenu->setWindowTitle(QCoreApplication::translate("StartMenu", "MainWindow", nullptr));
        startButton->setText(QCoreApplication::translate("StartMenu", " Start game ", nullptr));
        pushButton->setText(QCoreApplication::translate("StartMenu", "Options", nullptr));
        startButton_2->setText(QCoreApplication::translate("StartMenu", "Credits", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartMenu: public Ui_StartMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTMENU_H
