#include "questObjectWidget.h"

#include "QDebug"


QuestObjectWidget::QuestObjectWidget(QWidget *parent) : QWidget(parent)
{
    m_pQuestObjectLayout     = new QVBoxLayout();

    m_pQuestObjectLabel      = new QLabel("Objet de quête");
    m_pQuestObjectListWidget = new QListWidget();

    m_pQuestObjectLayout->addWidget(m_pQuestObjectLabel);
    m_pQuestObjectLayout->addWidget(m_pQuestObjectListWidget);

    this->setLayout(m_pQuestObjectLayout);
}

QuestObjectWidget::~QuestObjectWidget()
{
    if(m_pQuestObjectLabel != NULL)
    {
        delete m_pQuestObjectLabel;
    }
    if(m_pQuestObjectListWidget != NULL)
    {
        delete m_pQuestObjectListWidget;
    }
    if(m_pQuestObjectLayout != NULL)
    {
        delete m_pQuestObjectLayout;
    }
}

void QuestObjectWidget::refreshQuestView(QuestObject questObject)
{
    m_pQuestObjectListWidget->clear();

    std::map<QString, int>::iterator it;
    for(it = questObject.m_mapQuestObject.begin();it != questObject.m_mapQuestObject.end(); ++it)
    {
        QString element = it->first + " " + QString::number(it->second);
        m_pQuestObjectListWidget->addItem(element);
    }

}

