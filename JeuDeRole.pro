#-------------------------------------------------
#
# Project created by QtCreator 2018-03-18T11:50:28
#
#-------------------------------------------------

QT       += core gui xml quick qml svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JeuDeRole
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

RESOURCES += jeuDeRole.qrc

DISTFILES +=


# For icon Appli
RC_FILE = $$PWD/Ressources/ressource.rc


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=  $$PWD/Controllers/MainController\
                $$PWD/Controllers/BattleController\
                $$PWD/Controllers/HeroController\
                $$PWD/Controllers/QuestController\
                $$PWD/Controllers/WorldMapController\
                $$PWD/Controllers/Parser\
                $$PWD/Controllers/Logger\
                $$PWD/Controllers/Communication\
                $$PWD/Views/MainWindowWidget\
                $$PWD/Views/BattleWidget\
                $$PWD/Views/HeroWidget\
                $$PWD/Views/HeroWidgetEdit\
                $$PWD/Views/QuestWidget\
                $$PWD/Views/WorldMapWidget\
                $$PWD/Model\
                $$PWD/Data\
                $$PWD/OpenGL

SOURCES +=\
    JeuDeRole.cpp \
    Views/MainWindowWidget/mainWidget.cpp \
    Views/MainWindowWidget/mainWindow.cpp \
    Views/QuestWidget/questWidget.cpp \
    Views/WorldMapWidget/worldMapWidget.cpp \
    Views/MainWindowWidget/ongletWidget.cpp \
    Controllers/BattleController/battleController.cpp \
    Controllers/MainController/mainWindowController.cpp \
    Controllers/QuestController/questController.cpp \
    Controllers/WorldMapController/worldMapController.cpp \
    Controllers/Parser/parserXml.cpp \
    Controllers/Logger/loggerfile.cpp \
    Views/BattleWidget/battleWidget.cpp \
    Controllers/Communication/interfaceQML.cpp \
    OpenGL/FrameBufferRenderer_OpenGL.cpp \
    OpenGL/FrameBufferObject_OpenGL.cpp \
    OpenGL/BattleMapRender.cpp \
    Model/BattleMapData.cpp \
    OpenGL/OpenGlRenderSingleton.cpp \
    Model/Tile.cpp \
    Model/Character.cpp \
    Model/AnimationSprite.cpp \
    Model/Curseur.cpp \
    Model/PathFinding.cpp \
    Data/sharedDataHero.cpp




HEADERS  += \
    Views/MainWindowWidget/mainWidget.h \
    Views/MainWindowWidget/mainWindow.h \
    Views/BattleWidget/battleWidget.h \
    Views/QuestWidget/questWidget.h \
    Views/WorldMapWidget/worldMapWidget.h \
    Views/MainWindowWidget/ongletWidget.h \
    Controllers/MainController\
    Controllers/BattleController/battleController.h \
    Controllers/MainController/mainWindowController.h \
    Controllers/QuestController/questController.h \
    Controllers/WorldMapController/worldMapController.h \
    Controllers/Parser/parserXml.h \
    Data/sharedDataXmlField.h \
    Data/sharedDataHero.h \
    Controllers/Logger/ilogger.h \
    Controllers/Logger/loggerfile.h \
    Controllers/Communication/interfaceQML.h \
    OpenGL/FrameBufferRenderer_OpenGL.h \
    OpenGL/FrameBufferObject_OpenGL.h \
    OpenGL/BattleMapRender.h \
    Model/BattleMapData.h \
    Model/Character.h \
    OpenGL/OpenGlRenderSingleton.h \
    Model/Tile.h \
    Model/AnimationSprite.h \
    Model/Curseur.h \
    Model/PathFinding.h
