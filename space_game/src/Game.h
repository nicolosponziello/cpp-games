#pragma once

#include "Actor.h"
#include "Constants.h"
#include "Component.h"
//#include "SpriteComponent.h"
//#include "BGSpriteComponent.h"
#include <SDL2/SDL.h>
#include <vector>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include <algorithm>

class Game
{
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor *actor);
    void RemoveActor(class Actor *actor);

    void AddSprite(class SpriteComponent *sprite);
    void RemoveSprite(class SpriteComponent *sprite);

    SDL_Texture *GetTexture(const std::string &filename);

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    void LoadData();
    void UnloadData();

    SDL_Window *mWindow;
    bool mIsRunning;
    SDL_Renderer *mRenderer;
    Uint32 mTickCount;

    //actor stuff
    std::vector<class Actor *> mActors;
    std::vector<class Actor *> mPendingActors;
    bool mIsUpdatingActors;

    //sprites
    std::vector<class SpriteComponent *> mSprites;

    //textures
    std::map<std::string, SDL_Texture *> textures;

    class Ship *ship;

    class TestAnim *testAnim;
};