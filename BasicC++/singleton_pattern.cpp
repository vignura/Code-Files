#include <iostream>

using namespace std;

class Singleton {

	static class Singleton *instance;
	static int instanceCount;
	static int refernceCount;

private:
	Singleton()
	{
		instanceCount++;
	}

public:
	static Singleton* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new Singleton();
		}
		refernceCount++;
		return instance;
	}

	int getInstanceCount()
	{
		return instanceCount;
	}

	int getReferenceCount()
	{
		return refernceCount;
	}

	~Singleton()
	{
		if (refernceCount > 0)
		{
			refernceCount--;
		}
	}
};

class Singleton* Singleton::instance;
int Singleton::instanceCount;
int Singleton::refernceCount;

int main(int argc, char const *argv[])
{
	Singleton *instance1 = Singleton::getInstance();
	cout << "instance count: " << instance1->getInstanceCount() << endl;
	cout << "refernce count: " << instance1->getReferenceCount() << endl;

	Singleton *instance2 = Singleton::getInstance();
	cout << "instance count: " << instance2->getInstanceCount() << endl;
	cout << "refernce count: " << instance1->getReferenceCount() << endl;

	Singleton *instance3 = Singleton::getInstance();
	cout << "instance count: " << instance3->getInstanceCount() << endl;
	cout << "refernce count: " << instance1->getReferenceCount() << endl;

	return 0;
}