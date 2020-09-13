Rational Rational::operator+(Rational R_val)
{
Rational sum;
int LCM;
bool dec = false;
if(mag() < R_val.mag()){//std::cout<<"sign if is executed and R_val.sign  = "<<R_val.sign<<std::endl;
	sum.sign = R_val.sign;
}
else{//std::cout<<"sign else is executed and sign  = "<<sign<<std::endl;
	sum.sign = sign;}
//std::cout<<"sum.sign ="<<sum.sign<<std::endl;
if(((n/(double)d) < (R_val.n/(double)R_val.d)) && (int_val < 0)){
int_val--;
n = n + d;
dec = true;
}
//std::cout<<"int val (after borrow) = "<<int_val<<std::endl;	
sum.int_val = sum.sign * ((int)(sign * int_val) + (int)(R_val.sign * R_val.int_val));
//std::cout<<"sign * int_val = "<<(sign * int_val)<<"\tRval(sign * int_val) = "<<(R_val.sign * R_val.int_val)<<std::endl;
//std::cout<<"sum.int_val = "<<sum.int_val<<std::endl;
LCM = getLCM(d,R_val.d);
int tmp1 = (sign * ((n * LCM) / d)) + (R_val.sign * ((R_val.n * LCM) / R_val.d));
if(tmp1 < 0)
	tmp1 *= -1;
sum.int_val += (tmp1 / LCM);
//std::cout<<"sum.int_val (after adding)= "<<sum.int_val<<std::endl;
sum.n = (tmp1 % LCM);
sum.d = LCM;
//std::cout<<"sum.n = "<<sum.n<<"\tsum.d = "<<sum.d<<std::endl;
if(dec){
int_val += (n / d);
n = n % d;
}
return sum;
}
