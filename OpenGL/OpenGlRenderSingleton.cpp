#include "OpenGlRenderSingleton.h"

OpenGlRenderSingleton* OpenGlRenderSingleton::m_pInstance = NULL;


OpenGlRenderSingleton::OpenGlRenderSingleton():
    m_pBattleMapRender(NULL)
{
}

void OpenGlRenderSingleton::init()
{
    //if(m_battleMapData)
    //{
        m_pBattleMapRender = new BattleMapRender(m_battleMapData);
        m_pBattleMapRender->initBattleMapRender();
    //}
}

void OpenGlRenderSingleton::render()
{
    if(m_pBattleMapRender != NULL)
    {
        m_pBattleMapRender->renderBattleMap();
    }

}
