#ifndef HSCORE_HPP
#define HSCORE_HPP
#include <string>

class Hscore
{
private:
    std::string name;
    int score;
public:
    Hscore() = delete;
    Hscore(std::string name, int score);
    int getScore() const;
    const std::string& getName() const;
    friend bool operator<(const Hscore& left, const Hscore& right)
    {
        return (left.score < right.score);
    }
};

#endif // HSCORE_HPP
