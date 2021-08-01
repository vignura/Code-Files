cmake_minimum_required(VERSION 3.12)
project(CookingPlan)
#headers
include_directories(.)
#Sources
set (SOURCES "Meal.cpp"
             "WeekPlan.cpp"
             "main.cpp")
 
add_executable(CookingPlan ${SOURCES})