#ifndef SPRITE_COMP
#define SPRITE_COMP

#include "Component.h"
#include "Actor.h"
#include "Libs/Math.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SpriteComponent : public Component 
{
public:
    //lower draw order -> background
    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();
    virtual void Draw(SDL_Renderer* renderer);
    virtual void SetTexture(SDL_Texture* texture);

    int GetDrawOrder () const { return mDrawOrder; }
    int GetTextureHeight() const { return mTextureHeight; }
    int GetTextureWidth() const { return mTextureWidth; }

protected:
    SDL_Texture* mTexture;
    int mDrawOrder;
    int mTextureHeight;
    int mTextureWidth;
};

#endif