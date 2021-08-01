#include "WeekPlan.h"

WeekPlan::WeekPlan()
{
    // do nothing
}
WeekPlan::WeekPlan(Meal breakfast[7], Meal Lunch[7], Meal dinner[7])
{
    for (int i = 0; i < 7; i++)
    {
        this->breakfast[i] = breakfast[i];
        this->lunch[i] = lunch[i];
        this->dinner[i] = dinner[i];
    }
}

void WeekPlan::setBreakfast(int day, Meal breakfast)
{
    this->breakfast[day] = breakfast;
}

void WeekPlan::setLunch(int day, Meal lunch)
{
    this->lunch[day] = lunch;
}

void WeekPlan::setDinner(int day, Meal dinner)
{
    this->dinner[day] = dinner;
}

Meal& WeekPlan::getBreakfast(int day)
{
    return this->breakfast[day];
}

Meal& WeekPlan::getLunch(int day)
{
    return this->lunch[day];
}

Meal& WeekPlan::getDinner(int day)
{
    return this->dinner[day];
}

void WeekPlan::print()
{
    char weekDay[][12] = {"monday", "tuesday", "wenesday", "thursday", "friday", "saturday", "sunday"};
    
    for(int i = 0; i < 7; i++)
    {
        printf("%s\n", weekDay[i]);
        printf("Breakfast: ");
        this->breakfast[i].print();
        printf("Lunch: ");
        this->lunch[i].print();
        printf("Dinner: ");
        this->dinner[i].print();
        printf("\n");
    }
}