#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "CurrentConditionsDisplay.h"
#include "WeatherData.h"

// globals
float temperature;
float humidity;
pthread_mutex_t currentConditionsMutex = PTHREAD_MUTEX_INITIALIZER;

// private functions
static void weatherDataUpdated()
{
	pthread_mutex_lock(&currentConditionsMutex);
	temperature = weatherDataGetTemperature();
	humidity = weatherDataGetHumidity();
	pthread_mutex_unlock(&currentConditionsMutex);
}

// public APIS
void initCurrentConditionsDisplay()
{
	pthread_mutex_lock(&currentConditionsMutex);
	temperature = 0;
	humidity = 0;
	weatherDataRegisterObserver(&weatherDataUpdated);
	pthread_mutex_unlock(&currentConditionsMutex);
}

void displayCurrentConditions()
{
	// printf("%s\n", __func__);
	pthread_mutex_lock(&currentConditionsMutex);
	printf("CURRENT CONDITIONS: temperature: %2.2f deg C humidity: %2.2f %% \n", temperature, humidity);
	pthread_mutex_unlock(&currentConditionsMutex);	
}