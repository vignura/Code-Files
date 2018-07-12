#ifndef _GLIBCXX_CALC
#define _GLIBCXX_CALC 1
class calc
{
public:
int add(int,int);
int sub(int,int);
int mul(int,int);
float div(int,int);
};
//Addition 
int calc::add(int a, int b)
{
return (a + b);
}
//Subtraction
int calc::sub(int a, int b)
{
return (a - b);
}
//Multiplication
int calc::mul(int a, int b)
{
return (a * b);
}
//Division
float calc::div(int a, int b)
{
return (a / b);
}
#endif
