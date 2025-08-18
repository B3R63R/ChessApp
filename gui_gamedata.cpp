#include "gui_gamedata.h"

GUI::GameData::GameData(QObject *parent)
    : QObject{parent}
{}

void GUI::GameData::setMoveMade() {

    emit moveMadeChanged();
}
