#ifndef WEATHER_DATA_H
#define WEATHER_DATA_H

#include <stdbool.h>

typedef struct WeatherData
{
	float temperature;
	float humidity;	
} WeatherData;

typedef void (*weatherDataChanged) (void);

void weatherDataInit();
void weatherDataSet(float temperature, float humidity);
float weatherDataGetTemperature();
float weatherDataGetHumidity();
bool weatherDataRegisterObserver(weatherDataChanged observer);
bool weatherDataUnregisterObserver(weatherDataChanged observer);
void weatherDataNotifyObservers();
void weatherDataStateChanged();

#endif // WEATHER_DATA_H