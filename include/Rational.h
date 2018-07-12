#ifndef RATIONAL_H
#define RATIONAL_H
#include "Factorise.h"
class Rational{
int n;
int d;
int getLCM(int,int);
int getHCF(int,int);
void print_array(int *,int);
Rational& reduce();
public:
Rational(){n = 0; d = 1;}
Rational(int nu,int de){
n = nu; 
d = de;
if(d < 0){
	n *= -1;
	d *= -1;
}
}
double abs();
bool is_int()
{
if((int)abs() == abs())
	return true;
else
	return false;
}
//assignment operator
void operator=(const Rational &Rval);
//arithmatic operators
Rational operator+(const Rational &R_val);
Rational operator-(const Rational &R_val);
Rational operator*(const Rational &R_val);
Rational operator/(const Rational &R_val);
Rational operator%(const Rational &R_val);
//overloaded arithmatic operators
Rational operator+(const int &R_val);
Rational operator-(const int &R_val);
Rational operator*(const int &R_val);
Rational operator/(const int &R_val);
Rational operator%(const int &R_val);
//relational operators
bool operator<(Rational R_val);
bool operator>(Rational R_val);
bool operator<=(Rational R_val);
bool operator>=(Rational R_val);
bool operator==(Rational R_val);
bool operator!=(Rational R_val);
//overloaded relational operators
bool operator<(const int &R_val);
bool operator>(const int &R_val);
bool operator<=(const int &R_val);
bool operator>=(const int &R_val);
bool operator==(const int &R_val);
bool operator!=(const int &R_val);
//compound assignment operators
void operator+=(const Rational &R_val);
void operator-=(const Rational &R_val);
void operator*=(const Rational &R_val);
void operator/=(const Rational &R_val);
void operator%=(const Rational &R_val);
//overloaded compound assignment operators
void operator+=(const int &R_val);
void operator-=(const int &R_val);
void operator*=(const int &R_val);
void operator/=(const int &R_val);
void operator%=(const int &R_val);
//increment decrement operators
void operator++();
void operator--();
void operator++(int R_val);
void operator--(int R_val);
//io functions
void getUserInput();
void getint();
int toint();
void print();
};
//Private Functions
//int array printing function
void Rational::print_array(int *array,int len)
{
for(int i = 0; i < len; i++)
{
std::cout<<array[i]<<std::endl;
}
}
// Fraction Reducing fuction
Rational& Rational::reduce()
{
int numerator = 1;
int denominator = 1;
int *nu_factors,*de_factors;
Fact nu,de;
//factorising
nu.factorise(this -> n);
nu_factors = nu.factors();
de.factorise(this -> d);
de_factors = de.factors();
/**
std::cout<<"Printing the arrays before cancelling"<<std::endl;
std::cout<<"Numerators"<<std::endl;
print_array(nu_factors,nu.len());
std::cout<<"denominators"<<std::endl;
print_array(de_factors,de.len());
/**/
//cancelling the common factors 
for(int i = 0; i < nu.len()-1; i++)
{
	for(int j = 0; j < de.len()-1; j++)
	{
		if(nu_factors[i] == de_factors[j]){
			nu_factors[i] = 1;
			de_factors[j] = 1;
			break;		
		}	
	}
}
/**
std::cout<<"Printing the arrays after cancelling"<<std::endl;
std::cout<<"Numerators "<<nu.len()<<std::endl;
print_array(nu_factors,nu.len());
std::cout<<"denominators "<<de.len()<<std::endl;
print_array(de_factors,de.len());
/**/
//calculating the reduced values of numerator and denominator
for(int i = 0; i < nu.len()-1; i++)
{
	numerator *= nu_factors[i];
}
for(int i = 0; i < de.len()-1; i++)
{
	denominator *= de_factors[i];
}
/**
std::cout<<"numerator = "<<numerator<<std::endl;
std::cout<<"denominator = "<<denominator<<std::endl;/**/
this -> n = numerator;
this -> d = denominator;
return *this;
}
//LCM Finding Function
int Rational::getLCM(int a, int b)
{
int LCM,HCF;
HCF = getHCF(a,b);
LCM = (a / HCF) * b;
return LCM;
}
//HCF Finding Function
int Rational::getHCF(int a, int b)
{
int num,div,rem;
if(a < b){
	div = a;
	num = b;
}
else{ 
	div = b;
	num = a;
}
do{
rem = num % div;
if(rem != 0){
	num = div;
	div = rem;
}
}while(rem != 0);
return div;
}
///////////////////
///////////////////
//Public member Functions
double Rational::abs()
{
	return (n / (double)d);
}
void Rational::getint()
{
std::cout<<"Enter a number: ";
std::cin>>n;
}
int Rational::toint()
{
return (abs());
} 
void Rational::getUserInput()
{
std::cout<<"Enter the Numerator value: ";
std::cin>>n;
std::cout<<"Enter the denominator value: ";
std::cin>>d;
if(d < 0){
	n *= -1;
	d *= -1;
}
}
void Rational::print()
{
std::cout<<"("<<n<<" / "<<d<<")";
}
//assignment operator
void Rational::operator=(const Rational &R_val)
{
this -> n = R_val.n;
this -> d = R_val.d;
}
//Arithmatic operators
Rational Rational::operator+(const Rational &R_val)
{
int LCM;
Rational sum;
LCM = getLCM(d,R_val.d);
sum.n = ((n * LCM) / d) + ((R_val.n * LCM) / (R_val.d));
sum.d = LCM;
if(sum .n < 0){
	sum.n *= -1;
	sum.reduce();
	sum.n *= -1;
}
else
	sum.reduce();
return sum;
}

