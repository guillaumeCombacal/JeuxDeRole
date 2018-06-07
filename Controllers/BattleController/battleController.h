#ifndef BATTLECONTROLLER_H
#define BATTLECONTROLLER_H

#include"battleWidget.h"

class BattleController
{

private:

    BattleWidget *m_pBattleWidget;

public:
    BattleController();
    ~BattleController();

    BattleWidget *getBattleWidget();
};

#endif // BATTLECONTROLLER_H
