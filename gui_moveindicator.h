#ifndef GUI_MOVEINDICATOR_H
#define GUI_MOVEINDICATOR_H

#include <QPushButton>
#include <QWidget>
#include <QFrame>

namespace GUI {

class  MoveIndicator: public QPushButton
{
    Q_OBJECT
public:
    explicit MoveIndicator(QWidget *parent = nullptr);

private:
    QFrame *visualCircle;
};

}
#endif // GUI_MOVEINDICATOR_H
