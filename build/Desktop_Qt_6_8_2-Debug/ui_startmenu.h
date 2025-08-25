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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartMenu
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page_Start;
    QGridLayout *gridLayout;
    QFrame *frame_2;
    QGridLayout *gridLayout_7;
    QSpacerItem *horizontalSpacer_17;
    QSpacerItem *verticalSpacer_41;
    QSpacerItem *verticalSpacer_42;
    QVBoxLayout *verticalLayout_7;
    QPushButton *pushButton_start;
    QPushButton *pushButton_options;
    QPushButton *pushButton_button;
    QSpacerItem *verticalSpacer_43;
    QSpacerItem *verticalSpacer_44;
    QSpacerItem *verticalSpacer_45;
    QSpacerItem *verticalSpacer_46;
    QSpacerItem *horizontalSpacer_18;
    QSpacerItem *verticalSpacer_47;
    QSpacerItem *horizontalSpacer_19;
    QSpacerItem *verticalSpacer_48;
    QFrame *frame_7;
    QWidget *page_options;
    QGridLayout *gridLayout_8;
    QSpacerItem *horizontalSpacer_20;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QLabel *label;
    QSlider *horizontalSlider;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_49;
    QSpacerItem *verticalSpacer_50;

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
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        page_Start = new QWidget();
        page_Start->setObjectName("page_Start");
        gridLayout = new QGridLayout(page_Start);
        gridLayout->setObjectName("gridLayout");
        frame_2 = new QFrame(page_Start);
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
        gridLayout_7 = new QGridLayout(frame_2);
        gridLayout_7->setObjectName("gridLayout_7");
        horizontalSpacer_17 = new QSpacerItem(200, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_17, 1, 2, 1, 1);

        verticalSpacer_41 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_7->addItem(verticalSpacer_41, 0, 1, 1, 1);

        verticalSpacer_42 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_7->addItem(verticalSpacer_42, 2, 4, 1, 1);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        pushButton_start = new QPushButton(frame_2);
        pushButton_start->setObjectName("pushButton_start");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_start->sizePolicy().hasHeightForWidth());
        pushButton_start->setSizePolicy(sizePolicy1);
        pushButton_start->setMaximumSize(QSize(400, 125));
        QFont font;
        font.setFamilies({QString::fromUtf8("CARDOT")});
        font.setPointSize(40);
        pushButton_start->setFont(font);
        pushButton_start->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        verticalLayout_7->addWidget(pushButton_start);

        pushButton_options = new QPushButton(frame_2);
        pushButton_options->setObjectName("pushButton_options");
        pushButton_options->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        verticalLayout_7->addWidget(pushButton_options);

        pushButton_button = new QPushButton(frame_2);
        pushButton_button->setObjectName("pushButton_button");
        sizePolicy1.setHeightForWidth(pushButton_button->sizePolicy().hasHeightForWidth());
        pushButton_button->setSizePolicy(sizePolicy1);
        pushButton_button->setMaximumSize(QSize(400, 125));
        pushButton_button->setFont(font);
        pushButton_button->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        verticalLayout_7->addWidget(pushButton_button);


        gridLayout_7->addLayout(verticalLayout_7, 1, 1, 1, 1);

        verticalSpacer_43 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_7->addItem(verticalSpacer_43, 0, 3, 1, 1);

        verticalSpacer_44 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_7->addItem(verticalSpacer_44, 0, 0, 1, 1);

        verticalSpacer_45 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_7->addItem(verticalSpacer_45, 0, 4, 1, 1);

        verticalSpacer_46 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_7->addItem(verticalSpacer_46, 2, 0, 1, 1);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_18, 1, 4, 1, 1);

        verticalSpacer_47 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_7->addItem(verticalSpacer_47, 2, 3, 1, 1);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_19, 1, 0, 1, 1);

        verticalSpacer_48 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_7->addItem(verticalSpacer_48, 2, 1, 1, 1);

        frame_7 = new QFrame(frame_2);
        frame_7->setObjectName("frame_7");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frame_7->sizePolicy().hasHeightForWidth());
        frame_7->setSizePolicy(sizePolicy2);
        frame_7->setMinimumSize(QSize(323, 522));
        frame_7->setStyleSheet(QString::fromUtf8("\n"
"#frame_7 {\n"
"	border: none;\n"
"	background-color: #151515;\n"
"	background-repeat: no-repeat;\n"
"	background-position: center;\n"
"    background-image: url(:/images/img/startmenubackground.png);\n"
"	\n"
"}\n"
"\n"
""));
        frame_7->setFrameShape(QFrame::Shape::StyledPanel);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);

        gridLayout_7->addWidget(frame_7, 1, 3, 1, 1);


        gridLayout->addWidget(frame_2, 0, 0, 1, 1);

        stackedWidget->addWidget(page_Start);
        page_options = new QWidget();
        page_options->setObjectName("page_options");
        gridLayout_8 = new QGridLayout(page_options);
        gridLayout_8->setObjectName("gridLayout_8");
        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_20, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        checkBox = new QCheckBox(page_options);
        checkBox->setObjectName("checkBox");

        verticalLayout->addWidget(checkBox);

        checkBox_2 = new QCheckBox(page_options);
        checkBox_2->setObjectName("checkBox_2");

        verticalLayout->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(page_options);
        checkBox_3->setObjectName("checkBox_3");

        verticalLayout->addWidget(checkBox_3);

        checkBox_4 = new QCheckBox(page_options);
        checkBox_4->setObjectName("checkBox_4");

        verticalLayout->addWidget(checkBox_4);

        label = new QLabel(page_options);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        horizontalSlider = new QSlider(page_options);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setOrientation(Qt::Orientation::Horizontal);

        verticalLayout->addWidget(horizontalSlider);

        comboBox = new QComboBox(page_options);
        comboBox->setObjectName("comboBox");

        verticalLayout->addWidget(comboBox);

        pushButton = new QPushButton(page_options);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);


        gridLayout_8->addLayout(verticalLayout, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_8->addItem(horizontalSpacer, 1, 2, 1, 1);

        verticalSpacer_49 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_8->addItem(verticalSpacer_49, 0, 1, 1, 1);

        verticalSpacer_50 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_8->addItem(verticalSpacer_50, 2, 1, 1, 1);

        stackedWidget->addWidget(page_options);

        horizontalLayout->addWidget(stackedWidget);

        StartMenu->setCentralWidget(centralwidget);

        retranslateUi(StartMenu);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(StartMenu);
    } // setupUi

    void retranslateUi(QMainWindow *StartMenu)
    {
        StartMenu->setWindowTitle(QCoreApplication::translate("StartMenu", "MainWindow", nullptr));
        pushButton_start->setText(QCoreApplication::translate("StartMenu", " Start game ", nullptr));
        pushButton_options->setText(QCoreApplication::translate("StartMenu", "Options", nullptr));
        pushButton_button->setText(QCoreApplication::translate("StartMenu", "Tutorial", nullptr));
        checkBox->setText(QCoreApplication::translate("StartMenu", "Rotate after move", nullptr));
        checkBox_2->setText(QCoreApplication::translate("StartMenu", "Promote always to queen", nullptr));
        checkBox_3->setText(QCoreApplication::translate("StartMenu", "Move hits", nullptr));
        checkBox_4->setText(QCoreApplication::translate("StartMenu", "Hide board numeration", nullptr));
        label->setText(QCoreApplication::translate("StartMenu", "Sound Volume", nullptr));
        pushButton->setText(QCoreApplication::translate("StartMenu", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartMenu: public Ui_StartMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTMENU_H
