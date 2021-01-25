#include "Hscore.hpp"


Hscore::Hscore(std::string name, int score)
{
    this->name = name;
    this->score = score;
}

const std::string& Hscore::getName() const
{
    return name;
}
int Hscore::getScore() const
{
    return score;
}
