#ifndef _TEMP_FUNCTIONS_H

#define _TEMP_FUNCTIONS_H

#include "../Inc/main.h"

#define MAX_COUNT_YEAR_T 525600							//максимальное количество измерений датичка температуры за год
#define MAX_COUNT_MONTH_T 44640							//максимальное количество измерений датичка температуры за месяц

struct sensorTemperature								//структура для занчений с датчика
{
	uint16_t year;										//год
	uint8_t month;										//месяц
	uint8_t day;										//деннь
	uint8_t hour;										//часы
	uint8_t minute;										//минуты
	int temperature;									//температура
};

typedef struct
{
	struct sensorTemperature *dataTemperature;			//структура для хранения валидных данных
	uint32_t countSensorMeasurements;					//количество валидных измерений
	uint32_t errorCount;								//количество не валидных измерений
	uint32_t *lineFileDataError;						//массив где хранятся номера линий файла где битые данные
	//char *dataError[21];								//хранилище битых данных
} data;

void addDataTemperature(data*, char*);					//считывание и парсинг данных

uint64_t dateToInt(data*, uint32_t);					//функция перевода даты и временив в uint64_t

void swap(data*, uint32_t, uint32_t);					//функция меняет местами i-й элемент с j-ым элементом

void sortByDate(data*, char*);							//функция сортировки пузырьком

void middleTemperatureMonth(data*, float (*)[]);		//среднемесячная температура

void minTemperatureMonth(data*, float (*)[]);			//минимальная температура за месяц

void maxTemperatureMonth(data*, float (*)[]);			//максимальная температура за месяц

float middleTemperatureYear(data*);						//среднегодовая температура

int minTemperatureYear(data*);							//минамальная температура за год

int maxTemperatureYear(data*);							//максимальная температура за год

void printDataTemperature(data*);						//печать счиатанных данных

void printNameTable();									//функция печати имени таблицы

void printHeadTable();									//функция печати шапки таблицы

void printStatMonth(uint8_t, float (*)[]);				//функция печати статистики за месяц

void printStatYear(float*);								//функция печати статистики за год

void printError(data*);									//функция печати ошибок в данных

void printStat(data*, float (*)[], float*, uint8_t);	//печать статистики

uint8_t checkDataIn(char*);								//функция проверки данных введенных по сле ключа -a и -d

void addData(data*, char*, char*);						//функция добавления данных введеных с ключа -a

//void delData(data*, char*, char*);						//функция удаления данных введеных с ключа -d

#endif
