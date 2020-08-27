#include "./Game.h"
#include <iostream>

int main(){
    Game game;
    if(game.Initialize()){
        std::cout << "init ok" << std::endl;
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
