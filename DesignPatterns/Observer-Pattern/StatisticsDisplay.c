#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "StatisticsDisplay.h"
#include "WeatherData.h"

#define MOVING_AVERAGE_SAMPLE_COUNT 16

// globals
float temperature;
float avgTemp;
float minTemp;
float maxTemp;
pthread_mutex_t statMutex = PTHREAD_MUTEX_INITIALIZER;

// private functions
// should be called when holding mutex
static void updateStatistics(float temperature)
{
	static int count = 0;
	float locAvgTemp = 0;

	if(count < MOVING_AVERAGE_SAMPLE_COUNT)
	{
		avgTemp = temperature;
		locAvgTemp += temperature;
		count++;
	}
	else if (count == MOVING_AVERAGE_SAMPLE_COUNT)
	{
		avgTemp = locAvgTemp / MOVING_AVERAGE_SAMPLE_COUNT;
		count++;
	}
	else
	{
		avgTemp = (avgTemp * MOVING_AVERAGE_SAMPLE_COUNT + temperature) / (MOVING_AVERAGE_SAMPLE_COUNT + 1);
	}

	if(minTemp > temperature)
	{
		minTemp = temperature;
	}

	if(maxTemp < temperature)
	{
		maxTemp = temperature;
	}
}

static void weatherDataUpdated()
{
	pthread_mutex_lock(&statMutex);
	temperature = weatherDataGetTemperature();
	updateStatistics(temperature);
	pthread_mutex_unlock(&statMutex);
}

// public APIS
void initStatisticsDisplay()
{
	pthread_mutex_lock(&statMutex);
	temperature = 0;
	avgTemp = 0;
	minTemp = 100;
	maxTemp = 0;
	weatherDataRegisterObserver(&weatherDataUpdated);
	pthread_mutex_unlock(&statMutex);
}

void displayStatistics()
{
	pthread_mutex_lock(&statMutex);
	printf("STATISTICS: Avg / Min / Max: %2.2f / %2.2f /%2.2f deg C\n", avgTemp, minTemp, maxTemp);
	pthread_mutex_unlock(&statMutex);	
}