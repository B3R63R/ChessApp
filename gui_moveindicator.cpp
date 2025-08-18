#include "gui_moveindicator.h"
#include "gui_moveindicator.h"

GUI::MoveIndicator::MoveIndicator(QWidget *parent)
    : QPushButton(parent)
{
    this->setFixedSize(30, 30);
    this->setStyleSheet("border: 2px thick rgba(94, 87, 87, 0.5); border-radius: 15px; background-color: rgba(64, 55, 55, 0.5);");
}

