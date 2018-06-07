#include "featureHeroWidget.h"

#include "QImage"
#include "QDebug"


FeatureHeroWidget::FeatureHeroWidget(QWidget *parent) : QWidget(parent)
{

    m_pFeatureHeroLayout = new QGridLayout();

    m_pLabelImgFaceHero  = new QLabel("Image Face Hero");

    m_pLabelName              = new QLabel("Name");
    m_pLabelLevel             = new QLabel("Level");
    m_pLabelJob               = new QLabel("Job");
    m_pLabelRace              = new QLabel("Race");
    m_pLabelSexe              = new QLabel("Sexe");
    m_pLabelXp                = new QLabel("XP");

    m_pLabelNameValue         = new QLabel("");
    m_pLabelLevelValue        = new QLabel("");
    m_pLabelJobValue          = new QLabel("");
    m_pLabelRaceValue         = new QLabel("");
    m_pLabelSexeValue         = new QLabel("");
    m_pLabelXpValue           = new QLabel("");

    m_pLabelImgFaceHero->setFixedHeight(200);
    m_pLabelImgFaceHero->setFixedWidth(200);

    m_pFeatureHeroLayout->addWidget(m_pLabelImgFaceHero,0,0,3,3);

    // Colonne 1
    m_pFeatureHeroLayout->addWidget(m_pLabelName,4,0,1,1);
    m_pFeatureHeroLayout->addWidget(m_pLabelNameValue,5,0,1,1);
    m_pFeatureHeroLayout->addWidget(m_pLabelLevel,6,0,1,1);
    m_pFeatureHeroLayout->addWidget(m_pLabelLevelValue,7,0,1,1);

    // Colonne 2
    m_pFeatureHeroLayout->addWidget(m_pLabelRace,4,1,1,1);
    m_pFeatureHeroLayout->addWidget(m_pLabelRaceValue,5,1,1,1);
    m_pFeatureHeroLayout->addWidget(m_pLabelXp,6,1,1,1);
    m_pFeatureHeroLayout->addWidget(m_pLabelXpValue,7,1,1,1);

    // Colonne 3
    m_pFeatureHeroLayout->addWidget(m_pLabelSexe,4,2,1,1);
    m_pFeatureHeroLayout->addWidget(m_pLabelSexeValue,5,2,1,1);
    m_pFeatureHeroLayout->addWidget(m_pLabelJob,6,2,1,1);
    m_pFeatureHeroLayout->addWidget(m_pLabelJobValue,7,2,1,1);

    this->setLayout(m_pFeatureHeroLayout);
}

FeatureHeroWidget::~FeatureHeroWidget()
{
    if(m_pLabelImgFaceHero != NULL)
    {
        delete m_pLabelImgFaceHero;
    }
    if(m_pLabelName != NULL)
    {
        delete m_pLabelName;
    }
    if(m_pLabelNameValue != NULL)
    {
        delete m_pLabelNameValue;
    }
    if(m_pLabelLevel != NULL)
    {
        delete m_pLabelLevel;
    }
    if(m_pLabelLevelValue != NULL)
    {
        delete m_pLabelLevelValue;
    }
    if(m_pLabelJob != NULL)
    {
        delete m_pLabelJob;
    }
    if(m_pLabelJobValue != NULL)
    {
        delete m_pLabelJobValue;
    }
    if(m_pLabelRace != NULL)
    {
        delete m_pLabelRace;
    }
    if(m_pLabelRaceValue != NULL)
    {
        delete m_pLabelRaceValue;
    }
    if(m_pLabelXp != NULL)
    {
        delete m_pLabelXp;
    }
    if(m_pLabelXpValue != NULL)
    {
        delete m_pLabelXpValue;
    }
    if(m_pLabelSexe != NULL)
    {
        delete m_pLabelSexe;
    }
    if(m_pLabelSexeValue != NULL)
    {
        delete m_pLabelSexeValue;
    }
    if(m_pFeatureHeroLayout != NULL)
    {
        delete m_pFeatureHeroLayout;
    }
}

void FeatureHeroWidget::refreshFeatureView(Feature feature)
{
    qDebug()<<"FeatureHeroWidget::refreshFeatureView";

    m_pLabelNameValue->setText(feature.m_Name);
    m_pLabelLevelValue->setText(QString::number(feature.m_Lvl));
    m_pLabelJobValue->setText(feature.m_Job);
    m_pLabelRaceValue->setText(feature.m_Race);
    m_pLabelXpValue->setText(QString::number(feature.m_Xp));
    m_pLabelSexeValue->setText(feature.m_Sexe);

    // Refresh IMG hero
    QImage imgFaceHero(feature.m_FilenameImgFace);
    imgFaceHero = imgFaceHero.scaled(m_pLabelImgFaceHero->width(), m_pLabelImgFaceHero->height(), Qt::KeepAspectRatio);

    m_pLabelImgFaceHero->setPixmap(QPixmap::fromImage(imgFaceHero));
    m_pLabelImgFaceHero->setAlignment(Qt::AlignCenter);
}

