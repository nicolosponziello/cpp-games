#include "BGSpriteComponent.h"

BGSpriteComponent::BGSpriteComponent(class Actor *owner, int drawOrder)
    : SpriteComponent(owner, drawOrder),
      mScrollSpeed(0.0f)
{
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture *> &textures)
{
    int count = 0;
    for (auto text : textures)
    {
        BGTexture tmp;
        tmp.mTexture = text;

        tmp.mOffset.x = count * mScreenSize.x;
        tmp.mOffset.y = 0;
        mBGTexture.emplace_back(tmp);
        count++;
    }
}

void BGSpriteComponent::Update(float deltaTime)
{
    SpriteComponent::Update(deltaTime);

    for (auto &bg : mBGTexture)
    {
        //update x to make an infinite scrolling effect
        bg.mOffset.x += mScrollSpeed * deltaTime;
        if (bg.mOffset.x < -mScreenSize.x)
        {
            bg.mOffset.x = (mBGTexture.size() - 1) * mScreenSize.x - 1;
        }
    }
}

void BGSpriteComponent::Draw(SDL_Renderer *renderer)
{
    for (auto &bg : mBGTexture)
    {
        SDL_Rect rect;
        rect.w = static_cast<int>(mScreenSize.x);
        rect.h = static_cast<int>(mScreenSize.y);

        rect.x = static_cast<int>(mOwner->GetPosition().x - rect.w / 2 + bg.mOffset.x);
        rect.y = static_cast<int>(mOwner->GetPosition().y - rect.h / 2 + bg.mOffset.y);

        SDL_RenderCopy(renderer, bg.mTexture, nullptr, &rect);
    }
}