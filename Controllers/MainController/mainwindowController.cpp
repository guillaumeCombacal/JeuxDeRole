#include "mainWindowController.h"
#include "loggerfile.h"
#include "FrameBufferObject_OpenGL.h"
#include "BattleMapRender.h"
#include "OpenGlRenderSingleton.h"

#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include <QWidget>
#include <QQuickView>
#include <QQmlContext>

MainWindowController::MainWindowController(QApplication* app):
    m_desktopWidget(NULL),
    m_mainWindow (NULL),
    m_viewQML(NULL),
    m_pApp(app)
{

    // Example Logger
    //LoggerFile::write(Q_FUNC_INFO, "yoloTest");// logger;

    // Lancement de l'application
    /*m_pWorldMapController = new WorldMapController();
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
    */


    // ************************** LANCEMENT DE LA VUE QML ************************************

    // Get the size of the user's screen
    //m_desktopWidget = QApplication::desktop();
    //int width  = m_desktopWidget->screenGeometry().width();
    //int height = m_desktopWidget->screenGeometry().height();

    // Create the Main Window containing all the QML app
    m_mainWindow = new QWidget();

    // Init the Main Window Size
    //m_mainWindow->setFixedWidth(100);
    //m_mainWindow->setFixedHeight(100);

    // Useless ???
    //m_layoutMainWindow = new QVBoxLayout();

    // Interaction QML
    //Anchor anchor;
    //qmlRegisterType<Anchor>("classAnchor", 1, 0, "Anchor");

    // Init the QML view
    m_viewQML = new QQuickView();
    m_mainWindow = QWidget::createWindowContainer(m_viewQML);




    //m_mainWindow->setMinimumSize(width / 2, height / 2);
    //m_mainWindow->setMaximumSize(width, height);

    // Integration composant OpenGL
    // TODO Implementer une communication avec le QML pour savoir quoi générer dans le rendu
    qmlRegisterType<FrameBufferObject_OpenGL>("FrameBufferObject_OpenGL", 1, 0, "OpenGLView");

    // Initialisation des données - à partir du fichier de sauvegarde
    //m_battleMapData.loadDataBattleMap();
    _loadGameData();

    // Initialisation de la classe FrameBufferObject_OpenGL
    OpenGlRenderSingleton::getInstance()->setBattleMapData(&m_battleMapData);

    #ifdef QT_DEBUG
        m_viewQML->rootContext()->setContextProperty("ressourcesDirPath", QGuiApplication::applicationDirPath() + "/../../JeuDeRole");
    #else// Release Mode
        m_viewQML->rootContext()->setContextProperty("ressourcesDirPath", QGuiApplication::applicationDirPath());
    #endif

    // Loading the Main Parent QML Component
    m_viewQML->setSource(QUrl("qrc:/QML/MainWindow.qml"));

    // Signal to quit application
    QObject::connect((QObject*)m_viewQML->rootContext()->engine(), SIGNAL(quit()), this, SLOT(onQuitQMLApplication()));

    //m_viewQML->showFullScreen();

    // Useless ???
    //m_pLayoutWorldMapWidget->addWidget(container);

    //anchor.setProperty("color", QVariant::fromValue(Qt::red));

    // Useless
    //this->setLayout(m_pLayoutWorldMapWidget);



    // Show the view on full screen
    m_mainWindow->showFullScreen();


}

MainWindowController::~MainWindowController()
{
    /*if(m_pWorldMapController != NULL)
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
    }*/

    // *********** QML ************
    if(m_desktopWidget != NULL)
    {
        delete m_desktopWidget;
        m_desktopWidget = NULL;
    }
    if(m_viewQML != NULL)
    {
        delete m_viewQML;
        m_viewQML = NULL;
    }
    if(m_mainWindow != NULL)
    {
        delete m_mainWindow;
        m_mainWindow = NULL;
    }


}


// Callback when you push the QML close button
// Saving data in JSON file
void MainWindowController::onQuitQMLApplication()
{
    qDebug()<<"close the QML application";

    _saveGameData();

    m_pApp->quit();
}


void MainWindowController::_saveGameData()
{
    // Sauvegarde des données
    QFile saveFile(QStringLiteral("save.json"));
    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
    }
    QJsonObject gameObject;
    m_battleMapData.saveDataBattleMap(gameObject);

    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());
}

void MainWindowController::_loadGameData()
{
    // Load data by reading the file
//    QFile loadFile( QStringLiteral("save.json"));

//    if (!loadFile.open(QIODevice::ReadOnly)) {
//        qWarning("Couldn't open save file.");
//        //return false;
//    }
//    QByteArray data = loadFile.readAll();
//    QJsonDocument loadDoc(QJsonDocument::fromJson(data));

//    m_battleMapData.loadDataBattleMap(loadDoc.object());


    // Load data by generation
    m_battleMapData.generateMapData();
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

