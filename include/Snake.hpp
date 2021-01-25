#ifndef SNAKE_HPP
#define SNAKE_HPP
#include "Drawable.hpp"
struct Node: public Drawable
{
    int x;
    int y;
    Node* next;
    Node* prev;
    Node()
    {
        next = nullptr;
        prev = nullptr;
    }
    ~Node(){}
    void render(){
        move(y, x);
        if(prev == nullptr){printw("O");} // Checks if Head Node
        else{printw("o");}
    }
};

class Snake: public Drawable
{
    private:
    static const int START_Y = 25;
    static const int START_X = 25;
    static const int START_LENGTH = 3;
    Node* head;
    Node* tail;
    int x_dir = 0;
    int y_dir = -1; // snake starts going up
    void deleteSnake();
    void createSnake();
    public:
    Snake();
    ~Snake();
    void render();
    void update();
    void addNode(int y, int x);
    void grow();
    void reset();
    void setYdir(int y);
    void setXdir(int x);
    int getYdir() const;
    int getXdir() const;
    Node* getHead() const;
    Node* getTail() const;
    static const int SNAKE_COLOR = 1;
    // direction constants
    static const int UP = -1;
    static const int DOWN = 1;
    static const int LEFT = -2;
    static const int RIGHT = 2;
};

#endif // SNAKE_HPP