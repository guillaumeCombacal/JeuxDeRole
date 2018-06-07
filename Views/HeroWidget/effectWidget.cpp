#include "effectWidget.h"

#include "QDebug"


EffectWidget::EffectWidget(QWidget *parent) : QWidget(parent)
{   
    m_pEffectLayout     = new QVBoxLayout();

    m_pEffectLabel      = new QLabel("Effets");

    m_pLabelRaceEffect       = new QLabel("Race Effect");
    m_pLabelClassEffect      = new QLabel("Class Effect");
    m_pLabelBonusEffect      = new QLabel("Bonus Effect");
    m_pLabelMalusEffect      = new QLabel("Malus Effect");

    m_pLabelRaceEffectValue  = new QLabel("");
    m_pLabelClassEffectValue = new QLabel("");
    m_pLabelBonusEffectValue = new QLabel("");
    m_pLabelMalusEffectValue = new QLabel("");

    m_pEffectLayout->addWidget(m_pEffectLabel);
    m_pEffectLayout->addWidget(m_pLabelRaceEffect);
    m_pEffectLayout->addWidget(m_pLabelRaceEffectValue);
    m_pEffectLayout->addWidget(m_pLabelClassEffect);
    m_pEffectLayout->addWidget(m_pLabelClassEffectValue);
    m_pEffectLayout->addWidget(m_pLabelBonusEffect);
    m_pEffectLayout->addWidget(m_pLabelBonusEffectValue);
    m_pEffectLayout->addWidget(m_pLabelMalusEffect);
    m_pEffectLayout->addWidget(m_pLabelMalusEffectValue);

    this->setLayout(m_pEffectLayout);
}

EffectWidget::~EffectWidget()
{
    if(m_pEffectLabel != NULL)
    {
        delete m_pEffectLabel;
    }
    if(m_pLabelRaceEffect != NULL)
    {
        delete m_pLabelRaceEffect;
    }
    if(m_pLabelRaceEffectValue != NULL)
    {
        delete m_pLabelRaceEffectValue;
    }
    if(m_pLabelClassEffect != NULL)
    {
        delete m_pLabelClassEffect;
    }
    if(m_pLabelClassEffectValue != NULL)
    {
        delete m_pLabelClassEffectValue;
    }
    if(m_pLabelBonusEffect != NULL)
    {
        delete m_pLabelBonusEffect;
    }
    if(m_pLabelBonusEffectValue != NULL)
    {
        delete m_pLabelBonusEffectValue;
    }
    if(m_pLabelMalusEffectValue != NULL)
    {
        delete m_pLabelMalusEffectValue;
    }
    if(m_pEffectLayout != NULL)
    {
        delete m_pEffectLayout;
    }
}

void EffectWidget::refreshEffectView(Effect effect)
{
    m_pLabelRaceEffectValue->setText(effect.m_RaceEffect);
    m_pLabelClassEffectValue->setText(effect.m_ClassEffect);
    m_pLabelBonusEffectValue->setText(effect.m_BonusEffect);
    m_pLabelMalusEffectValue->setText(effect.m_MalusEffect);
}


