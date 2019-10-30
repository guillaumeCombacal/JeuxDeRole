#ifndef INTERFACE_QML_H
#define INTERFACE_QML_H

#include <QObject>
#include <QDebug>
#include <QJSValue>

class MainWindowController;

enum KeyValue
{
    ENTER = 0,
    BACK_SPACE,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

enum ViewType
{
    WORLD_MAP = 0,
    BATTLE_MAP,
    HERO_MENU,
    QUEST_MENU
};

// Class to handle the communication between C++ and QML
class InterfaceQML : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(type name READ name WRITE setName NOTIFY nameChanged)

private:
    MainWindowController* m_pMainWindowController;

public:
    // Note : MainWindowController* is handled by mainWindowController
    InterfaceQML(MainWindowController* i_pMainWindowController);
    ~InterfaceQML();

    Q_INVOKABLE void eventKeyboardFromQML(QJSValue keyValue);
    Q_INVOKABLE void changeViewType(QJSValue keyValue);
};

#endif // INTERFACE_QML_H
