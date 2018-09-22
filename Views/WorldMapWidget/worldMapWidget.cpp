#include "worldMapWidget.h"

#include "QDebug"

#include <QQuickView>
#include <QQmlContext>
#include <QGuiApplication>
#include <QDesktopWidget>
#include <QApplication>

WorldMapWidget::WorldMapWidget(QWidget *parent) : QWidget(parent),
m_pLayoutWorldMapWidget(NULL)
{

    // Get the size of the user's screen
    QDesktopWidget *desktopWidget = QApplication::desktop();
    int width  = desktopWidget->screenGeometry().width();
    int height = desktopWidget->screenGeometry().height();

    qDebug()<<"widthDesktop = "<<width;
    qDebug()<<"heightDesktop = "<<height;

    //this->setFixedWidth(1300);
    //this->setFixedHeight(600);

    this->setFixedWidth(width - 18);
    this->setFixedHeight(height - 140);

    m_pLayoutWorldMapWidget = new QVBoxLayout();

    // Interaction QML
    //Anchor anchor;
    //qmlRegisterType<Anchor>("classAnchor", 1, 0, "Anchor");

    QQuickView *view = new QQuickView();
    QWidget *container = QWidget::createWindowContainer(view, this);
    container->setMinimumSize(this->width(), this->height());
    container->setMaximumSize(this->width(), this->height());

    #ifdef QT_DEBUG
        view->rootContext()->setContextProperty("ressourcesDirPath", QGuiApplication::applicationDirPath() + "/../../JeuDeRole");
    #else// Release Mode
        view->rootContext()->setContextProperty("ressourcesDirPath", QGuiApplication::applicationDirPath());
    #endif

    view->setSource(QUrl("qrc:/QML/WorldMap/WorldMap.qml")); // Fetch this url by right clicking on your resource file.

    m_pLayoutWorldMapWidget->addWidget(container);

    //anchor.setProperty("color", QVariant::fromValue(Qt::red));

    this->setLayout(m_pLayoutWorldMapWidget);

}

/*WorldMapWidget::~WorldMapWidget()
{
    if(m_pLayoutWorldMapWidget != NULL)
    {
        delete m_pLayoutWorldMapWidget;
    }
}*/
