#ifndef HEROWIDGET_H
#define HEROWIDGET_H

#include <QWidget>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QGridLayout>

#include "statsWidget.h"
#include "loadEditHeroWidget.h"
#include "featureHeroWidget.h"
#include "bagPackWidget.h"
#include "effectWidget.h"
#include "equipmentWidget.h"
#include "questObjectWidget.h"
#include "skillsWidget.h"
#include "questObjectWidget.h"

#include "sharedDataHero.h"

class HeroWidget : public QWidget
{
    Q_OBJECT

private:

    QGridLayout*        m_pHeroLayout;
    StatsWidget*        m_pStatsWidget;
    FeatureHeroWidget*  m_pFeatureHeroWidget;
    LoadEditHeroWidget* m_pLoadEditHeroWidget;
    BagPackWidget*      m_pBagPackWidget;
    EffectWidget*       m_pEffectWidget;
    EquipmentWidget*    m_pEquipmentWidget;
    SkillsWidget*       m_pSkillsWidget;
    QuestObjectWidget*  m_pQuestWidget;

    QPushButton*        m_pBtnPreviousHero;
    QPushButton*        m_pBtnNextHero;


public:
    explicit HeroWidget(QWidget *parent = 0);
    ~HeroWidget();

    LoadEditHeroWidget *getLoadEditHeroWidget();
    void refreshView(Stats stats, Feature feature, Equipment equipment,
                     Skills skills, Effect effect, Bag bag, QuestObject questObject);
    void refreshEditableView();

    QPushButton* getBtnNextHero();
    QPushButton* getBtnPreviousHero();

signals:

public slots:
};

#endif // HEROWIDGET_H
