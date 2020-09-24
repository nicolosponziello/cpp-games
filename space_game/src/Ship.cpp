#include "Ship.h"
#include "Game.h"
#include "AnimSpriteComponent.h"

Ship::Ship(Game *game)
    : Actor(game),
      mRightSpeed(0.0f),
      mDownSpeed(0.0f)
{

    AnimSpriteComponent *animSprite = new AnimSpriteComponent(this);
    std::vector<SDL_Texture *> anims = {
        game->GetTexture("assets/Ship01.png"),
        game->GetTexture("assets/Ship02.png"),
        game->GetTexture("assets/Ship03.png"),
        game->GetTexture("assets/Ship04.png")};
    animSprite->SetAnimationTextures(anims);
}

void Ship::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    Vector2 pos = GetPosition();
    pos.x += mRightSpeed * deltaTime;
    pos.y += mDownSpeed * deltaTime;

    if (pos.x >= SCREEN_WIDTH - 50)
    {
        pos.x = SCREEN_WIDTH - 50;
    }
    if (pos.x < 35)
    {
        pos.x = 35;
    }
    if (pos.y >= SCREEN_HEIGHT - 30)
    {
        pos.y = SCREEN_HEIGHT - 30;
    }
    if (pos.y < 25)
    {
        pos.y = 25;
    }
    SetPosition(pos);
}

void Ship::ProcessKeyboard(const u_int8_t *state)
{
    mRightSpeed = 0;
    mDownSpeed = 0;

    if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
    {
        mDownSpeed = -250.0f;
    }
    if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])
    {
        mRightSpeed = -250.0f;
    }
    if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
    {
        mDownSpeed = 250.0f;
    }
    if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
    {
        mRightSpeed = 250.0f;
    }
}