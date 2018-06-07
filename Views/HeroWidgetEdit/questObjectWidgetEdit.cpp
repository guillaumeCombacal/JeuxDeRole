#include "questObjectWidgetEdit.h"

#include "QDebug"
#include "QLineEdit"

QuestObjectWidgetEdit::QuestObjectWidgetEdit(QWidget *parent) : QWidget(parent)
{
    m_pQuestObjectLayout       = new QGridLayout();

    m_pQuestObjectLabel        = new QLabel("Objet de quête");
    m_pQuestObjectListWidget   = new QListWidget();

    m_pBtnAddInListWidget      = new QPushButton("Add Item");
    m_pBtnRemoveFromListWidget = new QPushButton("Remove Item");

    m_pLineEditNameQuestObj    = new QLineEdit("");
    m_pLineEditNumber          = new QLineEdit("");

    m_pQuestObjectLayout->addWidget(m_pQuestObjectLabel, 0, 0, 1, 1);
    m_pQuestObjectLayout->addWidget(m_pQuestObjectListWidget, 1, 0, 3, 4);

    m_pQuestObjectLayout->addWidget(m_pBtnAddInListWidget, 4, 0, 1, 1);
    m_pQuestObjectLayout->addWidget(m_pBtnRemoveFromListWidget, 4, 1, 1, 1);

    m_pQuestObjectLayout->addWidget(m_pLineEditNameQuestObj, 4, 2, 1, 1);
    m_pQuestObjectLayout->addWidget(m_pLineEditNumber, 4, 3, 1, 1);

    this->setLayout(m_pQuestObjectLayout);
}

QuestObjectWidgetEdit::~QuestObjectWidgetEdit()
{
    if(m_pQuestObjectLabel != NULL)
    {
        delete m_pQuestObjectLabel;
    }
    if(m_pQuestObjectListWidget != NULL)
    {
        delete m_pQuestObjectListWidget;
    }
    if(m_pBtnAddInListWidget != NULL)
    {
        delete m_pBtnAddInListWidget;
    }
    if(m_pBtnRemoveFromListWidget != NULL)
    {
        delete m_pBtnRemoveFromListWidget;
    }
    if(m_pLineEditNameQuestObj != NULL)
    {
        delete m_pLineEditNameQuestObj;
    }
    if(m_pLineEditNumber != NULL)
    {
        delete m_pLineEditNumber;
    }
    if(m_pQuestObjectLayout != NULL)
    {
        delete m_pQuestObjectLayout;
    }
}

void QuestObjectWidgetEdit::refreshQuestViewEdit(QuestObject questObject)
{
    qDebug()<<"refreshQuestView";

    m_pQuestObjectListWidget->clear();

    std::map<QString, int>::iterator it;
    for(it = questObject.m_mapQuestObject.begin();it != questObject.m_mapQuestObject.end(); ++it)
    {
        QString element = it->first + " " + QString::number(it->second);
        m_pQuestObjectListWidget->addItem(element);
    }
}

QuestObject QuestObjectWidgetEdit::getQuestObjectValues()
{
    QuestObject questObject;

    questObject.m_mapQuestObject.clear();

    for(int i = 0; i < m_pQuestObjectListWidget->count(); i++)
    {
        QStringList list = m_pQuestObjectListWidget->item(i)->text().split(' ');
        std::pair<QString, int> pairElement(list.at(0), list.at(1).toInt());
        questObject.m_mapQuestObject.insert(pairElement);
    }

    return questObject;
}

QPushButton* QuestObjectWidgetEdit::getBtnAddQuestObj()
{
  return m_pBtnAddInListWidget;
}

QPushButton* QuestObjectWidgetEdit::getBtnRemoveQuestObj()
{
  return m_pBtnRemoveFromListWidget;
}

QString QuestObjectWidgetEdit::getValueQuestObj()
{
    return m_pLineEditNameQuestObj->text();
}

QString QuestObjectWidgetEdit::getValueNumberQuestObj()
{
    return m_pLineEditNumber->text();
}

