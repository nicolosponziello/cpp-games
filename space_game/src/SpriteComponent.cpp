#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
    :Component(owner),
    mTexture(nullptr),
    mDrawOrder(drawOrder),
    mTextureHeight(0),
    mTextureWidth(0)
{
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
    //set texture
    mTexture = texture;
    //set values
    SDL_QueryTexture(texture, nullptr, nullptr, &mTextureWidth, &mTextureHeight);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
    if(mTexture)
    {
        SDL_Rect rect;
        rect.w = static_cast<int>(mTextureWidth * mOwner->GetScale());
        rect.h = static_cast<int>(mTextureHeight * mOwner->GetScale());

        rect.x = static_cast<int>(mOwner->GetPosition().x - rect.w / 2);
        rect.y = static_cast<int>(mOwner->GetPosition().y - rect.h / 2);

        //draw
        SDL_RenderCopyEx(renderer, mTexture, nullptr, &rect, Math::ToDegrees(mOwner->GetRotation()), nullptr, SDL_FLIP_NONE);

    }
}