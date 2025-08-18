#ifndef GUI_GAMEDATA_H
#define GUI_GAMEDATA_H

#include <QObject>
namespace GUI {


class GameData : public QObject
{
    Q_OBJECT
public:
    explicit GameData(QObject *parent = nullptr);
    void setMoveMade();
    std::string lastKingSquareName;

signals:
    void moveMadeChanged();

private:

};

}
#endif // GUI_GAMEDATA_H
