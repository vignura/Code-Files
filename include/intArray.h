#ifndef INTARRAY
#define INTARRAY
#include <vector>
using std::vector;
using std::cout;
using std::endl;
class intArray
{	
	vector<int> arr;
	public:
	void push_back(int);
	void pop_back();
	void operator[](int);
	void at(int);
	int size();
	bool empty();
	void clear();	
};
//
void intArray::push_back(int val)
{
	arr.push_back(val);
}
//
void intArray::pop_back()
{
	arr.pop_back();
}
//
int intArray::size()
{
	return arr.size();
}
//
bool intArray::empty()
{
	return arr.empty();
}
void intArray::clear()
{
	arr.clear();
}
//
int intArray::size()
{
	return (arr.size());
}
#endif
