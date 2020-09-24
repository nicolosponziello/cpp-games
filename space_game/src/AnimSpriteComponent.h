#pragma once

#include "SpriteComponent.h"
#include <vector>
#include <map>
#include "Animation.h"

class AnimSpriteComponent : public SpriteComponent
{
public:
    AnimSpriteComponent(class Actor *owner, int drawOrder = 100);
    ~AnimSpriteComponent();

    //update animation every frame
    void Update(float deltaTime) override;

    //set textures for animations
    void SetAnimationTextures(const std::vector<SDL_Texture *> &textures);

    //set/get FPS
    float GetAnimFPS() const { return mAnimFPS; }
    void SetAnimFPS(float fps) { mAnimFPS = fps; }

    void AddNewAnimation(int a, int b, AnimationTypes type);

    void PlayAnimation(AnimationTypes type);

private:
    std::vector<SDL_Texture *> mAnimTextures;

    float mCurrentFrame;

    float mAnimFPS;

    std::map<AnimationTypes, Animation> mAnimations;
};