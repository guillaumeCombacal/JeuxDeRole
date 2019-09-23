#ifndef ANIMATION_SPRITE_H
#define ANIMATION_SPRITE_H

#define FREQUENCE_TIMER_SPRITE_ANIMATION 50 // Base Frequency for all sprites

class AnimationSprite
{

private:
    int m_countTimeout; // nb of times FREQUENCE_TIMER_SPRITE_ANIMATION is called. Call nextState() when timeout is reached

protected:

    int m_currentStateFrame;// enum of the current state
    int m_timeoutSignal_ms;// timeout in ms to changing state, and then coords

    virtual void updateCoordSprite(int i_stateFrame) = 0;
    virtual void nextState() = 0;


public:
     AnimationSprite();
     virtual ~AnimationSprite();

     virtual void updateAnimationSprite();


};

#endif // ANIMATION_SPRITE_H