Rational Rational::operator-(const Rational &R_val)
{
int LCM;
Rational diff;
LCM = getLCM(d,R_val.d);
diff.n = ((n * LCM) / d) - ((R_val.n * LCM) / (R_val.d));
diff.d = LCM;
if(diff .n < 0){
	diff.n *= -1;
	diff.reduce();
	diff.n *= -1;
}
else
	diff.reduce();
return diff;
}

Rational Rational::operator*(const Rational &R_val)
{
Rational pdt;
pdt.n = (n * R_val.n);
pdt.d = (d * R_val.d);
if(pdt .n < 0){
	pdt.n *= -1;
	pdt.reduce();
	pdt.n *= -1;
}
else
	pdt.reduce();
return pdt; 
}

Rational Rational::operator/(const Rational &R_val)
{
Rational res;
res.n = (n * R_val.d);
res.d = (d * R_val.n);
if(res.d < 0){
	res.n *= -1;
	res.d *= -1;
}
if(res .n < 0){
	res.n *= -1;
	res.reduce();
	res.n *= -1;
}
else
	res.reduce();
return res; 
}
Rational Rational::operator%(const Rational &R_val)
{
Rational res(n,d),mod;
res /= R_val;
mod.n = ((res.n) % (res.d));
mod.d = res.d;
return mod;
}
//Relational operators
bool Rational::operator<(Rational R_val)
{
if(abs() < (R_val.abs()))
	return true;
else
	return false;
}
bool Rational::operator>(Rational R_val)
{
if(abs() > (R_val.abs()))
	return true;
else
	return false;
}
bool Rational::operator<=(Rational R_val)
{
if(abs() <= (R_val.abs()))
	return true;
else
	return false;
}
bool Rational::operator>=(Rational R_val)
{
if(abs() >= (R_val.abs()))
	return true;
else
	return false;
}
bool Rational::operator==(Rational R_val)
{
if(abs() == R_val.abs())
	return true;
else
	return false;
}
bool Rational::operator!=(Rational R_val)
{
if(abs() != R_val.abs())
	return true;
else
	return false;
}
//compound assignment operators
void Rational::operator+=(const Rational &R_val)
{
Rational res(n,d); 
res = res + R_val;
n = res.n;
d = res.d;  
}
void Rational::operator-=(const Rational &R_val)
{
Rational res(n,d); 
res = res - R_val;
n = res.n;
d = res.d;
}

void Rational::operator*=(const Rational &R_val)
{
Rational res(n,d); 
res = res * R_val;
n = res.n;
d = res.d;
}
void Rational::operator/=(const Rational &R_val)
{
Rational res(n,d); 
res = res / R_val;
n = res.n;
d = res.d;
}
void Rational::operator%=(const Rational &R_val)
{
Rational res(n,d); 
res = res % R_val;
n = res.n;
d = res.d;
}
//Overloaded arithmatic operators
Rational Rational::operator+(const int &R_val)
{
Rational Rnum(R_val,1),result(n,d); 
result += Rnum;
return result;
}
Rational Rational::operator-(const int &R_val)
{
Rational Rnum(R_val,1),result(n,d); 
result -= Rnum;
return result;
}
Rational Rational::operator*(const int &R_val)
{
Rational Rnum(R_val,1),result(n,d); 
result *= Rnum;
return result;
}
Rational Rational::operator/(const int &R_val)
{
Rational Rnum(R_val,1),result(n,d); 
result /= Rnum;
return result;
}
Rational Rational::operator%(const int &R_val)
{
Rational Rnum(R_val,1),result(n,d); 
result %= Rnum;
return result;
}
//overloaded relational operators
bool Rational::operator<(const int &R_val)
{
if(abs() < R_val)
	return true;
else
	return false;
}
bool Rational::operator>(const int &R_val)
{
if(abs() > R_val)
	return true;
else
	return false;
}
bool Rational::operator<=(const int &R_val)
{
if(abs() <= R_val)
	return true;
else
	return false;
}
bool Rational::operator>=(const int &R_val)
{
if(abs() >= R_val)
	return true;
else
	return false;
}
bool Rational::operator==(const int &R_val)
{
if(abs() == R_val)
	return true;
else
	return false;
}
bool Rational::operator!=(const int &R_val)
{
if(abs() != R_val)
	return true;
else
	return false;
}

//overloaded compound assignment operators
void Rational::operator+=(const int &R_val)
{
Rational Rnum(R_val,1),result(n,d); 
result += Rnum;
n = result.n;
d = result.d;
}
void Rational::operator-=(const int &R_val)
{
Rational Rnum(R_val,1),result(n,d); 
result -= Rnum;
n = result.n;
d = result.d;
}
void Rational::operator*=(const int &R_val)
{
Rational Rnum(R_val,1),result(n,d); 
result *= Rnum;
n = result.n;
d = result.d;
}
void Rational::operator/=(const int &R_val)
{
Rational Rnum(R_val,1),result(n,d); 
result /= Rnum;
n = result.n;
d = result.d;
}
void Rational::operator%=(const int &R_val)
{
Rational Rnum(R_val,1),result(n,d); 
result %= Rnum;
n = result.n;
d = result.d;
}
//increment decrement operators
void Rational::operator++()
{
Rational Rnum(1,1),result(n,d);
result += Rnum;
n = result.n;
d = result.d; 
}
void Rational::operator--()
{
Rational Rnum(1,1),result(n,d);
result -= Rnum;
n = result.n;
d = result.d; 
}
void Rational::operator++(int R_val)
{
Rational Rnum(1,1),result(n,d);  
result += Rnum;
n = result.n;
d = result.d;
}
void Rational::operator--(int R_val)
{
Rational Rnum(1,1),result(n,d); 
result -= Rnum;
n = result.n;
d = result.d;
}
#endif
