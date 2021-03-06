#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include "Vector2.h"
#include <cmath>
#include "Constants.h"

class Game {
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	SDL_Window* mWindow;
	bool mIsRunning;
	SDL_Renderer* mRenderer;

	Vector2 mPaddle;
	Vector2 mPaddle2;
	Vector2 mBall;
	Uint32 mTickCount;
	int mPaddleDir;
	int mPaddle2Dir;
	Vector2 mBallVel;
};



#endif /* GAME_H_ */
