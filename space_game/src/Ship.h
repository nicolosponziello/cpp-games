#ifndef SHIP_ACTOR
#define SHIP_ACTOR

#include "Actor.h"

class Ship : public Actor
{
public:
    enum Animations
    {
        FLYING
    };
    Ship(class Game* game);
    void UpdateActor(float deltaTime);
    void ProcessKeyboard(const u_int8_t* state);
    float GetRightSpeed() const { return mRightSpeed; }
    float GetDownSpeed() const { return mDownSpeed; }
private:
    float mRightSpeed;
    float mDownSpeed;
};

#endif