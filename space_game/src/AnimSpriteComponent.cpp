#include "AnimSpriteComponent.h"
#include "Actor.h"
#include "TestAnim.h"
AnimSpriteComponent::AnimSpriteComponent(Actor *owner, int drawOrder)
    : SpriteComponent(owner, drawOrder),
      mCurrentFrame(0.0f),
      mAnimFPS(24.0f),
      mCurrentAnimation(Animation(0, 0, false)),
      mDefaultAnimationID(-1)
{
}

AnimSpriteComponent::~AnimSpriteComponent()
{
}

void AnimSpriteComponent::SetAnimationTextures(const std::vector<SDL_Texture *> &textures)
{
    mAnimTextures = textures;
    //mCurrentFrame = 0;
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
        SDL_Log("Frame %d of %d %d %s", static_cast<int>(mCurrentFrame), mCurrentAnimation.GetStartIndex(), mCurrentAnimation.GetEndIndex(), typeid(mOwner).name());

        if (mCurrentAnimation.IsLooping())
        {
            //wrap and restart animation if ended
            while (mCurrentFrame > mCurrentAnimation.GetEndIndex())
            {
                mCurrentFrame = mCurrentAnimation.GetStartIndex();
            }
        }
        else if (mCurrentAnimation.GetEndIndex() <= static_cast<int>(mCurrentFrame))
        {
            if (mDefaultAnimationID != -1)
            {
                this->PlayAnimation(mDefaultAnimationID);
            }
            return;
        }

        //set current texture
        SetTexture(mAnimTextures[static_cast<int>(mCurrentFrame)]);
    }
}

void AnimSpriteComponent::AddNewAnimation(int a, int b, int id, bool looping)
{
    mAnimations.insert({id, Animation(a, b, looping)});
}

void AnimSpriteComponent::PlayAnimation(int id)
{
    mCurrentAnimation = mAnimations.find(id)->second;
    SDL_Log("AnimSprite playing animation %d start %d end %d loop %d", id, mCurrentAnimation.GetStartIndex(), mCurrentAnimation.GetEndIndex(), mCurrentAnimation.IsLooping());
    mCurrentFrame = mCurrentAnimation.GetStartIndex();
}

void AnimSpriteComponent::SetDefaultAnimation(int id)
{
    mDefaultAnimationID = id;
    mCurrentAnimation = mAnimations.find(id)->second;
}