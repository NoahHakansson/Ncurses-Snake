#include <fstream>
#include <sstream>
#include "GameMenu.hpp"

GameMenu::GameMenu()
{
    difficulty = BABY_MODE;

    std::ifstream inFile("scores.txt");
    std::string line;
    std::string name;
    int score;

    // load highscores from file
    if(inFile)
    {
        while (getline(inFile, line))
        {
            std::string comma_string;
            std::istringstream ss(line);
            ss >> score;
            getline(ss, comma_string, ':');
            getline(ss, name, '\n');

            addScore(name, score);
        }
        inFile.close();
    }
}


GameMenu::~GameMenu()
{
    std::ofstream outFile ("scores.txt");
    if (outFile)
    {
        for(auto it = highscoreList.begin(); it != highscoreList.end(); it++){
            outFile << it->getScore();
            outFile << ':';
            outFile << it->getName();
            outFile << '\n';
        }
        outFile.close();
    }
}

void GameMenu::renderSelector()
{
    if(hovering == NEW_GAME || hovering == BABY_MODE){
        mvprintw(Y_MIDDLE+NEW_GAME, X_MIDDLE-2, ">");
    }
    else if(hovering == SETTINGS || hovering == MEEH){
        mvprintw(Y_MIDDLE+SETTINGS, X_MIDDLE-2, ">");
    }
    else if(hovering == HIGHSCORE || hovering == HARDCORE){
        mvprintw(Y_MIDDLE+HIGHSCORE, X_MIDDLE-2, ">");
    }
    else if(hovering == QUIT || hovering == BACK){
        mvprintw(Y_MIDDLE+QUIT, X_MIDDLE-2, ">");
    }
}

void GameMenu::renderMain()
{
    renderSnakeLogo();
    attron(COLOR_PAIR(MENU_COLOR));
    mvprintw(Y_MIDDLE+NEW_GAME, X_MIDDLE, "New Game");
    mvprintw(Y_MIDDLE+SETTINGS, X_MIDDLE, "Settings");
    mvprintw(Y_MIDDLE+HIGHSCORE, X_MIDDLE, "Highscore");
    mvprintw(Y_MIDDLE+QUIT, X_MIDDLE, "Quit");
    renderSelector();
    attroff(COLOR_PAIR(MENU_COLOR));
    renderCurrentDifficulty();
    mvprintw(Y_MIDDLE+NEW_GAME, 9, "Use W and S to change selection");
    mvprintw(Y_MIDDLE+NEW_GAME+2, 9, "Press SPACE to select");
}

void GameMenu::renderSettings()
{
    // Make sure we are not hovering something from a different menu.
    if(hovering < BABY_MODE || hovering > BACK){
        hovering = BABY_MODE;
    }
    renderSnakeLogo();
    attron(COLOR_PAIR(MENU_COLOR));
    mvprintw(Y_MIDDLE+NEW_GAME-2, X_MIDDLE, "Difficulty:");
    mvprintw(Y_MIDDLE+NEW_GAME, X_MIDDLE, "Baby mode");
    mvprintw(Y_MIDDLE+SETTINGS, X_MIDDLE, "Meeh");
    mvprintw(Y_MIDDLE+HIGHSCORE, X_MIDDLE, "HARDCORE");
    mvprintw(Y_MIDDLE+QUIT, X_MIDDLE, "Go Back");
    renderSelector();
    attroff(COLOR_PAIR(MENU_COLOR));
    renderCurrentDifficulty();
}

void GameMenu::renderHighscore()
{
    renderSnakeLogo();
    attron(COLOR_PAIR(MENU_COLOR));
    mvprintw(Y_MIDDLE+NEW_GAME-2, X_MIDDLE, "Highscores:");
    attroff(COLOR_PAIR(MENU_COLOR));
    attron(COLOR_PAIR(TITEL_COLOR));
    int pos = 0;
    for (auto it = highscoreList.rbegin(); it != highscoreList.rend(); it++){
        move(Y_MIDDLE+NEW_GAME + pos, X_MIDDLE);
        printw("%s: %d",it->getName().c_str(), it->getScore());
        pos++;
    }
    attroff(COLOR_PAIR(TITEL_COLOR));
    // back button
    attron(COLOR_PAIR(MENU_COLOR));
    mvprintw(Y_MIDDLE+HIGHSCORE+pos, X_MIDDLE, "Go Back");
    mvprintw(Y_MIDDLE+HIGHSCORE+pos, X_MIDDLE-2, ">");
    attroff(COLOR_PAIR(MENU_COLOR));
}

void GameMenu::renderCurrentDifficulty()
{
    attron(COLOR_PAIR(TITEL_COLOR));
    move(Y_MIDDLE+QUIT+3, X_MIDDLE-BACK);
    if(difficulty == BABY_MODE){printw("Current Difficulty: Baby mode");}
    else if(difficulty == MEEH){printw("Current Difficulty: Meeh");}
    else if(difficulty == HARDCORE){printw("Current Difficulty: HARDCORE");}
    attroff(COLOR_PAIR(TITEL_COLOR));
}

