#include "featureHeroWidgetEdit.h"

#include "QDebug"


FeatureHeroWidgetEdit::FeatureHeroWidgetEdit(QWidget *parent) : QWidget(parent)
{

    m_pFeatureHeroLayout = new QGridLayout();

    m_pBtnImgFaceHero    = new QPushButton("ImgFaceHero");
    m_filenameImgFaceHero= "";

    m_pName              = new QLineEdit("Name");
    m_pLevel             = new QLineEdit("Level");
    m_pJob               = new QLineEdit("Job");
    m_pRace              = new QLineEdit("Race");
    m_pSexe              = new QLineEdit("Sexe");
    m_pXp                = new QLineEdit("Xp");

    m_pLabelName         = new QLabel("Name");
    m_pLabelLevel        = new QLabel("Level");
    m_pLabelJob          = new QLabel("Job");
    m_pLabelRace         = new QLabel("Race");
    m_pLabelSexe         = new QLabel("Sexe");
    m_pLabelXp           = new QLabel("Xp");

    m_pBtnImgFaceHero->setFixedHeight(200);
    m_pBtnImgFaceHero->setFixedWidth(200);

    m_pFeatureHeroLayout->addWidget(m_pBtnImgFaceHero,0,0,3,3);

    m_pFeatureHeroLayout->addWidget(m_pLabelName,3,0,1,1);
    m_pFeatureHeroLayout->addWidget(m_pName,4,0,1,1);
    m_pFeatureHeroLayout->addWidget(m_pLabelRace,3,1,1,1);
    m_pFeatureHeroLayout->addWidget(m_pRace,4,1,1,1);
    m_pFeatureHeroLayout->addWidget(m_pLabelSexe,3,2,1,1);
    m_pFeatureHeroLayout->addWidget(m_pSexe,4,2,1,1);

    m_pFeatureHeroLayout->addWidget(m_pLabelLevel,5,0,1,1);
    m_pFeatureHeroLayout->addWidget(m_pLevel,6,0,1,1);
    m_pFeatureHeroLayout->addWidget(m_pLabelXp,5,1,1,1);
    m_pFeatureHeroLayout->addWidget(m_pXp,6,1,1,1);
    m_pFeatureHeroLayout->addWidget(m_pLabelJob,5,2,1,1);
    m_pFeatureHeroLayout->addWidget(m_pJob,6,2,1,1);

    this->setLayout(m_pFeatureHeroLayout);
}

FeatureHeroWidgetEdit::~FeatureHeroWidgetEdit()
{
    if(m_pBtnImgFaceHero != NULL)
    {
        delete m_pBtnImgFaceHero;
    }
    if(m_pName != NULL)
    {
        delete m_pName;
    }
    if(m_pLevel != NULL)
    {
        delete m_pLevel;
    }
    if(m_pJob != NULL)
    {
        delete m_pJob;
    }
    if(m_pRace != NULL)
    {
        delete m_pRace;
    }
    if(m_pFeatureHeroLayout != NULL)
    {
        delete m_pFeatureHeroLayout;
    }
}

void FeatureHeroWidgetEdit::refreshFeatureView(Feature feature)
{
    m_pName->setText(feature.m_Name);
    m_pLevel->setText(QString::number(feature.m_Lvl));
    m_pJob->setText(feature.m_Job);
    m_pRace->setText(feature.m_Race);
    m_pXp->setText(QString::number(feature.m_Xp));
    m_pSexe->setText(feature.m_Sexe);
    m_filenameImgFaceHero = feature.m_FilenameImgFace;

    // Refresh IMG inside the QPushButton
    if(feature.m_FilenameImgFace != "")
    {
        QImage imgFaceHero(feature.m_FilenameImgFace);
        imgFaceHero = imgFaceHero.scaled(m_pBtnImgFaceHero->width(), m_pBtnImgFaceHero->height(), Qt::KeepAspectRatioByExpanding);

        QIcon buttonIcon(QPixmap::fromImage(imgFaceHero));
        m_pBtnImgFaceHero->setIconSize(m_pBtnImgFaceHero->size());
        m_pBtnImgFaceHero->setIcon(buttonIcon);

        // Rend le text et le fond invisible
        m_pBtnImgFaceHero->setText("");
        m_pBtnImgFaceHero->setStyleSheet("QPushButton{background: transparent}");
    }

}

Feature FeatureHeroWidgetEdit::getFeatureValues()
{
    Feature feature;

    feature.m_Job  = m_pJob->text();
    feature.m_Lvl  = m_pLevel->text().toInt();
    feature.m_Name = m_pName->text();
    feature.m_Race = m_pRace->text();
    feature.m_Xp   = m_pXp->text().toInt();
    feature.m_Sexe = m_pSexe->text();
    feature.m_FilenameImgFace = m_filenameImgFaceHero;

    return feature;
}

QPushButton* FeatureHeroWidgetEdit::getBtnImgHero()
{
    return m_pBtnImgFaceHero;
}

