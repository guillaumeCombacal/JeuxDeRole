#include "statsWidget.h"

#include "QDebug"

StatsWidget::StatsWidget(QWidget *parent) : QWidget(parent)
{
    m_pMainLayoutStats = new QVBoxLayout();

    m_pLabelStats = new QLabel("Stats");

    m_pLabelPV           = new QLabel("PV");
    m_pLabelPA           = new QLabel("PA");
    m_pLabelPM           = new QLabel("PM");
    m_pLabelForce        = new QLabel("Force");
    m_pLabelDexterite    = new QLabel("Dexterite");
    m_pLabelIntelligence = new QLabel("Intelligence");
    m_pLabelProtection   = new QLabel("Protection");
    m_pLabelArmure       = new QLabel("Armure");

    m_pLabelPVValue           = new QLabel("");
    m_pLabelPAValue           = new QLabel("");
    m_pLabelPMValue           = new QLabel("");
    m_pLabelForceValue        = new QLabel("");
    m_pLabelDexteriteValue    = new QLabel("");
    m_pLabelIntelligenceValue = new QLabel("");
    m_pLabelProtectionValue   = new QLabel("");
    m_pLabelArmureValue       = new QLabel("");

    m_pMainLayoutStats->addWidget(m_pLabelStats);
    m_pMainLayoutStats->addWidget(m_pLabelPV);
    m_pMainLayoutStats->addWidget(m_pLabelPVValue);
    m_pMainLayoutStats->addWidget(m_pLabelPA);
    m_pMainLayoutStats->addWidget(m_pLabelPAValue);
    m_pMainLayoutStats->addWidget(m_pLabelPM);
    m_pMainLayoutStats->addWidget(m_pLabelPMValue);
    m_pMainLayoutStats->addWidget(m_pLabelForce);
    m_pMainLayoutStats->addWidget(m_pLabelForceValue);
    m_pMainLayoutStats->addWidget(m_pLabelDexterite);
    m_pMainLayoutStats->addWidget(m_pLabelDexteriteValue);
    m_pMainLayoutStats->addWidget(m_pLabelIntelligence);
    m_pMainLayoutStats->addWidget(m_pLabelIntelligenceValue);
    m_pMainLayoutStats->addWidget(m_pLabelProtection);
    m_pMainLayoutStats->addWidget(m_pLabelProtectionValue);
    m_pMainLayoutStats->addWidget(m_pLabelArmure);
    m_pMainLayoutStats->addWidget(m_pLabelArmureValue);

    this->setLayout(m_pMainLayoutStats);

}

StatsWidget::~StatsWidget()
{
    if(m_pLabelStats != NULL)
    {
        delete m_pLabelStats;
    }
    if(m_pLabelPV != NULL)
    {
        delete m_pLabelPV;
    }
    if(m_pLabelPVValue != NULL)
    {
        delete m_pLabelPVValue;
    }
    if(m_pLabelPA != NULL)
    {
        delete m_pLabelPA;
    }
    if(m_pLabelPAValue != NULL)
    {
        delete m_pLabelPAValue;
    }
    if(m_pLabelPM != NULL)
    {
        delete m_pLabelPM;
    }
    if(m_pLabelPMValue != NULL)
    {
        delete m_pLabelPMValue;
    }
    if(m_pLabelForce != NULL)
    {
        delete m_pLabelForce;
    }
    if(m_pLabelForceValue != NULL)
    {
        delete m_pLabelForceValue;
    }
    if(m_pLabelDexterite != NULL)
    {
        delete m_pLabelDexterite;
    }
    if(m_pLabelDexteriteValue != NULL)
    {
        delete m_pLabelDexteriteValue;
    }
    if(m_pLabelIntelligence != NULL)
    {
        delete m_pLabelIntelligence;
    }
    if(m_pLabelIntelligenceValue != NULL)
    {
        delete m_pLabelIntelligenceValue;
    }
    if(m_pLabelProtection != NULL)
    {
        delete m_pLabelProtection;
    }
    if(m_pLabelProtectionValue != NULL)
    {
        delete m_pLabelProtectionValue;
    }
    if(m_pLabelArmure != NULL)
    {
        delete m_pLabelArmure;
    }
    if(m_pLabelArmureValue != NULL)
    {
        delete m_pLabelArmureValue;
    }
    if(m_pMainLayoutStats != NULL)
    {
        delete m_pMainLayoutStats;
    }
}

void StatsWidget::refreshStatsView(Stats stats)
{
    qDebug()<<"StatsWidget::refreshStatsView";

    m_pLabelPVValue->setText(QString::number(stats.m_PV));
    m_pLabelPAValue->setText(QString::number(stats.m_PA));
    m_pLabelPMValue->setText(QString::number(stats.m_PM));
    m_pLabelForceValue->setText(QString::number(stats.m_Force));
    m_pLabelDexteriteValue->setText(QString::number(stats.m_Dexterite));
    m_pLabelIntelligenceValue->setText(QString::number(stats.m_Intelligence));
    m_pLabelProtectionValue->setText(QString::number(stats.m_Protection));
    m_pLabelArmureValue->setText(QString::number(stats.m_Armure));
}
