#include "AnimationSprite.h"

#include "QDebug"


AnimationSprite::AnimationSprite():
m_countTimeout(1)
{
}

AnimationSprite::~AnimationSprite()
{
}

void AnimationSprite::updateAnimationSprite()
{
    if(m_timeoutSignal_ms < m_countTimeout * FREQUENCE_TIMER_SPRITE_ANIMATION)
    {
        // Define the next frame state and get the coordinates of the texture
        nextState();
        updateCoordSprite(m_currentStateFrame);
        m_countTimeout = 1;
    }
    else
    {
       m_countTimeout++;
    }

}

