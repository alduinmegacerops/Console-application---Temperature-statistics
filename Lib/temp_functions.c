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
//функци перевода даты и временив в uint64_t
uint64_t dateToInt(struct sensorTemperature* dataTemperature)
{
	return dataTemperature -> minute + dataTemperature -> hour * 100 + dataTemperature -> day * 10000 + dataTemperature -> month * 1000000 + dataTemperature -> year * 100000000;
}
//функция меняет местами i-й элемент с j-ым элементом
void swap(struct sensorTemperature* dataTemperature, uint32_t i, uint32_t j)
{
	struct sensorTemperature temp;
	temp = dataTemperature[i];
	dataTemperature[i] = dataTemperature[j];
	dataTemperature[j] = temp;
}
//функция сортировки
void sortByDate(struct sensorTemperature* dataTemperature, uint32_t countMeasurements, char *nameFile)
{
	if(strcmp(nameFile, "Data/temperature_big.csv"))
		for(int i = 0; i < countMeasurements; ++i)
			for (int j = i; j < countMeasurements; ++j)
				if(dateToInt(dataTemperature + i) >= dateToInt(dataTemperature + j))
					swap(dataTemperature, i, j);
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
void middleTemperatureMonth(struct sensorTemperature* dataTemperature, uint32_t countMeasurements, float (*stat)[4])
{
	float sum[12] = {0}, counter[12] = {0};
	
	for(int i = 0; i < countMeasurements; i++)
	{
		switch((dataTemperature + i) -> month)
		{
			case 1:
				sum[0] += (dataTemperature + i) -> temperature;
				counter[0]++;
				break;
			
			case 2:
				sum[1] += (dataTemperature + i) -> temperature;
				counter[1]++;
				break;
			
			case 3:
				sum[2] += (dataTemperature + i) -> temperature;
				counter[2]++;
				break;
			
			case 4:
				sum[3] += (dataTemperature + i) -> temperature;
				counter[3]++;
				break;
			
			case 5:
				sum[4] += (dataTemperature + i) -> temperature;
				counter[4]++;
				break;
			
			case 6:
				sum[5] += (dataTemperature + i) -> temperature;
				counter[5]++;
				break;
				
			case 7:
				sum[6] += (dataTemperature + i) -> temperature;
				counter[6]++;
				break;
			
			case 8:
				sum[7] += (dataTemperature + i) -> temperature;
				counter[7]++;
				break;
			
			case 9:
				sum[8] += (dataTemperature + i) -> temperature;
				counter[8]++;
				break;
			
			case 10:
				sum[9] += (dataTemperature + i) -> temperature;
				counter[9]++;
				break;
			
			case 11:
				sum[10] += (dataTemperature + i) -> temperature;
				counter[10]++;
				break;
			
			case 12:
				sum[11] += (dataTemperature + i) -> temperature;
				counter[11]++;
				break;
			
			default:
				break;
		}
	}
	
	for(int i = 0; i < 12; i++)
	{
		if(counter[i] == 0)
			stat[i][0] = 1;
		else
			stat[i][1] = sum[i] / counter[i];
	}
}
//функция для нахождения минимальной температура за месяц
void minTemperatureMonth(struct sensorTemperature* dataTemperature, float (*stat)[4])
{
	int minMonth[12] = {0}, count = 0;
	
	for(int countMonth = 0; countMonth < 12; countMonth++)
	{
		minMonth[countMonth] = (dataTemperature + count) -> temperature;
		count++;
		while((dataTemperature + count) -> month == countMonth + 1)
		{
			if(minMonth[countMonth] > (dataTemperature + count) -> temperature)
				minMonth[countMonth] = (dataTemperature + count) -> temperature;
			count++;
		}
	}
	
	for(int i = 0; i < 12; i++)
		stat[i][2] = minMonth[i];
}
//функция для нахождения максимальной температура за месяц
void maxTemperatureMonth(struct sensorTemperature* dataTemperature, float (*stat)[4])
{
	int maxMonth[12] = {0}, count = 0;
	
	for(int countMonth = 0; countMonth < 12; countMonth++)
	{
		maxMonth[countMonth] = (dataTemperature + count) -> temperature;
		count++;
		while((dataTemperature + count) -> month == countMonth + 1)
		{
			if(maxMonth[countMonth] < (dataTemperature + count) -> temperature)
				maxMonth[countMonth] = (dataTemperature + count) -> temperature;
			count++;
		}
	}
	
	for(int i = 0; i < 12; i++)
		stat[i][3] = maxMonth[i];
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
