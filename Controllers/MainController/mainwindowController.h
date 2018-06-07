#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include "mainWindow.h"
#include "mainWidget.h"
#include "ongletWidget.h"
#include "worldMapController.h"
#include "battleController.h"
#include "heroController.h"
#include "questController.h"

#include<QObject>

class MainWindowController : public QObject
{
    Q_OBJECT

private:
    MainWindow *m_pMainWindow;
    MainWidget *m_pMainWidget;
    OngletWidget *m_pOngletWidget;

    WorldMapController *m_pWorldMapController;
    BattleController *m_pBattleController;
    HeroController *m_pHeroController;
    QuestController *m_pQuestController;

public:
    MainWindowController();
    ~MainWindowController();

public slots:
    void onSwitchOnglet(int idWidget);
    void onSwitchHeroEditView();
    void onSwitchHeroView();
};

#endif // MAINWINDOWCONTROLLER_H
