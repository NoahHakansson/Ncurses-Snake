#ifndef FOODCONTAINER_HPP
#define FOODCONTAINER_HPP
#include <vector>
#include "Food.hpp"
class FoodContainer: public Drawable
{
private:
    std::vector<Food> foodVec;
public:
    FoodContainer();
    ~FoodContainer();
    void render();
    void addFood(int y, int x);
    bool eatFood(int y, int x);
    void clearContainer();
    bool isFree(int y, int x) const;
};

#endif // FOODCONTAINER_HPP