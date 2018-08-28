#include "battleWidget.h"

#include "QDebug"

#include <QQuickView>
#include <QQmlContext>

BattleWidget::BattleWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedWidth(1200);
    this->setFixedHeight(600);

    m_pLayoutBattleMapWidget = new QVBoxLayout();

    // Interaction QML
    //Anchor anchor;
    //qmlRegisterType<Anchor>("classAnchor", 1, 0, "Anchor");

    QQuickView *view = new QQuickView();
    QWidget *container = QWidget::createWindowContainer(view, this);
    container->setMinimumSize(this->width(), this->height());
    container->setMaximumSize(this->width(), this->height());

    //view->rootContext()->setContextProperty("anchor", &anchor);

    view->setSource(QUrl("qrc:/QML/BattleMap/BattleMap.qml")); // Fetch this url by right clicking on your resource file.

    m_pLayoutBattleMapWidget->addWidget(container);

    //anchor.setProperty("color", QVariant::fromValue(Qt::red));

    this->setLayout(m_pLayoutBattleMapWidget);
}
