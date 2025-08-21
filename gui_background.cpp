#include "gui_background.h"
#include <QGraphicsScene>
#include <QPainter>

Background::Background () {

}

void Background::drawBackground(QPainter *painter, const QRectF &rect) {
    painter->drawImage(rect, QImage(":/backgrounds/backgrounds/startmenubackground.svg"));
}
