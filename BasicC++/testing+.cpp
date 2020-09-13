#include<iostream>
#include "Rational1.h"
using namespace std;
int main()
{
Rational a[17],b[17];
a[0] = 0; b[0] = 0;
//
a[1] = 0.5 ; b[1] = 0.3;
a[2] = 0.5 ; b[2] = -0.3;
a[3] = -0.5 ; b[3] = 0.3;
a[4] = -0.5 ; b[4] = -0.3;
//
a[5] = 0.1; b[5] = 0.4;
a[6] = 0.1; b[6] = -0.4;
a[7] = -0.1; b[7] = 0.4;
a[8] = -0.1; b[8] = -0.4;
//
a[9] = 5; b[9] = 3;
a[10] = 5; b[10] = -3;
a[11] = -5; b[11] = 3;
a[12] = -5; b[12] = -3;
//
a[13] = 1; b[13] = 4;
a[14] = 1; b[14] = -4;
a[15] = -1; b[15] = 4;
a[16] = -1; b[16] = -4;
Rational sum;
for(int i = 0; i < 17;i++)
{
sum = a[i] % b[i];
cout<<"("<<a[i].abs()<<" % "<<b[i].abs()<<") = "<<sum.abs()<<"\t";sum.print();cout<<endl;
}
return 0;
}
