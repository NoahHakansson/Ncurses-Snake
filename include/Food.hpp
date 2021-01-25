#ifndef FOOD_HPP
#define FOOD_HPP
#include "Drawable.hpp"
class Food: public Drawable
{
private:
    int yPos;
    int xPos;
public:
    Food(int y, int x);
    ~Food();
    void render();
    static const int FOOD_COLOR = 3;
    int getX() const;
    int getY() const;
    // Compare food position to parameters x and y
    bool equals(int y, int x) const;
};

#endif // FOOD_HPP