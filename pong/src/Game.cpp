#include "Game.h"

Game::Game() {
    mWindow = nullptr;
    mIsRunning = true;
    mRenderer = nullptr;

    mBall = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    mPaddle = {THICKNESS, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2};
    mPaddle2 = {SCREEN_WIDTH - 2*THICKNESS, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2};
    mTickCount = 0;
    mPaddleDir = 0;
    mPaddle2Dir = 0;
    mBallVel = {200.0f, -235.0f};
}

/**
    Initalizate game resources.
    Return true if initialization completes, false otherwise
*/
bool Game::Initialize(){
    int res = SDL_Init(SDL_INIT_VIDEO);

    //got some error
    if(res != 0){
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
        0
    );

    //another error
    if(!mWindow){
        SDL_Log("SLD create window failed: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!mRenderer){
        SDL_Log("SLD create renderer failed: %s", SDL_GetError());
        return false;
    }
    //all good
    return true;
}

void Game::Shutdown(){
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

void Game::RunLoop(){
    while(mIsRunning){
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}


void Game::ProcessInput(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
            mIsRunning = false;
            break;
        }
    }
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    if(keyboardState[SDL_SCANCODE_ESCAPE]){
        mIsRunning = false;
    }
    if(keyboardState[SDL_SCANCODE_UP]){
        mPaddle2Dir -= 1;
        if(mPaddle2Dir < -1){
            mPaddle2Dir = -1;
        }
    }
    if(keyboardState[SDL_SCANCODE_DOWN]){
        mPaddle2Dir += 1;
        if(mPaddle2Dir > +1){
            mPaddle2Dir = 1;
        }
    }
    if(keyboardState[SDL_SCANCODE_W]){
        mPaddleDir -= 1;
        if(mPaddleDir < -1){
            mPaddleDir = -1;
        }
    }
    if(keyboardState[SDL_SCANCODE_S]){
        mPaddleDir += 1;
        if(mPaddleDir > +1){
            mPaddleDir = 1;
        }
    }
}


void Game::UpdateGame(){
    // wait if the last update occurred less than 16ms ago
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16)){}
    //delta time is the seconds elapsed since last frame
    float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;
    mTickCount = SDL_GetTicks();

    //printf("Deltatime: %f", deltaTime);
    if (mPaddleDir != 0){
        mPaddle.y += mPaddleDir * PADDLE_SPEED * deltaTime;
        if(mPaddle.y < (PADDLE_HEIGHT / 2.0f +THICKNESS)){
            mPaddle.y = PADDLE_HEIGHT / 2.0f +THICKNESS;
        }
        if(mPaddle.y > SCREEN_HEIGHT - PADDLE_HEIGHT / 2.0f - THICKNESS){
            mPaddle.y = SCREEN_HEIGHT - PADDLE_HEIGHT / 2.0f - THICKNESS;
        }
    }

    if (mPaddle2Dir != 0){
        mPaddle2.y += mPaddle2Dir * PADDLE_SPEED * deltaTime;
        if(mPaddle2.y < (PADDLE_HEIGHT / 2.0f +THICKNESS)){
            mPaddle2.y = PADDLE_HEIGHT / 2.0f +THICKNESS;
        }
        if(mPaddle2.y > SCREEN_HEIGHT - PADDLE_HEIGHT / 2.0f - THICKNESS){
            mPaddle2.y = SCREEN_HEIGHT - PADDLE_HEIGHT / 2.0f - THICKNESS;
        }
    }

    mBall.x += mBallVel.x * deltaTime;
    mBall.y += mBallVel.y * deltaTime;

    float diffPaddle1 = abs(mPaddle.y - mBall.y);
    float diffPaddle2 = abs(mPaddle2.y - mBall.y);
    if(diffPaddle1 <= PADDLE_HEIGHT &&
        mBall.x <= mPaddle.x + THICKNESS && mBall.x >= 20.0f &&
        mBallVel.x < 0.0f){
        std::cout << "Collide paddle 1" << std::endl;
        mBallVel.x *= -1.0f;
    } else if (diffPaddle2 <= PADDLE_HEIGHT &&
        mBall.x >= mPaddle2.x - THICKNESS && mBall.x <= SCREEN_WIDTH - 20.0f &&
        mBallVel.x > 0.0f){
        mBallVel.x *= -1.0f;
        std::cout << "Collide paddle 2" << std::endl;
    } else if(mBall.x <= 0.0f || mBall.x >= SCREEN_WIDTH){
        mIsRunning = false;
    } else if(mBall.y <= THICKNESS && mBallVel.y < 0.0f){
        // ball collide on top
        std::cout << "Collide top" << mBall.x << " - " << mBall.y << std::endl;
        mBallVel.y *= -1;
    } else if(mBall.y >= SCREEN_HEIGHT - THICKNESS && mBallVel.y > 0.0f){
        // ball collide bottom
        std::cout << "Collide bottom" << std::endl;
        mBallVel.y *= -1;
    }

    // clam delta time if it is too high
    if(deltaTime > 0.05f){
        deltaTime = 0.05f;
    }
}


void Game::GenerateOutput(){
    //first, clear the back buffer
    SDL_SetRenderDrawColor(
        mRenderer,
        0,0, 255, 255
    );
    SDL_RenderClear(mRenderer);

    //draw some walls
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    SDL_Rect topWall {
        0,
        0,
        1024,
        THICKNESS
    };

    SDL_Rect bottomWall {
        0,
        768 - THICKNESS,
        1024,
        THICKNESS
    };

    SDL_RenderFillRect(mRenderer, &topWall);
    SDL_RenderFillRect(mRenderer, &bottomWall);

    // draw ball
    SDL_Rect ball {
        static_cast<int>(mBall.x - THICKNESS/2),
        static_cast<int>(mBall.y - THICKNESS/2),
        THICKNESS,
        THICKNESS
    };

    SDL_Rect paddle {
        static_cast<int>(mPaddle.x),
        static_cast<int>(mPaddle.y - PADDLE_HEIGHT/2),
        THICKNESS,
        PADDLE_HEIGHT
    };
    SDL_Rect paddle2 {
        static_cast<int>(mPaddle2.x),
        static_cast<int>(mPaddle2.y - PADDLE_HEIGHT/2),
        THICKNESS,
        PADDLE_HEIGHT
    };

    SDL_RenderFillRect(mRenderer, &ball);
    SDL_RenderFillRect(mRenderer, &paddle);
    SDL_RenderFillRect(mRenderer, &paddle2);
    //swap front and back buffer
    SDL_RenderPresent(mRenderer);
}
