#include "OpenGlRenderSingleton.h"

OpenGlRenderSingleton* OpenGlRenderSingleton::m_pInstance = NULL;


OpenGlRenderSingleton::OpenGlRenderSingleton():
    m_pBattleMapRender(NULL),
    m_pBattleMapData(NULL),
    m_bIsRendering(false)
{
}

void OpenGlRenderSingleton::init()
{
    if(m_pBattleMapData != NULL)
    {
        m_pBattleMapRender = new BattleMapRender(m_pBattleMapData);
        m_pBattleMapRender->initBattleMapRender();
    }
}

void OpenGlRenderSingleton::render()
{
    if(m_pBattleMapRender != NULL && m_bIsRendering)
    {
        m_pBattleMapRender->renderBattleMap();
    }
}
