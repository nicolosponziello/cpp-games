#include "TestAnim.h"
#include "Game.h"
#include "AnimSpriteComponent.h"
#include <vector>

TestAnim::TestAnim(Game *game)
    : Actor(game)
{
    mSprite = new AnimSpriteComponent(this);
    std::vector<SDL_Texture *> anims = {
        game->GetTexture("assets/Character01.png"),
        game->GetTexture("assets/Character02.png"),
        game->GetTexture("assets/Character03.png"),
        game->GetTexture("assets/Character04.png"),
        game->GetTexture("assets/Character05.png"),
        game->GetTexture("assets/Character06.png"),
        game->GetTexture("assets/Character07.png"),
        game->GetTexture("assets/Character08.png"),
        game->GetTexture("assets/Character09.png"),
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
    mSprite->AddNewAnimation(0, 5, TestAnim::WALKING, true);
    mSprite->AddNewAnimation(6, 14, TestAnim::JUMPING, false);
    mSprite->AddNewAnimation(15, 18, TestAnim::PUNCH, false);

    mSprite->SetAnimFPS(15.0f);
    mSprite->SetDefaultAnimation(TestAnim::WALKING);
}

void TestAnim::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
}

void TestAnim::ProcessKeyboard(const u_int8_t *state)
{
    if (state[SDL_SCANCODE_K])
    {
        mSprite->PlayAnimation(TestAnim::JUMPING);
    }
    if (state[SDL_SCANCODE_L])
    {
        mSprite->PlayAnimation(TestAnim::PUNCH);
    }
}