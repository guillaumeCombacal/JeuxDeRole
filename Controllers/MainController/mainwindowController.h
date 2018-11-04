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

// Forward Declaration
class QDesktopWidget;
class QWidget;
class QQuickView;
class QApplication;

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

    // ************ QML ***********
    QDesktopWidget* m_desktopWidget;
    QWidget*        m_mainWindow;
    QQuickView*     m_viewQML;

    QApplication* m_pApp;

public:
    MainWindowController(QApplication* app);
    ~MainWindowController();

public slots:
    void onSwitchOnglet(int idWidget);
    void onSwitchHeroEditView();
    void onSwitchHeroView();

    // QML
    void onQuitQMLApplication();
};

#endif // MAINWINDOWCONTROLLER_H