void GameMenu::renderSnakeLogo()
{
    attron(COLOR_PAIR(TITEL_COLOR));
    mvprintw(Y_MIDDLE+NEW_GAME-11, X_MIDDLE-18," _______  __    _  _______  ___   _  _______ ");
    mvprintw(Y_MIDDLE+NEW_GAME-10, X_MIDDLE-18,"|       ||  |  | ||   _   ||   | | ||       |");
    mvprintw(Y_MIDDLE+NEW_GAME-9, X_MIDDLE-18, "|  _____||   |_| ||  |_|  ||   |_| ||    ___|");
    mvprintw(Y_MIDDLE+NEW_GAME-8, X_MIDDLE-18, "| |_____ |       ||       ||      _||   |___ ");
    mvprintw(Y_MIDDLE+NEW_GAME-7, X_MIDDLE-18, "|_____  ||  _    ||       ||     |_ |    ___|");
    mvprintw(Y_MIDDLE+NEW_GAME-6, X_MIDDLE-18, " _____| || | |   ||   _   ||    _  ||   |___ ");
    mvprintw(Y_MIDDLE+NEW_GAME-5, X_MIDDLE-18, "|_______||_|  |__||__| |__||___| |_||_______|");
    attroff(COLOR_PAIR(TITEL_COLOR));
}

void GameMenu::render()
{
    if(currentChoice == 0){
        renderMain();
    }if(currentChoice == SETTINGS){
        renderSettings();
    }if(currentChoice == HIGHSCORE){
        renderHighscore();
        hovering = BACK;
    }
}


void GameMenu::reset()
{
    currentChoice = 0;
    hovering = 1;
}

void GameMenu::stepUp()
{
    hovering--;
    if(currentChoice == 0 && hovering < NEW_GAME){
        hovering = QUIT;
    }
    if(currentChoice == SETTINGS && hovering < BABY_MODE){
        hovering = BACK;
    }
    if(currentChoice == HIGHSCORE){
        hovering = BACK;
    }
}

void GameMenu::stepDown()
{
    hovering++;
    if(currentChoice == 0 && hovering > QUIT){
        hovering = NEW_GAME;
    }
    if(currentChoice == SETTINGS && hovering > BACK){
        hovering = BABY_MODE;
    }
    if(currentChoice == HIGHSCORE){
        hovering = BACK;
    }
}

int GameMenu::getDifficulty() const
{
    if(difficulty == BABY_MODE){return EASY;}
    else if(difficulty == MEEH){return MEDIUM;}
    else if(difficulty == HARDCORE){return HARD;}
    return EASY;
}

void GameMenu::setChoice(int choice)
{
    currentChoice = choice;
    if(currentChoice == BACK){
        currentChoice = 0;
        hovering = NEW_GAME;
    }
    else if(currentChoice == BABY_MODE){
        difficulty = BABY_MODE;
        currentChoice = SETTINGS;
    }
    else if(currentChoice == MEEH){
        difficulty = MEEH;
        currentChoice = SETTINGS;
    }
    else if(currentChoice == HARDCORE){
        difficulty = HARDCORE;
        currentChoice = SETTINGS;
    }
}

std::string GameMenu::getNameFromInput(int score)
{
    nodelay(stdscr, FALSE);
    echo();
    char nameArr[9] = "";
    attron(COLOR_PAIR(MENU_COLOR));
    mvprintw(Y_MIDDLE-2, X_MIDDLE-4, "New highscore!");
    attroff(COLOR_PAIR(MENU_COLOR));
    attron(COLOR_PAIR(TITEL_COLOR));
    mvprintw(Y_MIDDLE-1, X_MIDDLE-1, "Score: %d",score);
    mvprintw(Y_MIDDLE, X_MIDDLE-3, "Enter name:");
    mvprintw(Y_MIDDLE+2, X_MIDDLE-10, "Press enter to continue...");
    mvgetnstr(Y_MIDDLE, X_MIDDLE+9, nameArr, 8);
    attroff(COLOR_PAIR(TITEL_COLOR));
    nodelay(stdscr, TRUE);
    noecho();
    std::string name = nameArr;
    if(name == ""){name = "NoName";}
    return std::string(name);
}

void GameMenu::addHighscore(int score)
{
    std::string name = getNameFromInput(score);
    addScore(name, score);
}

void GameMenu::addScore(std::string name, int score)
{
    highscoreList.insert(Hscore(name, score));
    if(highscoreList.size() > 10)
    {
        auto stop = highscoreList.end();
        for(int i = 0; i < 10; i++){stop--;}
        for(auto it = highscoreList.begin(); it != stop; )
            it = highscoreList.erase(it);
    }
}

bool GameMenu::isHighscore(int score) const
{
    if(highscoreList.size() < 10 && score > 0){
        return true;
    }else if(score > getLowestHighscore()){
        return true;
    }
    return false;
}

int GameMenu::getTopHighscore() const
{
    if(highscoreList.size() > 0){
        auto score = highscoreList.end();
        score--;
        return score->getScore();
    }
    return 0;
}

int GameMenu::getLowestHighscore() const
{
    if(highscoreList.size() > 0){
        auto score = highscoreList.rend();
        score--;
        return score->getScore();
    }
    return 0;
}

int GameMenu::getChoice() const
{
    return currentChoice;
}

int GameMenu::getHovering() const
{
    return hovering;
}