#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "StatisticsDisplay.h"
#include "WeatherData.h"

// globals
float temperature;
float avgTemp;
float minTemp;
float maxTemp;
pthread_mutex_t statMutex = PTHREAD_MUTEX_INITIALIZER;

// private functions
static void weatherDataUpdated()
{
	pthread_mutex_lock(&statMutex);
	temperature = weatherDataGetTemperature();
	
	avgTemp = temperature;

	if(minTemp > temperature)
	{
		minTemp = temperature;
	}

	if(maxTemp < temperature)
	{
		maxTemp = temperature;
	}
	pthread_mutex_unlock(&statMutex);
}

// public APIS
void initStatisticsDisplay()
{
	pthread_mutex_lock(&statMutex);
	temperature = 0;
	weatherDataRegisterObserver(&weatherDataUpdated);
	pthread_mutex_unlock(&statMutex);
}

void displayStatistics()
{
	pthread_mutex_lock(&statMutex);
	printf("STATISTICS: Avg / Min / Max: %2.2f / %2.2f /%2.2f deg C\n", avgTemp, minTemp, maxTemp);
	pthread_mutex_unlock(&statMutex);	
}