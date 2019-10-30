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

    inline void setBattleMapRendering(bool i_bIsRendering){m_bIsRendering = i_bIsRendering;}
    inline void setBattleMapData(BattleMapData* i_pBattleMapData){m_pBattleMapData = i_pBattleMapData;}

private:

    OpenGlRenderSingleton();
    static OpenGlRenderSingleton* m_pInstance;

    BattleMapRender* m_pBattleMapRender;
    BattleMapData* m_pBattleMapData;

    bool m_bIsRendering;

};

#endif // OPENGL_RENDER_SINGLETON
