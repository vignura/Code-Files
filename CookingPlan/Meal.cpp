#include "Meal.h"
Meal::Meal()
{
    // do nothing
}

Meal::Meal(std::string &mainDish, std::vector<std::string> &sideDish)
{
    this->mainDish = mainDish;
    for (std::string dish : sideDish)
    {
        this->sideDish.push_back(dish);
    }
}

void Meal::setMainDish(std::string &mainDish)
{
    this->mainDish = mainDish;
}

std::string Meal::getMainDish()
{
    return this->mainDish;
}

void Meal::setSideDish(std::vector<std::string> &sideDish)
{
    for (std::string dish : sideDish)
    {
        this->sideDish.push_back(dish);
    }
}

std::vector<std::string>& Meal::getdSideDish()
{
    return this->sideDish;
}

void Meal::print()
{
    printf("[%s with ", this->mainDish.c_str());
    for (std::string dish : sideDish)
    {
        printf("%s ", dish.c_str());
    }
    printf("\b]\n");
}