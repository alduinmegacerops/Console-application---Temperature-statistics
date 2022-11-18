#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COUNT_YEAR_T 525600		//максимальное количество измерений датичка температуры за год
#define MAX_COUNT_MONTH_T 44640		//максимальное количество измерений датичка температуры за месяц

struct sensorTemperature		//структура для занчений с датчика
{
	uint16_t year;				//год
	uint8_t month;			//месяц
	uint8_t day;				//деннь
	uint8_t hour;				//часы
	uint8_t minute;				//минуты
	int temperature;			//температура
};

void addDataTemperature(struct sensorTemperature*, int*);			//считывание и парсинг данных	

float middleTemperatureMonth(struct sensorTemperature*);	//среднемесячная температура

int minTemperatureMonth(struct sensorTemperature*);			//минимальная температура за месяц

int maxTemperatureMonth(struct sensorTemperature*);			//максимальная температура за месяц

float middleTemperatureYear(struct sensorTemperature*);		//среднегодовая температура

int minTemperatureYear(struct sensorTemperature*);			//минамальная температура за год

int maxTemperatureYear(struct sensorTemperature*);			//максимальная температура за год

void printDataTemperature(struct sensorTemperature*, int);			//печать
