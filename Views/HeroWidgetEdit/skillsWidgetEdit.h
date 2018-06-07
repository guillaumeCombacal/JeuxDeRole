#ifndef SKILLSWIDGETEDIT_H
#define SKILLSWIDGETEDIT_H

#include <QWidget>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QLabel>

#include "sharedDataHero.h"

class SkillsWidgetEdit : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout* m_pSkillsLayout;
    QLabel*      m_pSkillLabel;
    QLineEdit*   m_pFirstFightSkill;
    QLineEdit*   m_pSecondFightSkill;
    QLineEdit*   m_pSupportFightSkill;
    QLabel*      m_pLabelFirstFightSkill;
    QLabel*      m_pLabelSecondFightSkill;
    QLabel*      m_pLabelSupportFightSkill;

	
public:
    explicit SkillsWidgetEdit(QWidget *parent = 0);
    ~SkillsWidgetEdit();

    void refreshSkillsView(Skills skills);

    Skills getSkillsValues();

signals:

private slots:


public slots:


};

#endif // SKILLSWIDGETEDIT_H
