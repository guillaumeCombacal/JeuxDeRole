#ifndef STATSWIDGETEDIT_H
#define STATSWIDGETEDIT_H

#include <QWidget>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QLabel>

#include "sharedDataHero.h"

class StatsWidgetEdit : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout* m_pMainLayoutStats;
    QLabel*      m_pLabelStats;

    QLineEdit*   m_pLineEditPV;
    QLineEdit*   m_pLineEditPA;
    QLineEdit*   m_pLineEditPM;
    QLineEdit*   m_pLineEditForce;
    QLineEdit*   m_pLineEditDexterite;
    QLineEdit*   m_pLineEditIntelligence;
    QLineEdit*   m_pLineEditProtection;
    QLineEdit*   m_pLineEditArmure;

    QLabel*      m_pLabelPV;
    QLabel*      m_pLabelPA;
    QLabel*      m_pLabelPM;
    QLabel*      m_pLabelForce;
    QLabel*      m_pLabelDexterite;
    QLabel*      m_pLabelIntelligence;
    QLabel*      m_pLabelProtection;
    QLabel*      m_pLabelArmure;

public:
    explicit StatsWidgetEdit(QWidget *parent = 0);
    ~StatsWidgetEdit();

    void refreshStatsView(Stats stats);

    Stats getStatsValues();

signals:

public slots:
};

#endif // STATSWIDGETEDIT_H
