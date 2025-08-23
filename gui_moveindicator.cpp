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
    visualCircle->setFixedSize(20, 20);
    visualCircle->setStyleSheet("border-radius: 10px; background-color: rgba(204, 188, 167, 0.5);");

    //Dont capture click event
    visualCircle->setAttribute(Qt::WA_TransparentForMouseEvents);

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(visualCircle);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);

}
