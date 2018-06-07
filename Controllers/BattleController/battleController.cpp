#include "battleController.h"

BattleController::BattleController()
{
    m_pBattleWidget = new BattleWidget();
}

BattleController::~BattleController()
{
    if(m_pBattleWidget != NULL)
    {
        delete m_pBattleWidget;
    }
}

BattleWidget *BattleController::getBattleWidget()
{
    return m_pBattleWidget;
}
