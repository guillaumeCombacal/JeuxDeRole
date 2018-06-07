#include "heroWidget.h"

#include "QDebug"

HeroWidget::HeroWidget(QWidget *parent) : QWidget(parent)
{

    m_pHeroLayout         = new QGridLayout();

    m_pStatsWidget        = new StatsWidget();
    m_pLoadEditHeroWidget = new LoadEditHeroWidget();
    m_pFeatureHeroWidget  = new FeatureHeroWidget();
    m_pBagPackWidget      = new BagPackWidget();
    m_pEffectWidget       = new EffectWidget();
    m_pEquipmentWidget    = new EquipmentWidget();
    m_pSkillsWidget       = new SkillsWidget();
    m_pQuestWidget        = new QuestObjectWidget();

    m_pBtnNextHero        = new QPushButton(">");
    m_pBtnPreviousHero    = new QPushButton("<");

    m_pBtnNextHero->setEnabled(false);
    m_pBtnPreviousHero->setEnabled(false);

    m_pHeroLayout->addWidget(m_pBtnPreviousHero,4,0,2,1);

    m_pHeroLayout->addWidget(m_pLoadEditHeroWidget,0,1,2,1);
    m_pHeroLayout->addWidget(m_pStatsWidget,2,1,8,1);

    m_pHeroLayout->addWidget(m_pFeatureHeroWidget,0,2,6,1);
    m_pHeroLayout->addWidget(m_pSkillsWidget,6,2,4,1);

    m_pHeroLayout->addWidget(m_pEquipmentWidget,0,3,6,1);
    m_pHeroLayout->addWidget(m_pEffectWidget,6,3,4,1);

    m_pHeroLayout->addWidget(m_pBagPackWidget,0,4,6,1);
    m_pHeroLayout->addWidget(m_pQuestWidget,6,4,4,1);

    m_pHeroLayout->addWidget(m_pBtnNextHero,4,7,2,1);

    this->setLayout(m_pHeroLayout);
}

HeroWidget::~HeroWidget()
{
    if(m_pStatsWidget != NULL)
    {
        delete m_pStatsWidget;
    }
    if(m_pLoadEditHeroWidget != NULL)
    {
        delete m_pLoadEditHeroWidget;
    }
    if(m_pFeatureHeroWidget != NULL)
    {
        delete m_pFeatureHeroWidget;
    }
    if(m_pBagPackWidget != NULL)
    {
        delete m_pBagPackWidget;
    }
    if(m_pEffectWidget != NULL)
    {
        delete m_pEffectWidget;
    }
    if(m_pEquipmentWidget != NULL)
    {
        delete m_pEquipmentWidget;
    }
    if(m_pSkillsWidget != NULL)
    {
        delete m_pSkillsWidget;
    }
    if(m_pQuestWidget != NULL)
    {
        delete m_pQuestWidget;
    }
    if(m_pHeroLayout != NULL)
    {
        delete m_pHeroLayout;
    }
    if(m_pBtnNextHero != NULL)
    {
        delete m_pBtnNextHero;
    }
    if(m_pBtnPreviousHero != NULL)
    {
        delete m_pBtnPreviousHero;
    }
}

QPushButton* HeroWidget::getBtnNextHero()
{
    return m_pBtnNextHero;
}

QPushButton* HeroWidget::getBtnPreviousHero()
{
    return m_pBtnPreviousHero;
}

LoadEditHeroWidget *HeroWidget::getLoadEditHeroWidget()
{
    return m_pLoadEditHeroWidget;
}

// Dispatch the refresh of all widget views
void HeroWidget::refreshView(Stats stats, Feature feature, Equipment equipment,
                             Skills skills, Effect effect, Bag bag, QuestObject questObject)
{
    /*
    m_pStatsWidget->refreshStatsView(QString::number(stats.m_PV), QString::number(stats.m_PA), QString::number(stats.m_PM),
                                     QString::number(stats.m_Protection), QString::number(stats.m_Armure),
                                     QString::number(stats.m_Force), QString::number(stats.m_Dexterite),
                                     QString::number(stats.m_Intelligence));

    m_pFeatureHeroWdget->refreshFeatureView(feature.m_Name, feature.m_Race, feature.m_Job,
                                            QString::number(feature.m_Lvl), QString::number(feature.m_Xp));

    m_pEquipmentWidget->refreshEquipmentView(equipment.m_Head, equipment.m_Chest, equipment.m_Hand, equipment.m_Leg,
                                             equipment.m_Feet,equipment.m_RightHandStuff, equipment.m_LeftHandStuff);

    m_pSkillsWdget->refreshSkillsView(skills.m_FirstFightSkill, skills.m_SecondFightSkill, skills.m_SupportFightSkill);

    m_pBagPackWidget->refreshBagView(QString::number(bag.m_Nourriture), QString::number(bag.m_Or), bag.m_vBag);

    m_pQuestWidget->refreshQuestView(questObject.m_vQuestObject);
    */

    qDebug()<<"HeroWidget::refreshView";

    m_pStatsWidget->refreshStatsView(stats);
    m_pFeatureHeroWidget->refreshFeatureView(feature);
    m_pEquipmentWidget->refreshEquipmentView(equipment);
    m_pSkillsWidget->refreshSkillsView(skills);
    m_pEffectWidget->refreshEffectView(effect);
    m_pBagPackWidget->refreshBagView(bag);
    m_pQuestWidget->refreshQuestView(questObject);
}

void HeroWidget::refreshEditableView()
{

}
