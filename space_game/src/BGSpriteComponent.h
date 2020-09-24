#ifndef BG_COMP
#define BG_COMP

#include "SpriteComponent.h"
#include "Actor.h"
#include <SDL2/SDL.h>
#include <vector>

class BGSpriteComponent : public SpriteComponent
{
public:
    //lower draw order to be painted in the background
    BGSpriteComponent(class Actor* owner, int drawOrder = 10);
    
    //update and draw overridden from parent
    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;

    //set backgrund textures
    void SetBGTextures(const std::vector<SDL_Texture*>& textures);

    //screen size and scroll speed
    void SetScreenSize(const Vector2& size) { mScreenSize = size; }
    Vector2 GetScreenSize() const { return mScreenSize; }
    void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
    float GetScrollSpeed() const { return mScrollSpeed; }
private:
    struct BGTexture
    {
        SDL_Texture* mTexture;
        Vector2 mOffset;
    };
    std::vector<BGTexture> mBGTexture;
    Vector2 mScreenSize;
    float mScrollSpeed;
};  

#endif