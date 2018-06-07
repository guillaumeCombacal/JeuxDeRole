#ifndef SKILLSWIDGET_H
#define SKILLSWIDGET_H

#include <QWidget>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QLabel>

#include "sharedDataHero.h"

class SkillsWidget : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout* m_pSkillsLayout;
    QLabel*      m_pSkillLabel;

    QLabel*      m_pLabelFirstFightSkill;
    QLabel*      m_pLabelSecondFightSkill;
    QLabel*      m_pLabelSupportFightSkill;

    QLabel*      m_pLabelFirstFightSkillValue;
    QLabel*      m_pLabelSecondFightSkillValue;
    QLabel*      m_pLabelSupportFightSkillValue;

	
public:
    explicit SkillsWidget(QWidget *parent = 0);
    ~SkillsWidget();

    void refreshSkillsView(Skills skills);

signals:

private slots:


public slots:


};

#endif // SKILLSWIDGET_H
