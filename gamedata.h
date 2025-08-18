#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QObject>
namespace GUI {


class GameData : public QObject
{
    Q_OBJECT
public:
    explicit GameData(QObject *parent = nullptr);
    void setMoveMade();

signals:
    void moveMadeChanged();

private:

};
}
#endif // GAMEDATA_H
