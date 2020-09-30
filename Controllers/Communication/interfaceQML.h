#ifndef INTERFACE_QML_H
#define INTERFACE_QML_H

#include <QObject>
#include <QDebug>
#include <QJSValue>

#include "sharedDataHero.h"

class MainWindowController;
class QQuickView;

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

    Q_PROPERTY(bool isCursorOnCharacter READ isCursorOnCharacter NOTIFY cursorOnCharacter)

    Q_PROPERTY(QVariantMap featuresCharacter READ getFeaturesCharacter NOTIFY featuresCharacterChanged)

    Q_PROPERTY(QStringList characterToAddInBattleMap READ getListCharacterToAddInBattleMap)

private:
    MainWindowController* m_pMainWindowController;
    QQuickView* m_pViewQML;

    bool m_bIsOnCharacter;
    Features m_sFeaturesCharacter;
    QStringList m_listCharacterToAddInBattleMap;//ERROR chargement en retard sur le QML

public:
    // Note : MainWindowController* is handled by mainWindowController
    InterfaceQML(MainWindowController* i_pMainWindowController, QQuickView* i_pViewQML);
    ~InterfaceQML();

    bool isCursorOnCharacter()const{return m_bIsOnCharacter;}
    inline void setIsCursorOnCharacter(bool i_bIsOnCharacter){m_bIsOnCharacter=i_bIsOnCharacter; emit cursorOnCharacter();}

    QVariantMap getFeaturesCharacter(){return ComCppQml::featuresToQVariantMap(m_sFeaturesCharacter);}
    inline void setFeaturesCharacter(Features i_sFeaturesCharacter){m_sFeaturesCharacter = i_sFeaturesCharacter; emit featuresCharacterChanged();}

    QStringList getListCharacterToAddInBattleMap(){return m_listCharacterToAddInBattleMap;}
    inline void setListCharacterToAddInBattleMap(QStringList listCharacter){m_listCharacterToAddInBattleMap = listCharacter; emit listCharacterToAddInBattleMapChanged();}


    Q_INVOKABLE void eventKeyboardFromQML(QJSValue keyValue);
    Q_INVOKABLE void changeViewType(QJSValue keyValue);
    Q_INVOKABLE void fightRequest();
    Q_INVOKABLE void orientationRequest();
    Q_INVOKABLE void selectCharacterToAddInBattle(QString nameCharacter);

 signals:
    void cursorOnCharacter();
    void featuresCharacterChanged();
    void listCharacterToAddInBattleMapChanged();
};

#endif // INTERFACE_QML_H
