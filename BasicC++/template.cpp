#include <iostream>
#include <stdio.h>

using namespace std;

// template function
template <typename T> T add(T a, T b)
{
	return a + b;
}

// template class for a linked list node
template <typename T> class node {
	T data;
	node *next;	
};


int main(int argc, char const *argv[])
{
	printf ("adding integers: sum: %d\n", add(1, 2));
	printf ("adding double: sum: %lf\n", add(1.10000001, 2.2000001));
	printf ("adding float: sum: %f\n", add(1.1f, 2.2f));
	
	return 0;
}