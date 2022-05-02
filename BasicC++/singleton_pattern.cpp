#include <iostream>
#include <pthread.h>

using namespace std;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

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
		refernceCount++;
		if (instance != nullptr)
		{
			return instance;
		}

		pthread_mutex_lock(&mtx);
		if (instance == nullptr)
		{
			instance = new Singleton();
		}
		pthread_mutex_unlock(&mtx);
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