#include "worldMapWidget.h"

#include "QDebug"

#include <QQuickView>
#include <QQmlContext>
#include <QGuiApplication>

WorldMapWidget::WorldMapWidget(QWidget *parent) : QWidget(parent),
m_pLayoutWorldMapWidget(NULL)
{
    this->setFixedWidth(1200);
    this->setFixedHeight(600);

    m_pLayoutWorldMapWidget = new QVBoxLayout();

    // Interaction QML
    //Anchor anchor;
    //qmlRegisterType<Anchor>("classAnchor", 1, 0, "Anchor");

    QQuickView *view = new QQuickView();
    QWidget *container = QWidget::createWindowContainer(view, this);
    container->setMinimumSize(this->width(), this->height());
    container->setMaximumSize(this->width(), this->height());

    view->rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());

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
