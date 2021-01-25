#include "Game.hpp"

int main(){

    // Intitate game.
    Game game;
    //start game loop.
    while(game.mainMenu())
    {
        game.gameLoop();
    }

}