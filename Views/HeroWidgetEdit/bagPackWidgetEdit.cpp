#include "bagPackWidgetEdit.h"

#include "QDebug"


BagPackWidgetEdit::BagPackWidgetEdit(QWidget *parent) : QWidget(parent)
{
    m_pBagPackEditLayout       = new QGridLayout();

    m_pBagPackEditLabel        = new QLabel("Sac");
    m_pBagPackEditListWidget   = new QListWidget();
    m_pFoodEditLabel           = new QLabel("Food");
    m_pOrEditLabel             = new QLabel("Or");
    m_pFoodEditLineEdit        = new QLineEdit("Food");
    m_pOrEditLineEdit          = new QLineEdit("Or");

    m_pBtnAddInListWidget      = new QPushButton("Add Item");
    m_pBtnRemoveFromListWidget = new QPushButton("Remove Item");

    m_pLineEditNameItem        = new QLineEdit("");
    m_pLineEditNumber          = new QLineEdit("");

    m_pBagPackEditLayout->addWidget(m_pFoodEditLabel, 0, 0, 1, 1);
    m_pBagPackEditLayout->addWidget(m_pFoodEditLineEdit, 0, 1 ,1, 1);
    m_pBagPackEditLayout->addWidget(m_pOrEditLabel, 0, 2, 1, 1);
    m_pBagPackEditLayout->addWidget(m_pOrEditLineEdit, 0, 3, 1, 1);
    m_pBagPackEditLayout->addWidget(m_pBagPackEditLabel, 1, 0, 1, 1);
    m_pBagPackEditLayout->addWidget(m_pBagPackEditListWidget, 2, 0, 3, 4 );

    m_pBagPackEditLayout->addWidget(m_pBtnAddInListWidget, 5, 0, 1, 1);
    m_pBagPackEditLayout->addWidget(m_pBtnRemoveFromListWidget, 5, 1, 1, 1);

    m_pBagPackEditLayout->addWidget(m_pLineEditNameItem, 5, 2, 1, 1);
    m_pBagPackEditLayout->addWidget(m_pLineEditNumber, 5, 3, 1, 1);

    this->setLayout(m_pBagPackEditLayout);
}

BagPackWidgetEdit::~BagPackWidgetEdit()
{
    if(m_pBagPackEditLabel != NULL)
    {
        delete m_pBagPackEditLabel;
    }

    if(m_pBagPackEditListWidget != NULL)
    {
        delete m_pBagPackEditListWidget;
    }
    if(m_pBtnAddInListWidget != NULL)
    {
        delete m_pBtnAddInListWidget;
    }
    if(m_pBtnRemoveFromListWidget != NULL)
    {
        delete m_pBtnRemoveFromListWidget;
    }
    if(m_pLineEditNameItem != NULL)
    {
        delete m_pLineEditNameItem;
    }
    if(m_pLineEditNumber != NULL)
    {
        delete m_pLineEditNumber;
    }
    if(m_pBagPackEditLayout != NULL)
    {
        delete m_pBagPackEditLayout;
    }
}

void BagPackWidgetEdit::refreshBagView(Bag bag)
{
    m_pFoodEditLineEdit->setText(QString::number(bag.m_Nourriture));
    m_pOrEditLineEdit->setText(QString::number(bag.m_Or));

    m_pBagPackEditListWidget->clear();

    std::map<QString, int>::iterator it;
    for(it = bag.m_mapBag.begin();it != bag.m_mapBag.end(); ++it)
    {
        QString element = it->first + " " + QString::number(it->second);
        m_pBagPackEditListWidget->addItem(element);
    }
}

Bag BagPackWidgetEdit::getBagValues()
{
    Bag bag;

    bag.m_Nourriture = m_pFoodEditLineEdit->text().toInt();
    bag.m_Or = m_pOrEditLineEdit->text().toInt();

    bag.m_mapBag.clear();

    for(int i = 0; i < m_pBagPackEditListWidget->count(); i++)
    {
        QStringList list = m_pBagPackEditListWidget->item(i)->text().split(' ');
        std::pair<QString, int> pairElement(list.at(0), list.at(1).toInt());
        bag.m_mapBag.insert(pairElement);
    }

    return bag;
}

QPushButton* BagPackWidgetEdit::getBtnAddItemInBag()
{
  return m_pBtnAddInListWidget;
}

QPushButton* BagPackWidgetEdit::getBtnRemoveItemFromBag()
{
  return  m_pBtnRemoveFromListWidget;
}

QString BagPackWidgetEdit::getValueNameItem()
{
    return m_pLineEditNameItem->text();
}

QString BagPackWidgetEdit::getValueNumberItem()
{
    return m_pLineEditNumber->text();
}


