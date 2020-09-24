#include "TestAnim.h"
#include "Game.h"
#include "AnimSpriteComponent.h"
#include <vector>

TestAnim::TestAnim(Game *game)
    : Actor(game)
{
    mSprite = new AnimSpriteComponent(this);
    std::vector<SDL_Texture *> anims = {
        game->GetTexture("assets/Character1.png"),
        game->GetTexture("assets/Character2.png"),
        game->GetTexture("assets/Character3.png"),
        game->GetTexture("assets/Character4.png"),
        game->GetTexture("assets/Character5.png"),
        game->GetTexture("assets/Character6.png"),
        game->GetTexture("assets/Character7.png"),
        game->GetTexture("assets/Character8.png"),
        game->GetTexture("assets/Character9.png"),
        game->GetTexture("assets/Character10.png"),
        game->GetTexture("assets/Character11.png"),
        game->GetTexture("assets/Character12.png"),
        game->GetTexture("assets/Character13.png"),
        game->GetTexture("assets/Character14.png"),
        game->GetTexture("assets/Character15.png"),
        game->GetTexture("assets/Character16.png"),
        game->GetTexture("assets/Character17.png"),
        game->GetTexture("assets/Character18.png")};
    mSprite->SetAnimationTextures(anims);
    mSprite->AddNewAnimation(0, 4, AnimationTypes::ONE);
    mSprite->AddNewAnimation(5, 15, AnimationTypes::TWO);
    mSprite->AddNewAnimation(15, 17, AnimationTypes::THREE);
}

void TestAnim::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
}

void TestAnim::ProcessKeyboard(const u_int8_t *state)
{
    if (state[SDL_SCANCODE_J])
    {
        mSprite->PlayAnimation(AnimationTypes::ONE);
    }
    if (state[SDL_SCANCODE_K])
    {
        mSprite->PlayAnimation(AnimationTypes::TWO);
    }
    if (state[SDL_SCANCODE_L])
    {
        mSprite->PlayAnimation(AnimationTypes::THREE);
    }
}