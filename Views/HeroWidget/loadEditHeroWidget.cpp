#include "loadEditHeroWidget.h"

#include "QDebug"
#include<QFileDialog>


LoadEditHeroWidget::LoadEditHeroWidget(QWidget *parent) : QWidget(parent)
{

    m_pLoadSaveHeroLayout = new QVBoxLayout();

    m_pBtnLoadHero        = new QPushButton("Load Hero");
    m_pBtnEditHero        = new QPushButton("Edit Hero");
    m_pBtnAddNewHero      = new QPushButton("Add New Hero");

    m_pLoadSaveHeroLayout->addWidget(m_pBtnLoadHero);
    m_pLoadSaveHeroLayout->addWidget(m_pBtnEditHero);
    m_pLoadSaveHeroLayout->addWidget(m_pBtnAddNewHero);

    m_pBtnEditHero->setEnabled(false);

    this->setLayout(m_pLoadSaveHeroLayout);
}

LoadEditHeroWidget::~LoadEditHeroWidget()
{
    if(m_pBtnLoadHero != NULL)
    {
        delete m_pBtnLoadHero;
    }
    if(m_pBtnEditHero != NULL)
    {
        delete m_pBtnEditHero;
    }
    if(m_pBtnAddNewHero != NULL)
    {
        delete m_pBtnAddNewHero;
    }
    if(m_pLoadSaveHeroLayout != NULL)
    {
        delete m_pLoadSaveHeroLayout;
    }
}

QPushButton* LoadEditHeroWidget::getBtnLoadHero()
{
    return m_pBtnLoadHero;
}

QPushButton* LoadEditHeroWidget::getBtnEditHero()
{
    return m_pBtnEditHero;
}

QPushButton* LoadEditHeroWidget::getBtnAddNewHero()
{
    return m_pBtnAddNewHero;
}
