#include "../Inc/temp_functions.h"

//функция для считывания и парсинга данных	
void addDataTemperature(struct sensorTemperature* dataTemperature, int *countSensorMeasurements)
{
	char buffer[21];
	int errorCount = 0;
	
	FILE *in;
	
	in = fopen("Data/temperature_small.csv", "r");
	
	for(*countSensorMeasurements; fscanf(in, "%21[^\n]s", buffer) != -1; (*countSensorMeasurements)++)
	{
		char tmp;
		uint8_t flag = 1;
		
		do
		{
			tmp = fgetc(in);
		}
		while(tmp != EOF && tmp != '\n');
		
		for(int i = 0; i < 21; i++)
		{
			if(buffer[i] == ';' || buffer[i] == '-' || buffer[i] == ' ' || buffer[i] == 0x0 || (buffer[i] >= '0' && buffer[i] <= '9'))
				flag = 0;
			else
			{
				flag = 1;
				memset(buffer,0,sizeof(buffer));
				break;
			}
		}
		
		if(flag == 0)
		{
			sscanf(buffer, "%d;%d;%d;%d;%d;%d",	&(dataTemperature + *countSensorMeasurements) -> year, 
												&(dataTemperature + *countSensorMeasurements) -> month,
												&(dataTemperature + *countSensorMeasurements) -> day,
												&(dataTemperature + *countSensorMeasurements) -> hour,
												&(dataTemperature + *countSensorMeasurements) -> minute,
												&(dataTemperature + *countSensorMeasurements) -> temperature);
			memset(buffer,0,sizeof(buffer));
		}
		else
		{
			printf("Data file error in line %d\n", *countSensorMeasurements + 1 + errorCount);
			errorCount++;
			(*countSensorMeasurements)--;
		}
	}
	
	fclose(in);
}

//функция для расчета среднемесячной температуры
float middleTemperatureMonth(struct sensorTemperature* dataTemperature)
{
	
}

//функция для нахождения минимальной температура за месяц
int minTemperatureMonth(struct sensorTemperature* dataTemperature)
{
	
}

//функция для нахождения максимальной температура за месяц
int maxTemperatureMonth(struct sensorTemperature* dataTemperature)
{
	
}

//функция для расчета среднегодовой температуры
float middleTemperatureYear(struct sensorTemperature* dataTemperature)
{
		
}

//функция для нахождения минимальной температура за год
int minTemperatureYear(struct sensorTemperature* dataTemperature)
{
	
}

//функция для нахождения максимальной температура за год
int maxTemperatureYear(struct sensorTemperature* dataTemperature)
{
	
}

//функция для нахождения минимальной температура за месяц
void printDataTemperature(struct sensorTemperature* dataTemperature, int countSensorMeasurements)	
{
	printf("%d\n", countSensorMeasurements);
	for(int i = 0; i < countSensorMeasurements; i++)
	{	
		printf("%04d %02d %02d %02d %02d %3d\n",	(dataTemperature + i) -> year,
													(dataTemperature + i) -> month,
													(dataTemperature + i) -> day,
													(dataTemperature + i) -> hour,
													(dataTemperature + i) -> minute,
													(dataTemperature + i) -> temperature);
	}
}
