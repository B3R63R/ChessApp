#ifndef GUI_MOVEINDICATOR_H
#define GUI_MOVEINDICATOR_H

#include <QPushButton>
#include <QWidget>

namespace GUI {

class  MoveIndicator: public QPushButton
{
    Q_OBJECT
public:
    explicit MoveIndicator(QWidget *parent = nullptr);
};

}
#endif // GUI_MOVEINDICATOR_H
