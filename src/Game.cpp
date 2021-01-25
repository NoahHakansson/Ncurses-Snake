#include "Game.hpp"

Game::Game()
{
    // initate screen
    initscr();
    start_color();
    init_pair(Snake::SNAKE_COLOR, COLOR_GREEN, COLOR_BLACK);
    init_pair(GameMenu::MENU_COLOR, COLOR_BLACK, COLOR_GREEN);
    init_pair(Food::FOOD_COLOR, COLOR_RED, COLOR_RED);
    init_pair(GameMenu::TITEL_COLOR, COLOR_GREEN, COLOR_BLACK);
    nodelay(stdscr, TRUE);
    noecho();
    curs_set(0);
    difficulty = menu.getDifficulty();

    // Add game objects to render in game loop.
    gameObjects.push_back(&snake);
    gameObjects.push_back(&foodList);
}

Game::~Game()
{
    // End screen and game.
    endwin();
}

void Game::snakeInput()
{
    // Y
    if(userSnakeInput == Keys::KEY_W && snake.getYdir() != Snake::DOWN){ // UP
        snake.setYdir(Snake::UP);
        snake.setXdir(0);
    }else if(userSnakeInput == Keys::KEY_S && snake.getYdir() != Snake::UP){ // DOWN
        snake.setYdir(Snake::DOWN);
        snake.setXdir(0);
    // X
    }else if(userSnakeInput == Keys::KEY_D && snake.getXdir() != Snake::LEFT){ // RIGHT
        snake.setYdir(0);
        snake.setXdir(Snake::RIGHT);
    }else if(userSnakeInput == Keys::KEY_A && snake.getXdir() != Snake::RIGHT){ // LEFT
        snake.setYdir(0);
        snake.setXdir(Snake::LEFT);
    }
    // Flush input buffer.
    flushinp();
}

void Game::menuInput()
{
    // Y
    if(userMenuInput == Keys::KEY_W){ // UP
        menu.stepUp();
    }else if(userMenuInput == Keys::KEY_S){ // DOWN
        menu.stepDown();
    }else if(userMenuInput == Keys::KEY_SPACE){
        menu.setChoice(menu.getHovering());
    }
    // Flush input buffer.
    flushinp();
}

bool Game::mainMenu()
{
    bool startGame = true;
    while(menu.getChoice() != menu.NEW_GAME && menu.getChoice() != menu.QUIT)
    {

        // Debug prints
        move(0,0);
        printw("Hovering: %d", menu.getHovering());
        move(2,0);
        printw("Current choice: %d", menu.getChoice());
        ////

        // Menu input
        userMenuInput = getch();

        menuInput();

        menu.render();

        // refreshes screen
        refresh();
        erase();
        sleep(50);
    }

    // Change difficulty
    difficulty = menu.getDifficulty();

    if(menu.getChoice() == menu.QUIT){
        startGame = false;
    }
    menu.reset();
    return startGame;
}

void Game::gameLoop()
{
    collision = false;
    addFood();
    int timeUnit = 0;
    sleep(1000); // game start delay.

    while(userSnakeInput != Keys::KEY_Q && !collision)
    {
        // Snake input
        userSnakeInput = getch();

        // add food after a certain time, even if no food is eaten.
        timeUnit++;
        if(timeUnit >= 100){
            addFood();
            timeUnit = 0;
        }
        showDebugInfo();
        
        printScore();
        
        snakeInput(); // Change snake direction depending on input
        
        snake.update();

        renderGameObjects(); // Render everything in the gameObjects vector.

        foodEatCheck(); // Checks if a food was eaten and if so remove it and grow snake.
        
        collisionCheck(); // Checks wall and self collision

        // refreshes screen
        refresh();
        erase();
        sleep(difficulty);
        
    }
    // Clear and reset stuffs at GAME OVER.
    pushHighscore();
    currentScore = 0;
    snake.reset();
    userSnakeInput = -1; // reset user input on exit to avoid early end of program.
    foodList.clearContainer();
}

void Game::pushHighscore()
{
    if(menu.isHighscore(currentScore)){
        sleep(500);
        menu.addHighscore(currentScore);
    }
}

void Game::addFood()
{
    // initialize Randomizer
    std::mt19937 mt(rd());
    double yMax = static_cast<double>(LINES);
    double xMax = static_cast<double>(COLS);
    std::uniform_real_distribution<double> yCord(2.0, yMax-2);
    std::uniform_real_distribution<double> xCord(2.0, xMax-2);

    // Randomize positions
    int yPos = static_cast<int>(yCord(mt));
    int xPos = static_cast<int>(xCord(mt));

    // Retry until a free spot is found
    while (!isFreePos(yPos, xPos))
    {
        yPos = static_cast<int>(yCord(mt));
        xPos = static_cast<int>(xCord(mt));
    }
    // when a free position is found add food there.
    foodList.addFood(yPos, xPos);
}

bool Game::isFreePos(int y, int x) const
{
    // check food isnt spawning on snake
    // if it is return false
    Node* walker = snake.getHead();
    while (walker != nullptr)
    {
        if(walker->y == y && (walker->x == x || walker->x == x+1))
        {
            return false;
        }
        walker = walker->next;
    }
    // check food isnt spawning on another piece of food
    return foodList.isFree(y, x);
}

void Game::foodEatCheck()
{
    int headY = snake.getHead()->y;
    int headX = snake.getHead()->x;

    if(foodList.eatFood(headY, headX)){
        currentScore++;
        snake.grow();
        addFood();
    }
}

void Game::collisionCheck()
{
    // Check wall collision
    if(!collision){
        collision = wallCollisionCheck();
    }
    // Check self collision
    if(!collision){
        collision = selfCollisionCheck();
    }
}

void Game::printScore()
{
    mvprintw(0, X_MIDDLE-10, "Score: %d", currentScore);
    if(currentScore < menu.getTopHighscore()){
        mvprintw(0, X_MIDDLE+5, "Highscore: %d", menu.getTopHighscore());
    }else{
        mvprintw(0, X_MIDDLE+5, "Highscore: %d", currentScore);
    }
}

void Game::showDebugInfo()
{
    // start debug mode if user presses B.
    if(userSnakeInput == Keys::KEY_B){
        if(!debugMode){
            debugMode = true;
        }else{
            debugMode = false;
        }
    }
    if(debugMode){
        // Debug prints
        move(0,0);
        printw("User input: %d", userSnakeInput);
        move(2,0);
        printw("Lines: %d", LINES);
        move(3,0);
        printw("Cols: %d", COLS);
        move(5,0);
        printw("Snake Y: %d", snake.getHead()->y);
        move(6,0);
        printw("Snake X: %d", snake.getHead()->x);
        move(7,0);
        printw("Difficulty: %d", difficulty);
        ////
    }
}
bool Game::wallCollisionCheck()
{
    if(snake.getHead()->y < 0 || snake.getHead()->y > LINES-1)
    {
        return true;
    }
    if(snake.getHead()->x < 0 || snake.getHead()->x > COLS-1)
    {
        return true;
    }
    return false;
}


bool Game::selfCollisionCheck()
{
    Node* walker = snake.getHead();
    int headY = walker->y;
    int headX = walker->x;
    walker = walker->next;
    while(walker != nullptr)
    {
        if(headY == walker->y && headX == walker->x){
            return true; // Found collision
        }
        walker = walker->next;
    }
    return false; // if no collision
}

void Game::renderGameObjects()
{
    // Render game objects
    for(Drawable* object : gameObjects){
        object->render();
    }
}


// takes miliseconds
void Game::sleep(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
