#include "cancelSaveHeroWidgetEdit.h"

#include "QDebug"
#include<QFileDialog>


CancelSaveHeroWidgetEdit::CancelSaveHeroWidgetEdit(QWidget *parent) : QWidget(parent)
{

    m_pLoadSaveHeroLayout = new QVBoxLayout();

    m_pCancelEdition      = new QPushButton("Cancel Edition");
    m_pSaveHero           = new QPushButton("Save Hero");

    m_pLoadSaveHeroLayout->addWidget(m_pCancelEdition);
    m_pLoadSaveHeroLayout->addWidget(m_pSaveHero);

    this->setLayout(m_pLoadSaveHeroLayout);

}

CancelSaveHeroWidgetEdit::~CancelSaveHeroWidgetEdit()
{
    if(m_pCancelEdition != NULL)
    {
        delete m_pCancelEdition;
    }
    if(m_pSaveHero != NULL)
    {
        delete m_pSaveHero;
    }
    if(m_pLoadSaveHeroLayout != NULL)
    {
        delete m_pLoadSaveHeroLayout;
    }
}

QPushButton *CancelSaveHeroWidgetEdit::getBtnCancelEdition()
{
    return m_pCancelEdition;
}

QPushButton *CancelSaveHeroWidgetEdit::getBtnSaveHero()
{
    return m_pSaveHero;
}


