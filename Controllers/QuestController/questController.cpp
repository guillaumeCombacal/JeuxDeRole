#include "questController.h"

QuestController::QuestController()
{
    m_pQuestWidget = new QuestWidget();
}

QuestController::~QuestController()
{
    if(m_pQuestWidget != NULL)
    {
        delete m_pQuestWidget;
    }
}

QuestWidget *QuestController::getQuestWidget()
{
    return m_pQuestWidget;
}
