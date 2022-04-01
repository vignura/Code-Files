#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "WeatherData.h"
#include "CurrentConditionsDisplay.h"
#include "StatisticsDisplay.h"

#define WEATHER_DATA_UPDATE_DELAY_SEC 					5
#define CURRENT_CONDITIONS_DISPLAY_UPDATE_DELAY_SEC		1

// private functions
static void* weatherDataTask(void *arg)
{
	float temperature = 25;
	float humidity = 50;

	while (true)
	{
		// printf("%s\n", __func__);
		weatherDataSet(temperature, humidity);

		if (temperature < 50)
		{
			temperature += 0.1;
		}
		else
		{
			temperature = 25;
		}

		if (humidity < 95)
		{
			humidity += 0.2;
		}
		else
		{
			humidity = 50;
		}
		sleep(WEATHER_DATA_UPDATE_DELAY_SEC);
	}

	return NULL;
}

static void* displayCurrentConditionsTask(void *arg)
{
	while (true)
	{
		// printf("%s\n", __func__);
		sleep(CURRENT_CONDITIONS_DISPLAY_UPDATE_DELAY_SEC);
		displayCurrentConditions();
	}

	return NULL;
}

static void* displayStatisticsTask(void *arg)
{
	while (true)
	{
		// printf("%s\n", __func__);
		sleep(CURRENT_CONDITIONS_DISPLAY_UPDATE_DELAY_SEC);
		displayStatistics();
	}

	return NULL;
}

int main(int argc, char const *argv[])
{
	printf("Weather Station App\n");
	
	// printf("Initializing ...\n");
	weatherDataInit();
	initCurrentConditionsDisplay();
	initStatisticsDisplay();

	// printf("Creating Thread ...\n");
	pthread_t weatherDataTaskID;
	pthread_create(&weatherDataTaskID, NULL, &weatherDataTask, NULL);

	pthread_t displayCurrentConditionsTaskID;
	pthread_create(&displayCurrentConditionsTaskID, NULL, &displayCurrentConditionsTask, NULL);

	pthread_t displayStatisticsTaskID;
	pthread_create(&displayStatisticsTaskID, NULL, &displayStatisticsTask, NULL);

	pthread_join(weatherDataTaskID, NULL);
	pthread_join(displayCurrentConditionsTaskID, NULL);
	pthread_join(displayStatisticsTaskID, NULL);

	return 0;
}
