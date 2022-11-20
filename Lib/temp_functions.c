#include "../Inc/temp_functions.h"

//Обработка ошибок
void errorData(uint32_t lineFileDataError, uint32_t errCount)
{
	FILE *err;
	
	if (errCount == 1)
		err = fopen("Error_Data", "w");
	else
		err = fopen("Error_Data", "a");
	
	fprintf(err, "Data file error in line %d\n", lineFileDataError);
	
	fclose(err);
}
//функция для считывания и парсинга данных	
void addDataTemperature(struct sensorTemperature* dataTemperature, uint32_t *countMeasurements, char *nameFile)
{
	char buffer[21];
	uint32_t errorCount = 1;
	
	FILE *in;
	
	in = fopen(nameFile, "r");
	
	for(*countMeasurements; fscanf(in, "%21[^\n]s", buffer) != -1; (*countMeasurements)++)
	{
		char tmp;
		uint8_t flag = 1;
//цикл пропускает оставшиеся символы до конца файла или строки (на случай, если строка была чересчур длинной
		do
		{
			tmp = fgetc(in);
		}
		while(tmp != EOF && tmp != '\n');
//проверка буффера на корректность данных	
		for(int i = 0; i < 21; i++)
		{
			if(buffer[i] == ';' || buffer[i] == '-' || buffer[i] == ' ' || buffer[i] == 0x0 || (buffer[i] >= '0' && buffer[i] <= '9'))
				flag = 0;
			else
			{
				flag = 1;
				errorData(*countMeasurements + errorCount, errorCount);
				errorCount++;
				(*countMeasurements)--;
				memset(buffer, 0, sizeof(buffer));
				break;
			}
		}
//парсим данные из буфера по полям структуры		
		if(flag == 0)
		{
			sscanf(buffer, "%d;%d;%d;%d;%d;%d",	&(dataTemperature + *countMeasurements) -> year, 
												&(dataTemperature + *countMeasurements) -> month,
												&(dataTemperature + *countMeasurements) -> day,
												&(dataTemperature + *countMeasurements) -> hour,
												&(dataTemperature + *countMeasurements) -> minute,
												&(dataTemperature + *countMeasurements) -> temperature);
			memset(buffer, 0, sizeof(buffer));
		}
	}
	
	fclose(in);
}
//функция для расчета среднемесячной температуры
float middleTemperatureMonth(struct sensorTemperature* dataTemperature, uint32_t countMeasurements)
{
	
}
//функция для нахождения минимальной температура за месяц
int minTemperatureMonth(struct sensorTemperature* dataTemperature, uint32_t countMeasurements)
{
	
}
//функция для нахождения максимальной температура за месяц
int maxTemperatureMonth(struct sensorTemperature* dataTemperature, uint32_t countMeasurements)
{
	
}
//функция для расчета среднегодовой температуры
float middleTemperatureYear(struct sensorTemperature* dataTemperature, uint32_t countMeasurements)
{
		
}
//функция для нахождения минимальной температура за год
int minTemperatureYear(struct sensorTemperature* dataTemperature, uint32_t countMeasurements)
{
	
}
//функция для нахождения максимальной температура за год
int maxTemperatureYear(struct sensorTemperature* dataTemperature, uint32_t countMeasurements)
{
	
}
//функция для печати счиатанных данных
void printDataTemperature(struct sensorTemperature* dataTemperature, uint32_t countMeasurements)	
{
	printf("%d\n", countMeasurements);
	for(int i = 0; i < countMeasurements; i++)
	{	
		printf("%04d %02d %02d %02d %02d %3d\n",	(dataTemperature + i) -> year,
													(dataTemperature + i) -> month,
													(dataTemperature + i) -> day,
													(dataTemperature + i) -> hour,
													(dataTemperature + i) -> minute,
													(dataTemperature + i) -> temperature);
	}
}
//функция для печати статистики
void printStat(struct sensorTemperature* dataTemperature)	
{
	
}
