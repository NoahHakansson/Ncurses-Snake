#include "Snake.hpp"
Snake::Snake()
{
    head = nullptr;
    tail = nullptr;

    createSnake();
}

Snake::~Snake()
{
    deleteSnake();
}

void Snake::deleteSnake()
{
    Node* current = head;
    while( current != nullptr ) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}

void Snake::createSnake()
{
    for(int i = 0; i < START_LENGTH; i++){
        addNode(START_Y, START_X - i*2);
    }
}

void Snake::render()
{
    // Render snake to window
    Node* walker = head;
    while(walker != nullptr)
    {
        attron(COLOR_PAIR(SNAKE_COLOR));
        walker->render();
        attroff(COLOR_PAIR(SNAKE_COLOR));
        walker = walker->next;
    }
}

void Snake::update()
{
    Node* walker = tail;
    while(walker != head)
    {
        // Update current node
        walker->x = walker->prev->x;
        walker->y = walker->prev->y;
        // Set current node to previous node in list.
        walker = walker->prev;
    }
    // update snake heads position
    head->x += x_dir;
    head->y += y_dir;
}

void Snake::addNode(int y, int x)
{
    Node *tmp = new Node;
    tmp->y = y;
    tmp->x = x;
    tmp->next = nullptr;
    tmp->prev = tail;

    if(head == nullptr)
    {
        head = tmp;
        tail = tmp;
    }
    else
    {
        tail->next = tmp;
        tail = tail->next;
    }
}

void Snake::grow()
{
    addNode(tail->y, tail->x);
}

void Snake::reset()
{
    x_dir = 0;
    y_dir = -1; // snake starts going up
    deleteSnake();
    createSnake();
}

Node* Snake::getHead() const
{
    return head;
}

Node* Snake::getTail() const
{
    return tail;
}

void Snake::setYdir(int y)
{
    y_dir = y;
}


void Snake::setXdir(int x)
{
    x_dir = x;
}

int Snake::getYdir() const
{
    return y_dir;
}

int Snake::getXdir() const
{
    return x_dir;
}
