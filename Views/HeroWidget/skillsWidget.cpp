#include "skillsWidget.h"

#include "QDebug"


SkillsWidget::SkillsWidget(QWidget *parent) : QWidget(parent)
{
    m_pSkillsLayout = new QVBoxLayout();

    m_pSkillLabel                  = new QLabel("Compétences");

    m_pLabelFirstFightSkill        = new QLabel("First Fight Skill");
    m_pLabelSecondFightSkill       = new QLabel("Second Fight Skill");
    m_pLabelSupportFightSkill      = new QLabel("Support Fight Skill");

    m_pLabelFirstFightSkillValue   = new QLabel("");
    m_pLabelSecondFightSkillValue  = new QLabel("");
    m_pLabelSupportFightSkillValue = new QLabel("");

    m_pSkillsLayout->addWidget(m_pSkillLabel);
    m_pSkillsLayout->addWidget(m_pLabelFirstFightSkill);
    m_pSkillsLayout->addWidget(m_pLabelFirstFightSkillValue);
    m_pSkillsLayout->addWidget(m_pLabelSecondFightSkill);
    m_pSkillsLayout->addWidget(m_pLabelSecondFightSkillValue);
    m_pSkillsLayout->addWidget(m_pLabelSupportFightSkill);
    m_pSkillsLayout->addWidget(m_pLabelSupportFightSkillValue);

    this->setLayout(m_pSkillsLayout);
}

SkillsWidget::~SkillsWidget()
{
    if(m_pSkillLabel != NULL)
    {
        delete m_pSkillLabel;
    }
    if(m_pLabelFirstFightSkill != NULL)
    {
        delete m_pLabelFirstFightSkill;
    }
    if(m_pLabelFirstFightSkillValue != NULL)
    {
        delete m_pLabelFirstFightSkillValue;
    }
    if(m_pLabelSecondFightSkill != NULL)
    {
        delete m_pLabelSecondFightSkill;
    }
    if(m_pLabelSecondFightSkillValue != NULL)
    {
        delete m_pLabelSecondFightSkillValue;
    }
    if(m_pLabelSupportFightSkill != NULL)
    {
        delete m_pLabelSupportFightSkill;
    }
    if(m_pLabelSupportFightSkillValue != NULL)
    {
        delete m_pLabelSupportFightSkillValue;
    }
    if(m_pSkillsLayout != NULL)
    {
        delete m_pSkillsLayout;
    }
}

void SkillsWidget::refreshSkillsView(Skills skills)
{
    m_pLabelFirstFightSkillValue->setText(skills.m_FirstFightSkill);
    m_pLabelSecondFightSkillValue->setText(skills.m_SecondFightSkill);
    m_pLabelSupportFightSkillValue->setText(skills.m_SupportFightSkill);
}



