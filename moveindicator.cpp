#include "moveindicator.h"
#include "moveindicator.h"
moveIndicator::moveIndicator(QWidget *parent)
    : QPushButton(parent)
{
    this->setFixedSize(30, 30);
    this->setStyleSheet("border: 2px ridge rgba(25, 54, 14, 0.5); border-radius: 15px; background-color: rgba(35, 84, 15, 0.5);");
}

