#ifndef _COOKING_PLAN_WEEK_PLAN_
#define _COOKING_PLAN_WEEK_PLAN_

#include "Meal.h"

class WeekPlan
{
private:
    Meal breakfast[7];
    Meal lunch[7];
    Meal dinner[7];
public:
    WeekPlan();
    WeekPlan(Meal breakfast[7], Meal Lunch[7], Meal dinner[7]);
    void setBreakfast(int day, Meal breakfast);
    void setLunch(int day, Meal lunch);
    void setDinner(int day, Meal dinner);
    
    Meal& getBreakfast(int day);
    Meal& getLunch(int day);
    Meal& getDinner(int day);

    void print();
};

#endif //_COOKING_PLAN_WEEK_PLAN_