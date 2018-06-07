#include "skillsWidgetEdit.h"

#include "QDebug"


SkillsWidgetEdit::SkillsWidgetEdit(QWidget *parent) : QWidget(parent)
{
    m_pSkillsLayout = new QVBoxLayout();

    m_pSkillLabel             = new QLabel("Compétences");
    m_pFirstFightSkill        = new QLineEdit("First Fight Skill");
    m_pSecondFightSkill       = new QLineEdit("Second Fight Skill");
    m_pSupportFightSkill      = new QLineEdit("Support Fight Skill");
    m_pLabelFirstFightSkill   = new QLabel("Technique Combat 1");
    m_pLabelSecondFightSkill  = new QLabel("Technique Combat 2");
    m_pLabelSupportFightSkill = new QLabel("Technique de Soutiens");

    m_pSkillsLayout->addWidget(m_pSkillLabel);
    m_pSkillsLayout->addWidget(m_pLabelFirstFightSkill);
    m_pSkillsLayout->addWidget(m_pFirstFightSkill);
    m_pSkillsLayout->addWidget(m_pLabelSecondFightSkill);
    m_pSkillsLayout->addWidget(m_pSecondFightSkill);
    m_pSkillsLayout->addWidget(m_pLabelSupportFightSkill);
    m_pSkillsLayout->addWidget(m_pSupportFightSkill);

    this->setLayout(m_pSkillsLayout);
}

SkillsWidgetEdit::~SkillsWidgetEdit()
{
    if(m_pSkillLabel != NULL)
    {
        delete m_pSkillLabel;
    }
    if(m_pFirstFightSkill != NULL)
    {
        delete m_pFirstFightSkill;
    }
    if(m_pSecondFightSkill != NULL)
    {
        delete m_pSecondFightSkill;
    }
    if(m_pSupportFightSkill != NULL)
    {
        delete m_pSupportFightSkill;
    }
    if(m_pSkillsLayout != NULL)
    {
        delete m_pSkillsLayout;
    }
}

void SkillsWidgetEdit::refreshSkillsView(Skills skills)
{
    m_pFirstFightSkill->setText(skills.m_FirstFightSkill);
    m_pSecondFightSkill->setText(skills.m_SecondFightSkill);
    m_pSupportFightSkill->setText(skills.m_SupportFightSkill);
}

Skills SkillsWidgetEdit::getSkillsValues()
{
    Skills skills;

    skills.m_FirstFightSkill = m_pFirstFightSkill->text();
    skills.m_SecondFightSkill = m_pSecondFightSkill->text();
    skills.m_SupportFightSkill = m_pSupportFightSkill->text();

    return skills;
}



