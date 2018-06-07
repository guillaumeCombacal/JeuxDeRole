#include "effectWidgetEdit.h"

#include "QDebug"


EffectWidgetEdit::EffectWidgetEdit(QWidget *parent) : QWidget(parent)
{   
    m_pEffectEditLayout     = new QVBoxLayout();

    m_pEffectEditLabel      = new QLabel("Effets");
    m_pRaceEffectEdit       = new QLineEdit("Race Effect");
    m_pClassEffectEdit      = new QLineEdit("Class Effect");
    m_pBonusEffectEdit      = new QLineEdit("Bonus Effect");
    m_pMalusEffectEdit      = new QLineEdit("Malus Effect");
    m_pRaceEffectEditLabel  = new QLabel("Effet de Race");
    m_pClassEffectEditLabel = new QLabel("Effet de Classe");
    m_pBonusEffectEditLabel = new QLabel("Effet Bonus");
    m_pMalusEffectEditLabel = new QLabel("Effet Malus");

    m_pEffectEditLayout->addWidget(m_pEffectEditLabel);
    m_pEffectEditLayout->addWidget(m_pRaceEffectEditLabel);
    m_pEffectEditLayout->addWidget(m_pRaceEffectEdit);
    m_pEffectEditLayout->addWidget(m_pClassEffectEditLabel);
    m_pEffectEditLayout->addWidget(m_pClassEffectEdit);
    m_pEffectEditLayout->addWidget(m_pBonusEffectEditLabel);
    m_pEffectEditLayout->addWidget(m_pBonusEffectEdit);
    m_pEffectEditLayout->addWidget(m_pMalusEffectEditLabel);
    m_pEffectEditLayout->addWidget(m_pMalusEffectEdit);

    this->setLayout(m_pEffectEditLayout);
}

EffectWidgetEdit::~EffectWidgetEdit()
{
    if(m_pEffectEditLabel != NULL)
    {
        delete m_pEffectEditLabel;
    }
    if(m_pRaceEffectEdit != NULL)
    {
        delete m_pRaceEffectEdit;
    }
    if(m_pClassEffectEdit != NULL)
    {
        delete m_pClassEffectEdit;
    }
    if(m_pBonusEffectEdit != NULL)
    {
        delete m_pBonusEffectEdit;
    }
    if(m_pMalusEffectEdit != NULL)
    {
        delete m_pMalusEffectEdit;
    }
    if(m_pEffectEditLayout != NULL)
    {
        delete m_pEffectEditLayout;
    }
}

void EffectWidgetEdit::refreshEffectView(Effect effect)
{
    m_pRaceEffectEdit->setText(effect.m_RaceEffect);
    m_pClassEffectEdit->setText(effect.m_ClassEffect);
    m_pMalusEffectEdit->setText(effect.m_MalusEffect);
    m_pBonusEffectEdit->setText(effect.m_BonusEffect);
}

 Effect EffectWidgetEdit::getEffectValues()
 {
     Effect effect;

     effect.m_BonusEffect = m_pBonusEffectEdit->text();
     effect.m_ClassEffect = m_pClassEffectEdit->text();
     effect.m_MalusEffect = m_pMalusEffectEdit->text();
     effect.m_RaceEffect = m_pRaceEffectEdit->text();

     return effect;
 }

