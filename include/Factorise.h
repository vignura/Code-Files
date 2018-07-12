#ifndef FACTORISE_H
#define FACTORISE_H
class Fact{
int factor[150];
int length;
int loop_count;
public:
void factorise(long long int num)
{
int c = 0;
loop_count = 0;
if(num == 0)
{
	factor[c] = 0;
	c++;
	factor[c] = 0; 
}
long long int num1 = num;
//std::cout<<"num1 = "<<num<<std::endl;
for(int i = 1; i <= num1; i++)
{	//std::cout<<"###num = "<<num1<<std::endl;
	loop_count++;	
	if(num1 % i == 0){
		num1 /= i;
		//std::cout<<"num1 = "<<num1<<" i = "<<i<<std::endl;
		factor[c] = i;
		c++;
		i = 1;
	} 	
}
factor[c] = num;
length = c+1;
}
int* factors()
{
return factor;
}
int len()
{
return length;
}
int getLoopCount()
{
return loop_count;
}
};
#endif
