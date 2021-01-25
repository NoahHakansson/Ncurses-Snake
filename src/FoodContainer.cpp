#include "FoodContainer.hpp"

FoodContainer::FoodContainer()
{

}

FoodContainer::~FoodContainer()
{
    
}


void FoodContainer::addFood(int y, int x)
{
    foodVec.push_back(Food(y, x));
}

// Return true if food is eaten.
// Return false if no food is found.
bool FoodContainer::eatFood(int y, int x)
{
    for(int i = 0; i < foodVec.size(); i++){
        if(foodVec[i].equals(y, x))
        {
            foodVec.erase(foodVec.begin() + i);
            return true;
        }
    }
    return false;
}

bool FoodContainer::isFree(int y, int x) const
{
    // check food isnt spawning on another piece of food
    // if it is return false
    for(int i = 0; i < foodVec.size(); i++){
        if(foodVec[i].equals(y, x))
        {
            return false;
        }
    }
    return true;
}

void FoodContainer::render()
{
    // render all food
    for(Food food : foodVec){
        food.render();
    }
}

void FoodContainer::clearContainer()
{
    foodVec.clear();
}