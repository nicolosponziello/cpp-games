#pragma once

#include "Actor.h"

class TestAnim : public Actor
{
public:
    enum TestAnimations
    {
        WALKING,
        JUMPING,
        PUNCH
    };
    TestAnim(class Game *game);
    void UpdateActor(float deltaTime);
    void ProcessKeyboard(const u_int8_t *state);

private:
    class AnimSpriteComponent *mSprite;
};