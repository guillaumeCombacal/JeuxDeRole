#include "heroWidgetEdit.h"

#include "QDebug"

HeroWidgetEdit::HeroWidgetEdit(QWidget *parent) : QWidget(parent)
{

    m_pHeroEditLayout           = new QGridLayout();

    m_pStatsWidgetEdit          = new StatsWidgetEdit();
    m_pCancelSaveHeroWidgetEdit = new CancelSaveHeroWidgetEdit();
    m_pFeatureHeroWidgetEdit    = new FeatureHeroWidgetEdit();
    m_pBagPackWidgetEdit        = new BagPackWidgetEdit();
    m_pEffectWidgetEdit         = new EffectWidgetEdit();
    m_pEquipmentWidgetEdit      = new EquipmentWidgetEdit();
    m_pSkillsWidgetEdit         = new SkillsWidgetEdit();
    m_pQuestWidgetEdit          = new QuestObjectWidgetEdit();

    // Proportion / dimension inside the grid Layout (widget*, row, column, rowSpan, columnSpan)

    m_pHeroEditLayout->addWidget(m_pCancelSaveHeroWidgetEdit,0,0,2,1);
    m_pHeroEditLayout->addWidget(m_pStatsWidgetEdit,2,0,8,1);

    m_pHeroEditLayout->addWidget(m_pFeatureHeroWidgetEdit,0,1,6,3);
    m_pHeroEditLayout->addWidget(m_pSkillsWidgetEdit,6,1,4,3);

    m_pHeroEditLayout->addWidget(m_pEquipmentWidgetEdit,0,4,6,1);
    m_pHeroEditLayout->addWidget(m_pEffectWidgetEdit,6,4,4,1);

    m_pHeroEditLayout->addWidget(m_pBagPackWidgetEdit,0,5,6,1);
    m_pHeroEditLayout->addWidget(m_pQuestWidgetEdit,6,5,4,1);

    this->setLayout(m_pHeroEditLayout);
}

HeroWidgetEdit::~HeroWidgetEdit()
{
    if(m_pStatsWidgetEdit != NULL)
    {
        delete m_pStatsWidgetEdit;
    }
    if(m_pCancelSaveHeroWidgetEdit != NULL)
    {
        delete m_pCancelSaveHeroWidgetEdit;
    }
    if(m_pFeatureHeroWidgetEdit != NULL)
    {
        delete m_pFeatureHeroWidgetEdit;
    }
    if(m_pBagPackWidgetEdit != NULL)
    {
        delete m_pBagPackWidgetEdit;
    }
    if(m_pEffectWidgetEdit != NULL)
    {
        delete m_pEffectWidgetEdit;
    }
    if(m_pEquipmentWidgetEdit != NULL)
    {
        delete m_pEquipmentWidgetEdit;
    }
    if(m_pSkillsWidgetEdit != NULL)
    {
        delete m_pSkillsWidgetEdit;
    }
    if(m_pQuestWidgetEdit != NULL)
    {
        delete m_pQuestWidgetEdit;
    }
    if(m_pHeroEditLayout != NULL)
    {
        delete m_pHeroEditLayout;
    }
}

CancelSaveHeroWidgetEdit* HeroWidgetEdit::getCancelSaveHeroWidgetEdit()
{
    return m_pCancelSaveHeroWidgetEdit;
}


StatsWidgetEdit* HeroWidgetEdit::getStatsWidgetEdit()
{
    return m_pStatsWidgetEdit;
}

FeatureHeroWidgetEdit* HeroWidgetEdit::getFeatureHeroWidgetEdit()
{
    return m_pFeatureHeroWidgetEdit;
}

BagPackWidgetEdit* HeroWidgetEdit::getBagPackWidgetEdit()
{
    return m_pBagPackWidgetEdit;
}

EffectWidgetEdit* HeroWidgetEdit::getEffectWidgetEdit()
{
    return m_pEffectWidgetEdit;
}

EquipmentWidgetEdit* HeroWidgetEdit::getEquipmentWidgetEdit()
{
    return m_pEquipmentWidgetEdit;
}

SkillsWidgetEdit* HeroWidgetEdit::getSkillsWidgetEdit()
{
    return m_pSkillsWidgetEdit;
}

QuestObjectWidgetEdit* HeroWidgetEdit::getQuestObjectWidgetEdit()
{
    return m_pQuestWidgetEdit;
}

// Dispatch the refresh of all widget views
void HeroWidgetEdit::refreshView(Stats stats, Feature feature, Equipment equipment,
                             Skills skills, Effect effect, Bag bag, QuestObject questObject)
{
    m_pStatsWidgetEdit->refreshStatsView(stats);
    m_pFeatureHeroWidgetEdit->refreshFeatureView(feature);
    m_pEquipmentWidgetEdit->refreshEquipmentView(equipment);
    m_pSkillsWidgetEdit->refreshSkillsView(skills);
    m_pEffectWidgetEdit->refreshEffectView(effect);
    m_pBagPackWidgetEdit->refreshBagView(bag);
    m_pQuestWidgetEdit->refreshQuestViewEdit(questObject);
}
