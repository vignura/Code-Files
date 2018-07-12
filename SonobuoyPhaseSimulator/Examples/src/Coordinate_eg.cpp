#include <iostream>
#include <cstdio>
#include "coordinate.h"
using namespace std;

int main(){
    
    Coordinate p1;          // no parameters given hence the members x, y, z are initialized to 0
    Coordinate p2(0,1,2);   // here x = 0, y = 1, z = 2
    Coordinate p3 = p2;     // the class provide operator= fiunction 
    double x, y, z;
    
    printf("Coordinate class demo\n");
    printf("List of Coordinate member functions\n");
    printf("\t1.getx() \
            \n\t2.gety() \
            \n\t3.getz() \
            \n\t4.setx() \
            \n\t5.sety() \
            \n\t6.setz() \
            \n\t7.setCoord() \
            \n\t8.Coordinate() parameterless constructor \
            \n\t9.Coordinate(x, y, z) parameterized constructor \
            \n\t10.operator=(): usage, p1 = p2\n");
    
    printf("\nprinting initial values of p1 p2 and p3 using the 'get' member function\n");
    // the members of the class are of double type
    printf("p1 (x, y, z) = (%f, %f, %f)\n", p1.getx(), p1.gety(), p1.getz()); 
    // getx(), gety(), getz() can be used for getting the x, y, z values
    // similarly setx(), sety(), setz() can be used for setting the x, y, z values
    printf("p2 (x, y, z) = (%f, %f, %f)\n", p2.getx(), p2.gety(), p2.getz());
    printf("p3 (x, y, z) = (%f, %f, %f)\n", p3.getx(), p3.gety(), p3.getz());
    
    printf("Changing values of p1 p2 and p3 using the 'set' and 'setCoord' member functions\n");
   
    printf("Enter coordinate for p1 (x y z): ");
    cin >> x >> y >> z;
    //changing the values of x, y , z after initialization using set function
    p1.setx(x);
    p1.sety(y);
    p1.setz(z);
    
    printf("Enter coordinate for p2 (x y z): ");
    cin >> x >> y >> z;
    //changing the values of x, y , z after initialization using set function
    p2.setx(x);
    p2.sety(y);
    p2.setz(z);
    
    printf("Enter coordinate for p2 (x y z): ");
    cin >> x >> y >> z;
    // changing the values of the x, y, z using setCoord function
    p3.setCoord(x, y,z);
    
    printf("printing the values of p1 p2 p3 after changing their values using 'set' and 'setCoord'\n");
    printf("p1 (x, y, z) = (%f, %f, %f)\n", p1.getx(), p1.gety(), p1.getz());
    printf("p2 (x, y, z) = (%f, %f, %f)\n", p2.getx(), p2.gety(), p2.getz());
    printf("p3 (x, y, z) = (%f, %f, %f)\n", p3.getx(), p3.gety(), p3.getz());
    
    return 0;    
}
