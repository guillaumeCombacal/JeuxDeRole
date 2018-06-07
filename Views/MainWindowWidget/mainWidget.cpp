#include "mainWidget.h"

#include <QDebug>

MainWidget::MainWidget(QWidget *ongletWidget, QWidget *worldMapWidget, QWidget *battleWidget,
                       QWidget *heroWidget, QWidget *heroWidgetEdit, QWidget *questWidget,
                       QWidget *parent) : QWidget(parent)
{
    m_pOngletWidget = ongletWidget;
    m_pOngletWidget->setFixedHeight(40);

    m_pStackWidget = new QStackedWidget();
    m_pStackWidget->addWidget(worldMapWidget);
    m_pStackWidget->addWidget(battleWidget);
    m_pStackWidget->addWidget(heroWidget);
    m_pStackWidget->addWidget(heroWidgetEdit);
    m_pStackWidget->addWidget(questWidget);
    m_pStackWidget->setCurrentIndex(0);

    m_pMainLayoutMainWidget = new QVBoxLayout();
    m_pMainLayoutMainWidget->addWidget(m_pOngletWidget);
    m_pMainLayoutMainWidget->addWidget(m_pStackWidget);

    this->setLayout(m_pMainLayoutMainWidget);
}

MainWidget::~MainWidget()
{
    if( m_pStackWidget != NULL)
    {
        delete m_pStackWidget;
    }
}

QStackedWidget *MainWidget::getStackWidget()
{
    return m_pStackWidget;
}


