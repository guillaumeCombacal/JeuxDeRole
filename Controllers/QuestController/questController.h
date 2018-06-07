#ifndef QUESTCONTROLLER_H
#define QUESTCONTROLLER_H

#include"questWidget.h"

class QuestController
{

private:
    QuestWidget *m_pQuestWidget;

public:
    QuestController();
    ~QuestController();

    QuestWidget *getQuestWidget();

};

#endif // QUESTCONTROLLER_H
