#ifndef GAME_HPP
#define GAME_HPP
#include <string>
#include <vector>
#include <random>
#include "Snake.hpp"
#include "Food.hpp"
#include "GameMenu.hpp"
#include "FoodContainer.hpp"
#include "Keys.hpp"

class Game
{
    private:
    GameMenu menu;
    Snake snake;
    FoodContainer foodList;
    std::vector<Drawable*> gameObjects;
    int currentScore = 0;
    int userSnakeInput = 0;
    int userMenuInput = 0;
    int difficulty;
    bool collision = false;
    bool debugMode = false;
    std::random_device rd;
    void addFood();
    void renderGameObjects();
    void pushHighscore();
    // game functions
    void sleep(int x);
    void snakeInput();
    void menuInput();
    bool wallCollisionCheck();
    bool selfCollisionCheck();
    void foodEatCheck();
    bool isFreePos(int y, int x) const;
    void collisionCheck();
    void printScore();
    void showDebugInfo();
    public:
    Game();
    ~Game();
    void gameLoop();
    bool mainMenu();
};
#endif // GAME_HPP