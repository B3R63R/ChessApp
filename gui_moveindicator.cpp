#include "gui_moveindicator.h"
#include "gui_moveindicator.h"

#include <QBoxLayout>
GUI::MoveIndicator::MoveIndicator(QWidget *parent)
    : QPushButton(parent)
{   //Fill whole area of parent
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //make invisible
    this->setFlat(true);
    //Remove spherical border
    this->setStyleSheet("background-color: transparent; border: none;");

    //Craete visible circle
    visualCircle = new QFrame(this);
    visualCircle->setFixedSize(30, 30);
    visualCircle->setStyleSheet("border: 2px thick rgba(94, 87, 87, 0.5); border-radius: 15px; background-color: rgba(64, 55, 55, 0.5);");

    //Dont capture click event
    visualCircle->setAttribute(Qt::WA_TransparentForMouseEvents);

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(visualCircle);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);

}

