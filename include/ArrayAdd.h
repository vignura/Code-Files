#ifndef ARRAYADD
#define ARRAYADD
#include <cstdlib>
class ArrayAdd{
	int * c;
	int len;
	public:
	int arrlen(int *);
	int arrlen();	
	void print(int *,int);
	void print();	
	int * resize(int *,int);
	int * addArray(int *,int *);
};
//
int ArrayAdd::arrlen(int * arr)
{	
	int len = 0;
	len = sizeof(arr) / sizeof(int);
	return len;
}
//
int ArrayAdd::arrlen()
{
	return len;
}
//
void ArrayAdd::print(int *array,int limit)
{
	if(array[0] != 0)
		std::cout<<array[0];
	for(int i = 1; i < limit; i++)
	{
		std::cout<<array[i];
	}
}
//
void ArrayAdd::print()
{
	print(c,arrlen(c));
}
//
int * ArrayAdd::resize(int *arr,int size)
{
	int len_arr = arrlen(arr);
	int * ARR = (int *)calloc(size,sizeof(int));	
	for(int i = 0; i < (size - len_arr); i++)
	{
		ARR[i] = 0;
	}
	for(int i = 0; i < len_arr; i++)
	{
		ARR[(size - len_arr) + i] = arr[i];
	}
	return ARR;
}
//
int * ArrayAdd::addArray(int *a,int *b)
{
	int sum,carry = 0;
	//resizing array
	int lena = arrlen(a);
	int lenb = arrlen(b);
	len = lena + 1;
	if(lena > lenb){
		b = resize(b,lena);
		len = lena + 1;	
	}
	else if(lena < lenb){
		a = resize(a,lenb);
		len = lenb + 1;
	}
	//creating pointer
	int * c = (int *)calloc(len,sizeof(int));
	//adding
	for(int i = len -1; i > 0; i--)
	{
		sum = carry + a[i-1] + b[i-1];
		c[i] = sum % 10;
		carry = sum /10;
	}
	c[0] = carry;
	//std::cout<<std::endl;print(c,len);std::cout<<std::endl;
	//std::cout<<"c = "<<c<<std::endl;	
	return c;
}
//
#endif
