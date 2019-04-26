#ifndef OPENGL_RENDER_SINGLETON
#define OPENGL_RENDER_SINGLETON

#include "BattleMapRender.h"
#include "BattleMapData.h"

class OpenGlRenderSingleton
{

public:
    ~OpenGlRenderSingleton();

    inline static OpenGlRenderSingleton* getInstance()
    {
        if(m_pInstance == NULL)
        {
            m_pInstance = new OpenGlRenderSingleton();
        }

        return m_pInstance;
    }

    void init();
    void render();
    inline void setBattleMapData(BattleMapData battleMapData){m_battleMapData=battleMapData;}
    //inline void setBattleMapRender(BattleMapRender* pBattleMapRender){m_pBattleMapRender=pBattleMapRender;}

private:

    OpenGlRenderSingleton();
    static OpenGlRenderSingleton* m_pInstance;

    BattleMapRender* m_pBattleMapRender;
    BattleMapData m_battleMapData;

};

#endif // OPENGL_RENDER_SINGLETON
