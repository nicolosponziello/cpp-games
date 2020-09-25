#include "Game.h"
#include "BGSpriteComponent.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "TestAnim.h"
#include <unistd.h>

Game::Game()
{
    mWindow = nullptr;
    mRenderer = nullptr;
    mIsRunning = true;
    mIsUpdatingActors = false;
    ship = nullptr;
}

bool Game::Initialize()
{
    int res = SDL_Init(SDL_INIT_VIDEO);

    //got some error
    if (res != 0)
    {
        SDL_Log("SLD init failed: %s", SDL_GetError());
        return false;
    }

    //proceed creating a window
    mWindow = SDL_CreateWindow(
        "c++ game programming",
        100,
        100,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0);

    //another error
    if (!mWindow)
    {
        SDL_Log("SLD create window failed: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer)
    {
        SDL_Log("SLD create renderer failed: %s", SDL_GetError());
        return false;
    }

    //init image rendering
    res = IMG_Init(IMG_INIT_PNG);
    if (!res)
    {
        SDL_Log("SLD image failed: %s", SDL_GetError());
        return false;
    }

    LoadData();

    mTickCount = SDL_GetTicks();

    //all good
    return true;
}

void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown()
{
    UnloadData();
    IMG_Quit();
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

void Game::ProcessInput()
{
    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
        switch (ev.type)
        {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        }
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    ship->ProcessKeyboard(state);
    testAnim->ProcessKeyboard(state);
}

void Game::UpdateGame()
{
    // wait if the last update occurred less than 16ms ago
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16))
    {
    }
    //delta time is the seconds elapsed since last frame
    float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    mTickCount = SDL_GetTicks();

    //start updating actors
    mIsUpdatingActors = true;
    for (auto actor : mActors)
    {
        actor->Update(deltaTime);
    }
    mIsUpdatingActors = false;
    //move pending actors inside actors
    for (auto pending : mPendingActors)
    {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    //dead actors
    std::vector<Actor *> deadActors;
    for (auto actor : mActors)
    {
        if (actor->GetState() == ActorState::Dead)
        {
            deadActors.emplace_back(actor);
        }
    }
    //delete dead actors and release memory
    for (auto dead : deadActors)
    {
        delete dead;
    }
}

void Game::GenerateOutput()
{
    //clear back buffer
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
    SDL_RenderClear(mRenderer);

    for (auto sprite : mSprites)
    {
        sprite->Draw(mRenderer);
    }

    //swap front and back buffers
    SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{

    ship = new Ship(this);
    ship->SetPosition(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    ship->SetScale(1.5f);
    
    Actor *tmp = new Actor(this);
    tmp->SetRotation(90.0f);
    tmp->SetPosition(Vector2(512.0f, 384.0f));

    BGSpriteComponent *bg = new BGSpriteComponent(tmp);
    bg->SetScreenSize(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT));
    std::vector<SDL_Texture *> bgTextures = {
        GetTexture("assets/Farback01.png"),
        GetTexture("assets/Farback02.png")};
    bg->SetBGTextures(bgTextures);
    bg->SetScrollSpeed(-100.0f);

    BGSpriteComponent *bg2 = new BGSpriteComponent(tmp, 50);
    bg2->SetScreenSize(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT));
    std::vector<SDL_Texture *> bgTextures2 = {
        GetTexture("assets/Stars.png"),
        GetTexture("assets/Stars.png")};
    bg2->SetBGTextures(bgTextures2);
    bg2->SetScrollSpeed(-200.0f);

    //test anim
    testAnim = new TestAnim(this);
    testAnim->SetPosition(Vector2(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3));
    testAnim->SetScale(1.5f);
}

void Game::UnloadData()
{
    while (!mActors.empty())
    {
        delete mActors.back();
    }

    for (auto txt : textures)
    {
        SDL_DestroyTexture(txt.second);
    }
    textures.clear();
}

void Game::AddActor(Actor *actor)
{
    if (mIsUpdatingActors)
    {
        mPendingActors.emplace_back(actor);
    }
    else
    {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor *actor)
{
    //check in active actors
    auto pos = std::find(mActors.begin(), mActors.end(), actor);
    if (pos != mActors.end())
    {
        std::iter_swap(pos, mActors.end() - 1);
        mActors.pop_back();
    }
    //check in pending actors
    pos = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (pos != mPendingActors.end())
    {
        std::iter_swap(pos, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }
}

void Game::RemoveSprite(SpriteComponent *sprite)
{
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}

void Game::AddSprite(SpriteComponent *sprite)
{
    //insert sprite in order based on DrawOrder to follow painter's algorithm
    int drawOrder = sprite->GetDrawOrder();
    auto pos = mSprites.begin();
    while (pos != mSprites.end())
    {
        if (drawOrder < (*pos)->GetDrawOrder())
        {
            break;
        }
        pos++;
    }
    mSprites.insert(pos, sprite);
}

SDL_Texture *Game::GetTexture(const std::string &filename)
{
    SDL_Texture *texture = nullptr;
    auto iter = textures.find(filename);
    SDL_Log("Current search dir: %s", getcwd(NULL, NULL));

    if (iter != textures.end())
    {
        SDL_Log("Texture %s found", filename.c_str());
        texture = iter->second;
    }
    else
    {
        //texture not found
        SDL_Surface *surface = IMG_Load(filename.c_str());
        if (!surface)
        {
            SDL_Log("Failed to load texture %s: %s", filename.c_str(), IMG_GetError());
            return nullptr;
        }

        //create texture
        texture = SDL_CreateTextureFromSurface(mRenderer, surface);
        SDL_FreeSurface(surface);

        if (!texture)
        {
            SDL_Log("Failed to create texture from surface %s", filename.c_str());
            return nullptr;
        }
        textures.emplace(filename.c_str(), texture);
    }
    return texture;
}