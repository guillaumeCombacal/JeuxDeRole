#ifndef STATSWIDGET_H
#define STATSWIDGET_H

#include <QWidget>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QLabel>

#include "sharedDataHero.h"

class StatsWidget : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout* m_pMainLayoutStats;
    QLabel*      m_pLabelStats;

    QLabel*      m_pLabelPV;
    QLabel*      m_pLabelPA;
    QLabel*      m_pLabelPM;
    QLabel*      m_pLabelForce;
    QLabel*      m_pLabelDexterite;
    QLabel*      m_pLabelIntelligence;
    QLabel*      m_pLabelProtection;
    QLabel*      m_pLabelArmure;

    QLabel*      m_pLabelPVValue;
    QLabel*      m_pLabelPAValue;
    QLabel*      m_pLabelPMValue;
    QLabel*      m_pLabelForceValue;
    QLabel*      m_pLabelDexteriteValue;
    QLabel*      m_pLabelIntelligenceValue;
    QLabel*      m_pLabelProtectionValue;
    QLabel*      m_pLabelArmureValue;

public:
    explicit StatsWidget(QWidget *parent = 0);
    ~StatsWidget();

    void refreshStatsView(Stats stats);

signals:

public slots:
};

#endif // STATSWIDGET_H
