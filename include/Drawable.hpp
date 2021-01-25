#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP
#include <ncurses.h>
#include <chrono>
#include <thread>

#define Y_MIDDLE ((LINES/2)-(LINES/10))
#define X_MIDDLE ((COLS/2)-(COLS/17))

class Drawable
{
    public:
    virtual inline ~Drawable(){}
    virtual void render() = 0;
};

#endif // DRAWABLE_HPP