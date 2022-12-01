#ifndef _TEMP_FUNCTIONS_H

#define _TEMP_FUNCTIONS_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COUNT_YEAR_T 525600		//максимальное количество измерений датичка температуры за год
#define MAX_COUNT_MONTH_T 44640		//максимальное количество измерений датичка температуры за месяц

struct sensorTemperature		//структура для занчений с датчика
{
	uint16_t year;				//год
	uint8_t month;				//месяц
	uint8_t day;				//деннь
	uint8_t hour;				//часы
	uint8_t minute;				//минуты
	int temperature;			//температура
};

typedef struct
{
	struct sensorTemperature *dataTemperature;
	uint32_t countSensorMeasurements;
} data;

void addDataTemperature(data*, char*);					//считывание и парсинг данных

void sortByDate(data*, char*);							//сортровка по дате

void middleTemperatureMonth(data*, float (*)[]);		//среднемесячная температура

void minTemperatureMonth(data*, float (*)[]);			//минимальная температура за месяц

void maxTemperatureMonth(data*, float (*)[]);			//максимальная температура за месяц

float middleTemperatureYear(data*);						//среднегодовая температура

int minTemperatureYear(data*);							//минамальная температура за год

int maxTemperatureYear(data*);							//максимальная температура за год

void printDataTemperature(data*);						//печать счиатанных данных

void printStat(data*, float (*)[], float*, uint8_t);	//печать статистики

#endif
