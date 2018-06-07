#include "bagPackWidget.h"

#include "QDebug"


BagPackWidget::BagPackWidget(QWidget *parent) : QWidget(parent)
{
    m_pBagPackLayout     = new QVBoxLayout();

    m_pBagPackLabel      = new QLabel("Sac");
    m_pBagPackListWidget = new QListWidget(); 

    m_pFoodLabel         = new QLabel("Food");
    m_pOrLabel           = new QLabel("Or");

    m_pFoodLabelValue    = new QLabel("");
    m_pOrLabelValue      = new QLabel("");

    m_pBagPackLayout->addWidget(m_pFoodLabel);
    m_pBagPackLayout->addWidget(m_pFoodLabelValue);
    m_pBagPackLayout->addWidget(m_pOrLabel);
    m_pBagPackLayout->addWidget(m_pOrLabelValue);
    m_pBagPackLayout->addWidget(m_pBagPackLabel);
    m_pBagPackLayout->addWidget(m_pBagPackListWidget);

    this->setLayout(m_pBagPackLayout);
}

BagPackWidget::~BagPackWidget()
{
    if(m_pBagPackLabel != NULL)
    {
        delete m_pBagPackLabel;
    }

    if(m_pFoodLabel != NULL)
    {
        delete m_pFoodLabel;
    }

    if(m_pFoodLabelValue != NULL)
    {
        delete m_pFoodLabelValue;
    }

    if(m_pOrLabel != NULL)
    {
        delete m_pOrLabel;
    }

    if(m_pOrLabelValue != NULL)
    {
        delete m_pOrLabelValue;
    }

    if(m_pBagPackListWidget != NULL)
    {
        delete m_pBagPackListWidget;
    }
    if(m_pBagPackLayout != NULL)
    {
        delete m_pBagPackLayout;
    }
}

void BagPackWidget::refreshBagView(Bag bag)
{
    m_pFoodLabelValue->setText(QString::number(bag.m_Nourriture));
    m_pOrLabelValue->setText(QString::number(bag.m_Or));

    m_pBagPackListWidget->clear();

    std::map<QString, int>::iterator it;
    for(it = bag.m_mapBag.begin();it != bag.m_mapBag.end(); ++it)
    {
        QString element = it->first + " " + QString::number(it->second);
        m_pBagPackListWidget->addItem(element);
    }
}



