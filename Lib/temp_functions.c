#include "../Inc/temp_functions.h"

void addDataTemperature(struct sensorTemperature* dataTemperature)			//считывание и парсингср данных	
{
	int count = 0;
	
	FILE *in;
	
	in = fopen("Data/temperature_small.csv", "r");
	
	fscanf(in, "%d;%d;%d;%d;%d;%d", &dataTemperature->year, 
									&dataTemperature->month,
									&dataTemperature->day,
									&dataTemperature->hour,
									&dataTemperature->minute,
									&dataTemperature->temperature);
	
	fclose(in);
}

float middleTemperatureMonth(struct sensorTemperature* dataTemperature)		//среднемесячная температура
{
	
}

int minTemperatureMonth(struct sensorTemperature* dataTemperature)			//минимальная температура за месяц
{
	
}

int maxTemperatureMonth(struct sensorTemperature* dataTemperature)			//максимальная температура за месяц
{
	
}

float middleTemperatureYear(struct sensorTemperature* dataTemperature)		//среднегодовая температура
{
	
}

int minTemperatureYear(struct sensorTemperature* dataTemperature)			//минамальная температура за год
{
	
}

int maxTemperatureYear(struct sensorTemperature* dataTemperature)			//максимальная температура за год
{
	
}
void printDataTemperature(struct sensorTemperature* dataTemperature)		//считывание и парсингср данных	
{
	printf("%04d %02d %02d %02d %02d %3d",	dataTemperature->year,
											dataTemperature->month,
											dataTemperature->day,
											dataTemperature->hour,
											dataTemperature->minute,
											dataTemperature->temperature);
}
