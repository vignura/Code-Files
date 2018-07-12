#ifndef RATIONAL1_H
#define RATIONAL1_H
#include "Factorise.h"
class Rational{
int sign;//stores the sign of the Rational number
unsigned int int_val;//interger value of the Rational number
unsigned int n;//(n/d) is the fractional part of the Rational number
unsigned int d;
//private member functions
int getLCM(int,int);
int getHCF(int,int);
void toRational(double num);
void reduce(long long int ,long long int);
int findtype(const char *type);
bool str_cmp(const char *data,const char *type);
void print_array(int *array,int len);
//public member functions
public:
//constructors for initialization
Rational();
Rational(int val);
Rational(double val);
Rational(int nu,int de);
//auxillary functions
double abs();
double mag();
int abs_int();
int mag_int();
bool is_int();
void reduce();
//io functions
void print();
void getUserIp(const char *type);
//assignment operator
void operator=(const Rational &Rval);
void operator=(const int &Rval);
void operator=(const double &Rval);
//arithmatic operators
Rational operator+(Rational R_val);
Rational operator+(int R_val);
Rational operator+(double R_val);
//
Rational operator-(Rational R_val);
Rational operator-(int R_val);
Rational operator-(double R_val);
//
Rational operator*(Rational R_val);
Rational operator*(int R_val);
Rational operator*(double R_val);
//
Rational operator/(Rational R_val);
Rational operator/(int R_val);
Rational operator/(double R_val);
//
Rational operator%(Rational R_val);
Rational operator%(int R_val);
Rational operator%(double R_val);
//Arithmatic compound assignment operators
//
Rational operator+=(Rational R_val);
Rational operator+=(int R_val);
Rational operator+=(double R_val);
//
Rational operator-=(Rational R_val);
Rational operator-=(int R_val);
Rational operator-=(double R_val);
//
Rational operator*=(Rational R_val);
Rational operator*=(int R_val);
Rational operator*=(double R_val);
//
Rational operator/=(Rational R_val);
Rational operator/=(int R_val);
Rational operator/=(double R_val);
//
Rational operator%=(Rational R_val);
Rational operator%=(int R_val);
Rational operator%=(double R_val);
//Relational operators
bool operator<(Rational R_val);
bool operator<(int R_val);
bool operator<(double R_val);
//
bool operator>(Rational R_val);
bool operator>(int R_val);
bool operator>(double R_val);
//
bool operator<=(Rational R_val);
bool operator<=(int R_val);
bool operator<=(double R_val);
//
bool operator>=(Rational R_val);
bool operator>=(int R_val);
bool operator>=(double R_val);
//
bool operator==(Rational R_val);
bool operator==(int R_val);
bool operator==(double R_val);
//
bool operator!=(Rational R_val);
bool operator!=(int R_val);
bool operator!=(double R_val);
//increment decrement operators
void operator++();
void operator--();
void operator++(int R_val);
void operator--(int R_val);
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						/* PRIVATE MEMBER FUNCTIONS */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//print array function
//int array printing function
void Rational::print_array(int *array,int len)
{
for(int i = 0; i < len; i++)
{
std::cout<<array[i]<<std::endl;
}
}
//to Rational function
void Rational::toRational(double num)
{
long long int nu,de = 1000000;
nu = num * de;
//std::cout<<"nu = "<<nu<<"\tde = "<<de<<std::endl;
if(nu % 10 == 9)
	nu++;
//std::cout<<"nu = "<<nu<<"\tde = "<<de<<std::endl;
reduce(nu,de); 
}
//Fraction reducing function
void Rational::reduce(long long int nu1,long long int de1)
{
//std::cout<<"nu1 = "<<nu1<<"\tde1 = "<<de1<<std::endl;
int numerator = 1, denominator = 1;
int *nu_factors,*de_factors;
Fact nu,de;
//factorising
nu.factorise(nu1);
nu_factors = nu.factors();
de.factorise(de1);
de_factors = de.factors();
//printing factors
/*
std::cout<<"nu factors..."<<std::endl;
print_array(nu_factors,nu.len());
std::cout<<"de factors..."<<std::endl;
print_array(de_factors,de.len());*/
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
//calculating the reduced values of numerator and denominator
for(int i = 0; i < nu.len()-1; i++)
{
	numerator *= nu_factors[i];
}
for(int i = 0; i < de.len()-1; i++)
{
	denominator *= de_factors[i];
}
//std::cout<<"n = "<<numerator<<"\td = "<<denominator<<std::endl;
n = numerator;
d = denominator;
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
//Finds the type of input to get(int , float or Rational)
int Rational::findtype(const char *type)
{
if(str_cmp("int",type))
	return 1;
if(str_cmp("float",type))
	return 2;
if(str_cmp("Rational",type))
	return 3;
}
//string compare functon
bool Rational::str_cmp(const char *data,const char *type)
{
int len;
for(int i = 0;((data[i] != 0) && (type[i] != 0));i++)
{
	if(data[i] != type[i])
		return false;
}
return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						/* PUBLIC MEMBER FUNCTIONS */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						/* CONSTRUCTORS */
//default constructor
Rational::Rational(){sign = 1; int_val = 0; n = 0; d = 1;}
//initializes the an object to a integer value
Rational::Rational(int val)
{
if(val < 0)
	sign = -1;
else
	sign = 1;
int_val = (val * sign);
n = 0; 
d = 1;
}
//initializes the an object to a float value
Rational::Rational(double val)
{
if(val < 0)
	sign = -1;
else
	sign = 1;
int_val = ((double)sign * val);
val = (double)sign * val;
val = val - (double)int_val;
toRational(val);
}
//initializes the an object to a Rational (n / d) value
Rational::Rational(int nu,int de)
{
if(de < 0){ de *= -1; nu *= -1;}
if(nu < 0){sign = -1;nu *= -1;}
else{sign = 1;}
int_val = nu / de;
n = nu % de;
d = de;
}
						/*AUXILLARY FUCTIONS*/
//absolute value returinig function
double Rational::abs()
{
return ((double)sign * ((double)int_val + (n / (double)d)));
}
//absolute magnitude returinig function
double Rational::mag()
{
return ((double)int_val + (n / (double)d));
}
//returns abs as int
int Rational::abs_int()
{
return (sign * (int)int_val);
}
//absolute magnitude returinig function
int Rational::mag_int()
{
return (int)int_val;
}
//is int checks wheather the number is a integer
bool Rational::is_int()
{
if(abs() == (int)abs())
	return true;
else
	return false;
} 
//fraction reducing function
void Rational::reduce()
{
reduce(n,d);
}
						/*IO FUNCTIONS*/
//printing function
void Rational::print()
{
if(sign < 0)
	std::cout<<"-";
std::cout<<int_val<<" ("<<n<<" / "<<d<<")";
}
//gets input from user using strandard inputs
void Rational::getUserIp(const char *type)
{
int choice;
choice = findtype(type);
switch(choice)
{
case 1:{
	int num;
	std::cout<<"enter an integer: ";
	std::cin>>num;
	if(num < 0)
		sign = -1;
	else
		sign = 1;
	int_val = sign * num;
	n = 0;
	d = 1;
}break;
case 2:{
	double num;
	std::cout<<"enter a (float) number: ";
	std::cin>>num;
	if(num < 0)
		sign = -1;
	else
		sign = 1;
	int_val = ((double)sign * num);
	num = (double)sign * num;
	num = num - (double)int_val;
	toRational(num);
}break;
case 3:{
	int nu,de;
	std::cout<<"enter the value of numerator: ";
	std::cin>>nu;
	std::cout<<"enter the value of deneminator: ";
	std::cin>>de;
	if(de < 0){ de *= -1; nu *= -1;}
	if(nu < 0){sign = -1;nu *= -1;}
	else{sign = 1;}
	int_val = nu / de;
	n = nu % de;
	d = de;
}break;
}
}
							/*ASSIGNMENT OPERATOR*/
//Assignment operator
void Rational::operator=(const Rational &Rval)
{
sign = Rval.sign;
int_val = Rval.int_val;
n = Rval.n;
d = Rval.d;
}
//Overloaded assignment operator for handling int
void Rational::operator=(const int &Rval)
{
if(Rval < 0)
	sign = -1;
else
	sign = 1;
int_val = (Rval * sign);
n = 0; 
d = 1;
}
//Overloaded assignment operator for handling double
void Rational::operator=(const double &Rval)
{
double val = Rval;
if(val < 0)
	sign = -1;
else
	sign = 1;
int_val = ((double)sign * val);
val = (double)sign * val;
val = val - (double)int_val;
toRational(val);
}
						/*ARITHMATIC OPERATORS*/
				//overloading '+' operator to handle Rational + Rational data 
Rational Rational::operator+(Rational R_val)
{
Rational sum;
int LCM;
bool dec = false,dec1 = false;
//assigning the sign of sum to the sign of the number with largest magnitude
if(mag() < R_val.mag())
	sum.sign = R_val.sign;
else
	sum.sign = sign;
//borrow operation
if(((n/(double)d) < (R_val.n/(double)R_val.d)) && (int_val > 0)){
int_val--;
n = n + d;
dec = true;
}
//special case when int_val is zero
if((int_val == 0) && (R_val.int_val > 0)){
R_val.int_val--;
R_val.n += R_val.d;
dec1 == true;
}
//Addition	
sum.int_val = sum.sign * ((int)(sign * int_val) + (int)(R_val.sign * R_val.int_val));
LCM = getLCM(d,R_val.d);
int tmp1 = (sign * ((n * LCM) / d)) + (R_val.sign * ((R_val.n * LCM) / R_val.d));
if(tmp1 < 0)
	tmp1 *= -1;
sum.int_val += (tmp1 / LCM);
sum.n = (tmp1 % LCM);
sum.d = LCM;
//reversing borrow operation 
if(dec){
int_val += (n / d);
n = n % d;
}
//reversing the decrement due to special case for zero int_val
if(dec1){
R_val.int_val += (R_val.n / R_val.d);
R_val.n = R_val.n % R_val.d;
}
sum.reduce();
return sum;
}
//handles int argument
Rational Rational::operator+(int R_val)
{
Rational sum,lval,Rval(R_val);
lval.sign = sign;
lval.int_val = int_val;
lval.n = n;
lval.d = d;
sum = lval + Rval;
return sum;
}
//handles double argument
Rational Rational::operator+(double R_val)
{
Rational sum,lval,Rval(R_val);
lval.sign = sign;
lval.int_val = int_val;
lval.n = n;
lval.d = d;
sum = lval + Rval;
return sum;
}
			//overloading '-' operator to handle Rational - Rational data 
Rational Rational::operator-(Rational R_val)
{
Rational diff,Rval;
Rval = R_val;
int LCM,neg = 1;
//assigning the sign of diff
if(mag() < Rval.mag()){
	diff.sign = (Rval.sign * -1);
}
else
	diff.sign = sign;
//decrementing the Rval when factional part of Rval is smaller than this val
if(((n/(double)d) > (Rval.n/(double)Rval.d)) && (Rval.mag() > mag()) && (abs() > 0)){
if(Rval.int_val > 0){
	Rval.int_val--;
	Rval.n+= Rval.d;
	}
}
//borrow operation
if((n/(double)d) < (Rval.n/(double)Rval.d) && (mag() > Rval.mag())){
if(int_val > 0){
int_val--;
n = n + d;
}
}
//subtracting the two numbers	
diff.int_val = diff.sign * ((sign * int_val) - (Rval.sign * Rval.int_val));
LCM = getLCM(d,Rval.d);
int tmp1 = (sign * ((n * LCM) / d)) - (Rval.sign *((Rval.n * LCM) / Rval.d));
if(tmp1 < 0)
	tmp1 *= -1;
diff.int_val += (tmp1 / LCM);
diff.n = (tmp1 % LCM);
diff.d = LCM;
diff.reduce();
return diff;
}
//handles int argument
Rational Rational::operator-(int R_val)
{
Rational diff,lval,Rval(R_val);
lval.sign = sign;
lval.int_val = int_val;
lval.n = n;
lval.d = d;
diff = lval - Rval;
return diff;
}
//handles double argument
Rational Rational::operator-(double R_val)
{
Rational diff,lval,Rval(R_val);
lval.sign = sign;
lval.int_val = int_val;
lval.n = n;
lval.d = d;
diff = lval - Rval;
return diff;
}
			//overloading '*' operator to handle Rational * Rational data 
Rational Rational::operator*(Rational R_val)
{
Rational pdt;
int LCM;
int tmp_n;
pdt.sign = sign * R_val.sign;
pdt.int_val = int_val * R_val.int_val;
pdt.n = n * R_val.n;
pdt.d = d * R_val.d;
LCM = getLCM(pdt.d,getLCM(R_val.d,d));
tmp_n = ((int_val * R_val.n) * (LCM / R_val.d)) + ((R_val.int_val * n) * (LCM / d)) + (pdt.n * (LCM / pdt.d));
pdt.int_val += (tmp_n / LCM);
pdt.n = tmp_n % LCM;
pdt.d = LCM;
pdt.reduce();
return pdt;
}
//handles int argument
Rational Rational::operator*(int R_val)
{
Rational pdt,lval,Rval(R_val);
lval.sign = sign;
lval.int_val = int_val;
lval.n = n;
lval.d = d;
pdt = lval * Rval;
return pdt;
}
//handles double argument
Rational Rational::operator*(double R_val)
{
Rational pdt,lval,Rval(R_val);
lval.sign = sign;
lval.int_val = int_val;
lval.n = n;
lval.d = d;
pdt = lval * Rval;
return pdt;
}
			//overloading '/' operator to handle Rational / Rational data 
Rational Rational::operator/(Rational R_val)
{
Rational res;
res.sign = sign * R_val.sign;
unsigned long long nu,de;
nu = ((int_val * d) + n) * R_val.d;
de = ((R_val.int_val * R_val.d) + R_val.n) * d;
if(de != 0){
res.int_val = nu / de;
res.n = nu % de;
res.d = de;
res.reduce();
}
else{res.int_val = 0; res.n = 0; res.d = 1;}
return res;
}
//handles int argument
Rational Rational::operator/(int R_val)
{
Rational res,lval,Rval(R_val);
lval.sign = sign;
lval.int_val = int_val;
lval.n = n;
lval.d = d;
res = lval / Rval;
return res;
}
//handles double argument
Rational Rational::operator/(double R_val)
{
Rational res,lval,Rval(R_val);
lval.sign = sign;
lval.int_val = int_val;
lval.n = n;
lval.d = d;
res = lval / Rval;
return res;
}
			//overloading '%' operator to handle Rational % Rational data
Rational Rational::operator%(Rational R_val)
{
Rational rem,tmp;
tmp.sign = sign;
tmp.int_val = int_val;
tmp.n = n;
tmp.d = d;
rem = tmp / R_val;
rem.sign = 1;
rem.int_val = 0;
return rem;
}
//handles int argument
Rational Rational::operator%(int R_val)
{
Rational rem,lval,Rval(R_val);
lval.sign = sign;
lval.int_val = int_val;
lval.n = n;
lval.d = d;
rem = lval % Rval;
return rem;
}
//handles double argument
Rational Rational::operator%(double R_val)
{
Rational rem,lval,Rval(R_val);
lval.sign = sign;
lval.int_val = int_val;
lval.n = n;
lval.d = d;
rem = lval % Rval;
return rem;
}
					/*ARITHMATIC COMPOUND ASSIGNMENT OPERATOR*/
			//overloading '+=' operator to handle Rational += Rational data
Rational Rational::operator+=(Rational R_val)
{
Rational res;
//coping this value to res
res.sign = sign;
res.int_val = int_val;
res.n = n;
res.d = d;
//adding
res = res + R_val;
//reassignig sum to this
sign = res.sign;
int_val =res.int_val;
n = res.n;
d = res.d;
}
//handles int argument
Rational Rational::operator+=(int R_val)
{
Rational res,Rval(R_val);
//coping this value to res
res.sign = sign;
res.int_val = int_val;
res.n = n;
res.d = d;
//adding
res = res + Rval;
//reassignig sum to this
sign = res.sign;
int_val =res.int_val;
n = res.n;
d = res.d;
}
//handles double argument
Rational Rational::operator+=(double R_val)
{
Rational res,Rval(R_val);
//coping this value to res
res.sign = sign;
res.int_val = int_val;
res.n = n;
res.d = d;
//adding
res = res + Rval;
//reassignig sum to this
sign = res.sign;
int_val =res.int_val;
n = res.n;
d = res.d;
}
			//overloading '-=' operator to handle Rational -= Rational data
Rational Rational::operator-=(Rational R_val)
{
Rational res;
//coping this value to res
res.sign = sign;
res.int_val = int_val;
res.n = n;
res.d = d;
//subtracting
res = res - R_val;
//reassignig sum to this
sign = res.sign;
int_val =res.int_val;
n = res.n;
d = res.d;
}
//handles int argument
Rational Rational::operator-=(int R_val)
{
Rational res,Rval(R_val);
//coping this value to res
res.sign = sign;
res.int_val = int_val;
res.n = n;
res.d = d;
//subtracting
res = res - Rval;
//reassignig sum to this
sign = res.sign;
int_val =res.int_val;
n = res.n;
d = res.d;
}
//handles double argument
Rational Rational::operator-=(double R_val)
{
Rational res,Rval(R_val);
//coping this value to res
res.sign = sign;
res.int_val = int_val;
res.n = n;
res.d = d;
//subtracting
res = res - Rval;
//reassignig sum to this
sign = res.sign;
int_val =res.int_val;
n = res.n;
d = res.d;
}
			//overloading '*=' operator to handle Rational *= Rational data
Rational Rational::operator*=(Rational R_val)
{
Rational res;
//coping this value to res
res.sign = sign;
res.int_val = int_val;
res.n = n;
res.d = d;
//multipling
res = res * R_val;
//reassignig sum to this
sign = res.sign;
int_val =res.int_val;
n = res.n;
d = res.d;
}
//handles int argument
Rational Rational::operator*=(int R_val)
{
Rational res,Rval(R_val);
//coping this value to res
res.sign = sign;
res.int_val = int_val;
res.n = n;
res.d = d;
//multipling
res = res * Rval;
//reassignig sum to this
sign = res.sign;
int_val =res.int_val;
n = res.n;
d = res.d;
}
//handles double argument
Rational Rational::operator*=(double R_val)
{
Rational res,Rval(R_val);
//coping this value to res
res.sign = sign;
res.int_val = int_val;
res.n = n;
res.d = d;
//multipling
res = res * Rval;
//reassignig sum to this
sign = res.sign;
int_val =res.int_val;
n = res.n;
d = res.d;
}
			//overloading '/=' operator to handle Rational /= Rational data
Rational Rational::operator/=(Rational R_val)
{
Rational res;
//coping this value to res
res.sign = sign;
res.int_val = int_val;
res.n = n;
res.d = d;
//dividing
res = res / R_val;
//reassignig sum to this
sign = res.sign;
int_val =res.int_val;
n = res.n;
d = res.d;
}
//handles int argument
Rational Rational::operator/=(int R_val)
{
Rational res,Rval(R_val);
//coping this value to res
res.sign = sign;
res.int_val = int_val;
res.n = n;
res.d = d;
//dividing
res = res / Rval;
//reassignig sum to this
sign = res.sign;
int_val =res.int_val;
n = res.n;
d = res.d;
}
//handles double argument
Rational Rational::operator/=(double R_val)
{
Rational res,Rval(R_val);
//coping this value to res
res.sign = sign;
res.int_val = int_val;
res.n = n;
res.d = d;
//dividing
res = res / Rval;
//reassignig sum to this
sign = res.sign;
int_val =res.int_val;
n = res.n;
d = res.d;
}
			//overloading '%=' operator to handle Rational %= Rational data
Rational Rational::operator%=(Rational R_val)
{
Rational res;
//coping this value to res
res.sign = sign;
res.int_val = int_val;
res.n = n;
res.d = d;
//mod
res = res % R_val;
//reassignig sum to this
sign = res.sign;
int_val =res.int_val;
n = res.n;
d = res.d;
}
//handles int argument
Rational Rational::operator%=(int R_val)
{
Rational res,Rval(R_val);
//coping this value to res
res.sign = sign;
res.int_val = int_val;
res.n = n;
res.d = d;
//mod
res = res % Rval;
//reassignig sum to this
sign = res.sign;
int_val =res.int_val;
n = res.n;
d = res.d;
}
//handles double argument
Rational Rational::operator%=(double R_val)
{
Rational res,Rval(R_val);
//coping this value to res
res.sign = sign;
res.int_val = int_val;
res.n = n;
res.d = d;
//mod
res = res % Rval;
//reassignig sum to this
sign = res.sign;
int_val =res.int_val;
n = res.n;
d = res.d;
}
						/*RELATIONAL OPERATORS*/
			//overloading '<' operator to handle Rational < Rational data
bool Rational::operator<(Rational R_val)
{
if(abs() < R_val.abs())
	return true;
else
	return false;
}
//handles int argument
bool Rational::operator<(int R_val)
{
if(abs() < R_val)
	return true;
else
	return false;
}
//handles double argument
bool Rational::operator<(double R_val)
{
if(abs() < R_val)
	return true;
else
	return false;
}
			//overloading '>' operator to handle Rational > Rational data
bool Rational::operator>(Rational R_val)
{
if(abs() > R_val.abs())
	return true;
else
	return false;
}
//handles int argument
bool Rational::operator>(int R_val)
{
if(abs() > R_val)
	return true;
else
	return false;
}
//handles double argument
bool Rational::operator>(double R_val)
{
if(abs() > R_val)
	return true;
else
	return false;
}
			//overloading '<=' operator to handle Rational <= Rational data
bool Rational::operator<=(Rational R_val)
{
if(abs() <= R_val.abs())
	return true;
else
	return false;
}
//handles int argument
bool Rational::operator<=(int R_val)
{
if(abs() <= R_val)
	return true;
else
	return false;
}
//handles double argument
bool Rational::operator<=(double R_val)
{
if(abs() <= R_val)
	return true;
else
	return false;
}
			//overloading '>=' operator to handle Rational >= Rational data
bool Rational::operator>=(Rational R_val)
{
if(abs() >= R_val.abs())
	return true;
else
	return false;
}
//handles int argument
bool Rational::operator>=(int R_val)
{
if(abs() >= R_val)
	return true;
else
	return false;
}
//handles double argument
bool Rational::operator>=(double R_val)
{
if(abs() >= R_val)
	return true;
else
	return false;
}
			//overloading '==' operator to handle Rational == Rational data
bool Rational::operator==(Rational R_val)
{
if(abs() == R_val.abs())
	return true;
else
	return false;
}
//handles int argument
bool Rational::operator==(int R_val)
{
if(abs() == R_val)
	return true;
else
	return false;
}
//handles double argument
bool Rational::operator==(double R_val)
{
if(abs() == R_val)
	return true;
else
	return false;
}
			//overloading '!=' operator to handle Rational != Rational data
bool Rational::operator!=(Rational R_val)
{
if(abs() != R_val.abs())
	return true;
else
	return false;
}
//handles int argument
bool Rational::operator!=(int R_val)
{
if(abs() != R_val)
	return true;
else
	return false;
}
//handles double argument
bool Rational::operator!=(double R_val)
{
if(abs() != R_val)
	return true;
else
	return false;
}
						/*INCREMENT DECREMENT OPERATORS*/
//prefix increment operator
void Rational::operator++()
{
Rational Rnum(1),res;
res.sign = sign; 
res.int_val = int_val; 
res.n = n;
res.d = d;
//incrementing
res += Rnum;
//reassignig
sign = res.sign;
int_val = res.int_val;
n = res.n;
d = res.d; 
}
//prefix decrement operator
void Rational::operator--()
{
Rational Rnum(1),res;
res.sign = sign; 
res.int_val = int_val; 
res.n = n;
res.d = d;
//incrementing
res -= Rnum;
//reassignig
sign = res.sign;
int_val = res.int_val;
n = res.n;
d = res.d;
}
//postfix increment operator
void Rational::operator++(int R_val)
{
Rational Rnum(1),res;
res.sign = sign; 
res.int_val = int_val; 
res.n = n;
res.d = d;
//incrementing
res += Rnum;
//reassignig
sign = res.sign;
int_val = res.int_val;
n = res.n;
d = res.d;
}
//postfix decrement operator
void Rational::operator--(int R_val)
{
Rational Rnum(1),res;
res.sign = sign; 
res.int_val = int_val; 
res.n = n;
res.d = d;
//incrementing
res -= Rnum;
//reassignig
sign = res.sign;
int_val = res.int_val;
n = res.n;
d = res.d;
}
#endif
