#ifndef HEROWIDGETEDIT_H
#define HEROWIDGETEDIT_H

#include <QWidget>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QGridLayout>

#include "statsWidgetEdit.h"
#include "cancelSaveHeroWidgetEdit.h"
#include "featureHeroWidgetEdit.h"
#include "bagPackWidgetEdit.h"
#include "effectWidgetEdit.h"
#include "equipmentWidgetEdit.h"
#include "questObjectWidgetEdit.h"
#include "skillsWidgetEdit.h"
#include "questObjectWidgetEdit.h"

#include "sharedDataHero.h"

class HeroWidgetEdit : public QWidget
{
    Q_OBJECT

private:

    QGridLayout*              m_pHeroEditLayout;
    StatsWidgetEdit*          m_pStatsWidgetEdit;
    FeatureHeroWidgetEdit*    m_pFeatureHeroWidgetEdit;
    CancelSaveHeroWidgetEdit* m_pCancelSaveHeroWidgetEdit;
    BagPackWidgetEdit*        m_pBagPackWidgetEdit;
    EffectWidgetEdit*         m_pEffectWidgetEdit;
    EquipmentWidgetEdit*      m_pEquipmentWidgetEdit;
    SkillsWidgetEdit*         m_pSkillsWidgetEdit;
    QuestObjectWidgetEdit*    m_pQuestWidgetEdit;

public:
    explicit HeroWidgetEdit(QWidget *parent = 0);
    ~HeroWidgetEdit();

    CancelSaveHeroWidgetEdit* getCancelSaveHeroWidgetEdit();
    StatsWidgetEdit*          getStatsWidgetEdit();
    FeatureHeroWidgetEdit*    getFeatureHeroWidgetEdit();
    BagPackWidgetEdit*        getBagPackWidgetEdit();
    EffectWidgetEdit*         getEffectWidgetEdit();
    EquipmentWidgetEdit*      getEquipmentWidgetEdit();
    SkillsWidgetEdit*         getSkillsWidgetEdit();
    QuestObjectWidgetEdit*    getQuestObjectWidgetEdit();


    void refreshView(Stats stats, Feature feature, Equipment equipment,
                     Skills skills, Effect effect, Bag bag, QuestObject questObject);

signals:

public slots:
};

#endif // HEROWIDGETEDIT_H
