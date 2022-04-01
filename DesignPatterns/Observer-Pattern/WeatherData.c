#include "WeatherData.h"
#include <pthread.h>
#include <string.h>
#include <stdio.h>

// private macros
#define MAX_OBSERVERS_ALLOWED	64

// private structs
typedef struct ObserverList
{
	weatherDataChanged observers[MAX_OBSERVERS_ALLOWED];
	int count;
} ObserverList;

// global variables
WeatherData weatherData;
ObserverList observerList;
pthread_mutex_t weatherDataMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t observerListMutex = PTHREAD_MUTEX_INITIALIZER;

// private functions
static int getObserverIndex(weatherDataChanged observer)
{
	int index = -1;
	pthread_mutex_lock(&observerListMutex);
	for(int index = 0; index < observerList.count; index++)
	{
		if(observerList.observers[index] == observer)
		{
			return index;
		}
	}
	pthread_mutex_unlock(&observerListMutex);
	return index;
}

static bool addObserver(weatherDataChanged observer)
{
	bool result = false;

	if (observerList.count < MAX_OBSERVERS_ALLOWED)
	{
		pthread_mutex_lock(&observerListMutex);
		observerList.observers[observerList.count] = observer;
		observerList.count++;
		pthread_mutex_unlock(&observerListMutex);
		result = true;
	}
	else
	{
		printf("%s maximum observers reached! falied to add new observer\n", __func__);
	}

	return result;
}

static bool deleteObserver(int index, weatherDataChanged observer)
{
	bool result = false;

	pthread_mutex_lock(&observerListMutex);
	if (index >= 0 && index < observerList.count)
	{
		observerList.observers[index] = NULL;
		for (int i = index; i < observerList.count -1; i++)
		{
			observerList.observers[i] = observerList.observers[i + 1];
		}
		observerList.count--;
		result = true;
	}

	pthread_mutex_unlock(&observerListMutex);

	return result;
}

// public APIs
void weatherDataInit()
{
	pthread_mutex_lock(&weatherDataMutex);
	memset(&weatherData, 0, sizeof(WeatherData));	
	pthread_mutex_unlock(&weatherDataMutex);

	pthread_mutex_lock(&observerListMutex);
	memset(&observerList, 0, sizeof(ObserverList));
	pthread_mutex_unlock(&observerListMutex);
}

void weatherDataSet(float temperature, float humidity)
{
	pthread_mutex_lock(&weatherDataMutex);
	weatherData.temperature = temperature;
	weatherData.humidity = humidity;
	pthread_mutex_unlock(&weatherDataMutex);

	weatherDataStateChanged();
}

float weatherDataGetTemperature()
{
	pthread_mutex_lock(&weatherDataMutex);
	float temperature = weatherData.temperature;
	pthread_mutex_unlock(&weatherDataMutex);

	return temperature;
}

float weatherDataGetHumidity()
{
	pthread_mutex_lock(&weatherDataMutex);
	float humidity = weatherData.humidity;
	pthread_mutex_unlock(&weatherDataMutex);

	return humidity;
}

bool weatherDataRegisterObserver(weatherDataChanged observer)
{
	return addObserver(observer);
}

bool weatherDataUnregisterObserver(weatherDataChanged observer)
{
	bool result = false;
	
	int index = getObserverIndex(observer);
	if(index >= 0)
	{
		result = deleteObserver(index, observer);
	}

	return result;
}

void weatherDataNotifyObservers()
{
	// printf("%s\n", __func__);
	pthread_mutex_lock(&observerListMutex);
	for (int index = 0; index < observerList.count; index++)
	{
		observerList.observers[index]();
	}
	pthread_mutex_unlock(&observerListMutex);
}

void weatherDataStateChanged()
{
	// printf("%s\n", __func__);
	weatherDataNotifyObservers();
}