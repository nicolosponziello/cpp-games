#include "AnimSpriteComponent.h"
#include "Actor.h"

AnimSpriteComponent::AnimSpriteComponent(Actor *owner, int drawOrder)
    : SpriteComponent(owner, drawOrder),
      mCurrentFrame(0.0f),
      mAnimFPS(24.0f)
{
}

AnimSpriteComponent::~AnimSpriteComponent()
{
}

void AnimSpriteComponent::SetAnimationTextures(const std::vector<SDL_Texture *> &textures)
{
    mAnimTextures = textures;
    mCurrentFrame = 0;
    if (mAnimTextures.size() > 0)
    {
        SpriteComponent::SetTexture(textures[0]);
    }
}

void AnimSpriteComponent::Update(float deltaTime)
{
    SpriteComponent::Update(deltaTime);

    if (mAnimTextures.size() > 0)
    {
        //update current frame with fps and delta time
        mCurrentFrame += mAnimFPS * deltaTime;

        //wrap and restart animation if ended
        while (mCurrentFrame >= mAnimTextures.size())
        {
            mCurrentFrame -= mAnimTextures.size();
        }

        //set current texture
        SetTexture(mAnimTextures[static_cast<int>(mCurrentFrame)]);
    }
}

void AnimSpriteComponent::AddNewAnimation(int a, int b, AnimationTypes type)
{
    mAnimations.insert({type, Animation(a, b)});
}

void AnimSpriteComponent::PlayAnimation(AnimationTypes type)
{
    mCurrentFrame = mAnimations.find(type)->second.GetStartIndex();
}