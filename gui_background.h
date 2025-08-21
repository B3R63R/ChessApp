#ifndef GUI_BACKGROUND_H
#define GUI_BACKGROUND_H
#include <QGraphicsScene>

class Background : public QGraphicsScene
{
public:
    Background();
    void drawBackground(QPainter *painter, const QRectF &rect);
};

#endif // GUI_BACKGROUND_H
