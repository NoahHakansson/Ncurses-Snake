#include "Food.hpp"
Food::Food(int y, int x)
{
    yPos = y;
    xPos = x;
}

Food::~Food()
{

}

void Food::render()
{
    attron(COLOR_PAIR(FOOD_COLOR));
    move(yPos, xPos);
    printw("##");
    attroff(COLOR_PAIR(FOOD_COLOR));
}

int Food::getX() const
{
    return xPos;
}

int Food::getY() const
{
    return yPos;
}

bool Food::equals(int y, int x) const
{
    if(yPos == y && (xPos == x || xPos+1 == x))
    {
        return true;
    }
    return false;
}