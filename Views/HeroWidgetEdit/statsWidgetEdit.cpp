#include "statsWidgetEdit.h"

#include "QDebug"

StatsWidgetEdit::StatsWidgetEdit(QWidget *parent) : QWidget(parent)
{
    qDebug()<<"StatsWidget";

/*    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    */

    this->setGeometry(100, 100, 500, 500);

    m_pMainLayoutStats = new QVBoxLayout();

    m_pLabelStats = new QLabel("Stats");

    m_pLineEditPV =           new QLineEdit("PV");
    m_pLineEditPA =           new QLineEdit("PA");
    m_pLineEditPM =           new QLineEdit("PM");
    m_pLineEditForce =        new QLineEdit("Force");
    m_pLineEditDexterite =    new QLineEdit("Dexterite");
    m_pLineEditIntelligence = new QLineEdit("Intelligence");
    m_pLineEditProtection =   new QLineEdit("Protection");
    m_pLineEditArmure =       new QLineEdit("Armure");

    m_pLabelPV =              new QLabel("PV");
    m_pLabelPA =              new QLabel("PA");
    m_pLabelPM =              new QLabel("PM");
    m_pLabelForce =           new QLabel("Force");
    m_pLabelDexterite =       new QLabel("Dexterite");
    m_pLabelIntelligence =    new QLabel("Intelligence");
    m_pLabelProtection =      new QLabel("Protection");
    m_pLabelArmure =          new QLabel("Armure");

    m_pMainLayoutStats->addWidget(m_pLabelStats);
    m_pMainLayoutStats->addWidget(m_pLabelPV);
    m_pMainLayoutStats->addWidget(m_pLineEditPV);
    m_pMainLayoutStats->addWidget(m_pLabelPA);
    m_pMainLayoutStats->addWidget(m_pLineEditPA);
    m_pMainLayoutStats->addWidget(m_pLabelPM);
    m_pMainLayoutStats->addWidget(m_pLineEditPM);
    m_pMainLayoutStats->addWidget(m_pLabelForce);
    m_pMainLayoutStats->addWidget(m_pLineEditForce);
    m_pMainLayoutStats->addWidget(m_pLabelDexterite);
    m_pMainLayoutStats->addWidget(m_pLineEditDexterite);
    m_pMainLayoutStats->addWidget(m_pLabelIntelligence);
    m_pMainLayoutStats->addWidget(m_pLineEditIntelligence);
    m_pMainLayoutStats->addWidget(m_pLabelProtection);
    m_pMainLayoutStats->addWidget(m_pLineEditProtection);
    m_pMainLayoutStats->addWidget(m_pLabelArmure);
    m_pMainLayoutStats->addWidget(m_pLineEditArmure);

    this->setLayout(m_pMainLayoutStats);

}

StatsWidgetEdit::~StatsWidgetEdit()
{
    if(m_pLabelStats != NULL)
    {
        delete m_pLabelStats;
    }
    if(m_pLineEditPV != NULL)
    {
        delete m_pLineEditPV;
    }
    if(m_pLineEditPA != NULL)
    {
        delete m_pLineEditPA;
    }
    if(m_pLineEditPM != NULL)
    {
        delete m_pLineEditPM;
    }
    if(m_pLineEditForce != NULL)
    {
        delete m_pLineEditForce;
    }
    if(m_pLineEditDexterite != NULL)
    {
        delete m_pLineEditDexterite;
    }
    if(m_pLineEditIntelligence != NULL)
    {
        delete m_pLineEditIntelligence;
    }
    if(m_pLineEditProtection != NULL)
    {
        delete m_pLineEditProtection;
    }
    if(m_pLineEditArmure != NULL)
    {
        delete m_pLineEditArmure;
    }
    if(m_pMainLayoutStats != NULL)
    {
        delete m_pMainLayoutStats;
    }
}

void StatsWidgetEdit::refreshStatsView(Stats stats)
{
    m_pLineEditPV->setText(QString::number(stats.m_PV));
    m_pLineEditPA->setText(QString::number(stats.m_PA));
    m_pLineEditPM->setText(QString::number(stats.m_PM));
    m_pLineEditForce->setText(QString::number(stats.m_Force));
    m_pLineEditDexterite->setText(QString::number(stats.m_Dexterite));
    m_pLineEditIntelligence->setText(QString::number(stats.m_Intelligence));
    m_pLineEditProtection->setText(QString::number(stats.m_Protection));
    m_pLineEditArmure->setText(QString::number(stats.m_Armure));
}

Stats StatsWidgetEdit::getStatsValues()
{
    Stats stats;

    stats.m_PV = m_pLineEditPV->text().toInt();
    stats.m_PM = m_pLineEditPM->text().toInt();
    stats.m_PA = m_pLineEditPA->text().toInt();
    stats.m_Force = m_pLineEditForce->text().toInt();
    stats.m_Dexterite = m_pLineEditDexterite->text().toInt();
    stats.m_Intelligence = m_pLineEditIntelligence->text().toInt();
    stats.m_Protection = m_pLineEditProtection->text().toInt();
    stats.m_Armure = m_pLineEditArmure->text().toInt();

    return stats;
}
