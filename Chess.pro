QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chesslogic.cpp \
    gui_blackpiececlasses.cpp \
    gui_gamedata.cpp \
    gui_moveindicator.cpp \
    gui_piece.cpp \
    gui_whitepiececlasses.cpp \
    main.cpp \
    mainwindow.cpp \
    startmenu.cpp

HEADERS += \
    chesslogic.h \
    gui_blackpiececlasses.h \
    gui_gamedata.h \
    gui_moveindicator.h \
    gui_piece.h \
    gui_whitepiececlasses.h \
    mainwindow.h \
    startmenu.h

FORMS += \
    mainwindow.ui \
    startmenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += resource.qrc
