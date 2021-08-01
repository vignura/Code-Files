#include <stdio.h>
#include "WeekPlan.h"

void testWeekPlan();

int main(int argc, char const *argv[])
{
    /* code */
    printf("Weekly Cooking Plan\n");
    testWeekPlan();
    return 0;
}

void testWeekPlan()
{
    WeekPlan weekPlan;
    std::vector<std::string> sideDish;
    std::string mainDish;
     
    for(int i = 0; i < 7; i++)
    {   
        mainDish = "Dosa";
        sideDish.push_back("coconut chutney");
        Meal breakfast (mainDish, sideDish);
        weekPlan.setBreakfast(i, breakfast);
        sideDish.pop_back();

        mainDish = "Sambar and Rasam";
        sideDish.push_back("beetroot");
        Meal lunch (mainDish, sideDish);
        weekPlan.setLunch(i, lunch);
        sideDish.pop_back();

        mainDish = "Chapathi";
        sideDish.push_back("Potato Masal");
        Meal dinner (mainDish, sideDish);
        weekPlan.setDinner(i, dinner);
        sideDish.pop_back();
    }

   weekPlan.print();
}