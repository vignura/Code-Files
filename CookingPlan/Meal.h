#ifndef _COOKING_PLAN_MEAL_H_
#define _COOKING_PLAN_MEAL_H_

#include <string>
#include <vector>
#include <stdio.h>

class Meal 
{
private:
    std::string mainDish;
    std::vector<std::string> sideDish;

public:
    Meal();
    Meal(std::string &mainDish, std::vector<std::string> &sideDish);

    void setMainDish(std::string &mainDish);
    std::string getMainDish();

    void setSideDish(std::vector<std::string> &sideDish);
    std::vector<std::string>& getdSideDish();
    
    void print();
};

#endif // _COOKING_PLAN_MEAL_H_