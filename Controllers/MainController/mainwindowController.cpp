#include "mainWindowController.h"
#include "loggerfile.h"

#include<QDebug>

MainWindowController::MainWindowController()
{

    //LoggerFile::write(Q_FUNC_INFO, "yoloTest");// logger;

    m_pWorldMapController = new WorldMapController();
    m_pBattleController = new BattleController();
    m_pHeroController = new HeroController();
    m_pQuestController = new QuestController();

    m_pOngletWidget = new OngletWidget();

    QObject::connect(m_pOngletWidget, SIGNAL(sendSwitchWidget(int)), this, SLOT(onSwitchOnglet(int)));
    QObject::connect(m_pHeroController, SIGNAL(sendSwitchHeroEditView()), this, SLOT(onSwitchHeroEditView()));
    QObject::connect(m_pHeroController, SIGNAL(sendSwitchHeroView()), this, SLOT(onSwitchHeroView()));

    m_pMainWidget = new MainWidget(m_pOngletWidget, m_pWorldMapController->getWorldMapWidget(),
                                                    m_pBattleController->getBattleWidget(),
                                                    m_pHeroController->getHeroWidget(),
                                                    m_pHeroController->getHeroWidgetEdit(),
                                                    m_pQuestController->getQuestWidget());

    m_pMainWindow = new MainWindow(m_pMainWidget);

    m_pMainWindow->show();

}

MainWindowController::~MainWindowController()
{
    if(m_pWorldMapController != NULL)
    {
        delete m_pWorldMapController;
    }

    if(m_pBattleController != NULL)
    {
        delete m_pBattleController;
    }

    if(m_pHeroController != NULL)
    {
        delete m_pHeroController;
    }

    if(m_pQuestController != NULL)
    {
        delete m_pQuestController;
    }

    if(m_pMainWidget != NULL)
    {
        delete m_pMainWidget;
    }

    if(m_pMainWindow != NULL)
    {
        delete m_pMainWindow;
    }


}

void MainWindowController::onSwitchOnglet(int idWidget)
{
    switch (idWidget)
    {
    case 0:
        m_pMainWidget->getStackWidget()->setCurrentIndex(0);// World Map View
        break;
    case 1:
        m_pMainWidget->getStackWidget()->setCurrentIndex(1);// Battle View
        break;
    case 2:
        m_pMainWidget->getStackWidget()->setCurrentIndex(2);// Hero View
        break;
    case 3:
        m_pMainWidget->getStackWidget()->setCurrentIndex(4);// Quest View
        break;
    default:
        break;
    }
}

void MainWindowController::onSwitchHeroEditView()
{
    m_pMainWidget->getStackWidget()->setCurrentIndex(3);// World Map View
}

void MainWindowController::onSwitchHeroView()
{
    m_pMainWidget->getStackWidget()->setCurrentIndex(2);// World Map View
}

