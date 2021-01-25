#ifndef MENU_HPP
#define MENU_HPP
#include <set>
#include "Drawable.hpp"
#include "Hscore.hpp"

class GameMenu: public Drawable
{
    private:
    int currentChoice = 0; // 0 = we are at the main menu
    int hovering = 1;
    int difficulty;
    std::multiset<Hscore> highscoreList;
    // Menu difficulty choices
    static const int BABY_MODE = 5;
    static const int MEEH = 6;
    static const int HARDCORE = 7;
    static const int BACK = 8;
    void renderSelector();
    void renderMain();
    void renderSettings();
    void renderHighscore();
    void renderSnakeLogo();
    void renderCurrentDifficulty();
    std::string getNameFromInput(int score);
    void addScore(std::string name, int score);
    public:
    GameMenu();
    ~GameMenu();
    void render();
    void update();
    void setChoice(int choice);
    void stepUp();
    void stepDown();
    int getChoice() const;
    int getHovering() const;
    int getDifficulty() const;
    void addHighscore(int score);
    int getTopHighscore() const;
    int getLowestHighscore() const;
    bool isHighscore(int score) const;
    void reset();
    // Menu constants
    static const int NEW_GAME = 1;
    static const int SETTINGS = 2;
    static const int HIGHSCORE = 3;
    static const int QUIT = 4;
    static const int MENU_COLOR = 2;
    static const int TITEL_COLOR = 4;
    // difficulty
    static const int EASY = 200;
    static const int MEDIUM = 100;
    static const int HARD = 50;

};

#endif // MENU_HPP