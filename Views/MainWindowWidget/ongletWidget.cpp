#include "ongletWidget.h"

#include "QDebug"
#include <QApplication>

OngletWidget::OngletWidget(QWidget *parent) : QWidget(parent)
{
	m_pOngletLayout = new QHBoxLayout();
	
    m_pOngletWorldMapBtn = new QPushButton("World Map");
    m_pOngletWorldMapBtn->setObjectName("WorldMapBtn");
    m_pOngletWorldMapBtn->setMinimumHeight(25);
    connect(m_pOngletWorldMapBtn, SIGNAL(clicked(bool)), this, SLOT(onSwitchView()));

    m_pOngletBattleBtn = new QPushButton("Battle");
    m_pOngletBattleBtn->setObjectName("BattleBtn");
    m_pOngletBattleBtn->setMinimumHeight(25);
    connect(m_pOngletBattleBtn, SIGNAL(clicked(bool)), this, SLOT(onSwitchView()));

    m_pOngletHeroBtn = new QPushButton("Hero");
    m_pOngletHeroBtn->setObjectName("HeroBtn");
    m_pOngletHeroBtn->setMinimumHeight(25);
    connect(m_pOngletHeroBtn, SIGNAL(clicked(bool)), this, SLOT(onSwitchView()));

    m_pOngletQuestBtn = new QPushButton("Quest");
    m_pOngletQuestBtn->setObjectName("QuestBtn");
    m_pOngletQuestBtn->setMinimumHeight(25);
    connect(m_pOngletQuestBtn, SIGNAL(clicked(bool)), this, SLOT(onSwitchView()));

    m_pOngletLayout->addWidget(m_pOngletWorldMapBtn);
    m_pOngletLayout->addWidget(m_pOngletBattleBtn);
    m_pOngletLayout->addWidget(m_pOngletHeroBtn);
    m_pOngletLayout->addWidget(m_pOngletQuestBtn);

    this->setLayout(m_pOngletLayout);
}


void OngletWidget::onSwitchView()
{
    QString objectName = QObject::sender()->objectName();
    int idOnglet = -1;

    if(objectName == "WorldMapBtn")
    {
        idOnglet = 0;
    }
    else if(objectName == "BattleBtn")
    {
        idOnglet = 1;
    }
    else if(objectName == "HeroBtn")
    {
        idOnglet = 2;
    }
    else if(objectName == "QuestBtn")
    {
        idOnglet = 3;
    }

    // Send Signal
    if(idOnglet != -1)
    {
        Q_EMIT sendSwitchWidget(idOnglet);
    }
}
