#include "mainWindow.h"

MainWindow::MainWindow(MainWidget *mainWidget, QWidget *parent)
    : QMainWindow(parent)
{
/*    m_pXmlDom = new XmlDom();
    std::string fileName;
    fileName = "C:/Users/Yaku/Documents/DeveloppementCode/Project/jeuxDeRole/ParserXML/Data/Hero.xml";
    if(m_pXmlDom->readXmlFile(fileName))
    {
        std::printf("File read !");
    }
*/
    /*if(m_pXmlDom->writeXmlFile(fileName))
    {
        std::printf("File writen !");
    }*/


    // Init Layout
    //m_pMainLayout = new QVBoxLayout();

    // Set the Central Widget
   // m_pMainWidget = new MainWidget();
    m_pMainWidget = mainWidget;

    createMenuBar();
    this->setMenuBar(m_pMenuBar);

    setCentralWidget(m_pMainWidget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::createMenuBar()
{
    // Create The Actions In The Menu
    m_pActLoadingGame = new QAction(tr("&Loading Game State"), this);
    //m_pOpenAct->setShortcuts(QKeySequence::Open);
    //m_pOpenAct->setStatusTip(tr("Open a new file"));
    //connect(m_pOpenAct, SIGNAL(triggered()), this, SLOT(onClickLoadingList()));

    m_pActSavingGame = new QAction(tr("&Saving Game State"), this);

    // Create The Menu Bar
    m_pMenuBar = new QMenuBar;

    // Create the File Menu and add it to the Menu Bar
    m_pFileMenu = new QMenu(tr("&File"), this);
    m_pFileMenu->addAction(m_pActLoadingGame);
    m_pFileMenu->addAction(m_pActSavingGame);
    m_pMenuBar->addMenu(m_pFileMenu);

}
