#include "../Inc/temp_functions.h"

//Обработка ошибок
void errorData(uint32_t lineFileDataError, uint32_t errCount)
{
	FILE *err;
	
	switch(errCount)
	{
		case 0:
			err = fopen("Error_Data", "w");
		break;
		
		case 1:
			err = fopen("Error_Data", "w");
			fprintf(err, "%d", lineFileDataError);
		break;
		
		default:
			err = fopen("Error_Data", "a");
			fprintf(err, "\n%d", lineFileDataError);
		break;
	}
	
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
	if(strcmp(nameFile, "Data/temperature_big.csv") && strcmp(nameFile, "Data/temperature_big_t.csv"))
		for(int i = 0; i < countMeasurements; ++i)
			for (int j = i; j < countMeasurements; ++j)
				if(dateToInt(dataTemperature + i) >= dateToInt(dataTemperature + j))
					swap(dataTemperature, i, j);
}
//функция для считывания и парсинга данных	
void addDataTemperature(struct sensorTemperature* dataTemperature, uint32_t *countMeasurements, char *nameFile)
{
	char buffer[21];
	uint32_t errorCount = 0;
	
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
				errorCount++;
				errorData(*countMeasurements + errorCount, errorCount);
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
	
	if(errorCount == 0)
		errorData(0, errorCount);
	
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
//функция для нахождения минимальной температуры за месяц
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
//функция для нахождения максимальной температуры за месяц
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
	float sumTemperatureYear = 0;
		
	for(int i = 0; i < countMeasurements; i++)
		sumTemperatureYear += (dataTemperature + i) -> temperature;
		
	return sumTemperatureYear / countMeasurements;
}
//функция для нахождения минимальной температуры за год
int minTemperatureYear(struct sensorTemperature* dataTemperature, uint32_t countMeasurements)
{
	int minTempYear = dataTemperature -> temperature;
	
	for(int i = 1; i < countMeasurements; i++)
		if(minTempYear > (dataTemperature + i) -> temperature)
			minTempYear = (dataTemperature + i) -> temperature;
			
	return minTempYear;
}
//функция для нахождения максимальной температуры за год
int maxTemperatureYear(struct sensorTemperature* dataTemperature, uint32_t countMeasurements)
{
	int maxTempYear = dataTemperature -> temperature;
	
	for(int i = 1; i < countMeasurements; i++)
		if(maxTempYear < (dataTemperature + i) -> temperature)
			maxTempYear = (dataTemperature + i) -> temperature;
			
	return maxTempYear;
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
//Функция печати имени таблицы
void printNameTable()
{
	for(int i = 0; i < 102; i++)
		printf("%c", '=');
		
	printf("\n||%30c%s%30c||\n", ' ', "Temperature statistics from the sensor", ' ');
	
	for(int i = 0; i < 102; i++)
		printf("%c", '=');
}
//Функция печати шапки таблицы
void printHeadTable()
{
	printf("\n||%7c%s%6c|", ' ', "Month", ' ');
	printf("|%6c%s%6c|", ' ', "Middle Month", ' ');
	printf("|%6c%s%6c|", ' ', "Minimum Month", ' ');
	printf("|%6c%s%6c||\n", ' ', "Maximum Month", ' ');
	
	for(int i = 0; i < 102; i++)
		printf("%c", '=');
}
//Функция печати статистики за месяц
void printStatMonth(uint8_t number, float (*monthStat)[4])
{
	switch(number)
	{
		case 0:
			printf("\n||%8c%s%7c|", ' ', "JAN", ' ');
		break;
		
		case 1:
			printf("||%8c%s%7c|", ' ', "FEB", ' ');
		break;
		
		case 2:
			printf("||%8c%s%7c|", ' ', "MAR", ' ');
		break;
		
		case 3:
			printf("||%8c%s%7c|", ' ', "APR", ' ');
		break;
		
		case 4:
			printf("||%8c%s%7c|", ' ', "MAY", ' ');
		break;
		
		case 5:
			printf("||%8c%s%7c|", ' ', "JUN", ' ');
		break;
		
		case 6:
			printf("||%8c%s%7c|", ' ', "JUL", ' ');
		break;
		
		case 7:
			printf("||%8c%s%7c|", ' ', "AUG", ' ');
		break;
		
		case 8:
			printf("||%8c%s%7c|", ' ', "SEP", ' ');
		break;
		
		case 9:
			printf("||%8c%s%7c|", ' ', "OCT", ' ');
		break;
		
		case 10:
			printf("||%8c%s%7c|", ' ', "NOV", ' ');
		break;
		
		case 11:
			printf("||%8c%s%7c|", ' ', "DEC", ' ');
		break;
	}
	
	if(monthStat[number][0] == 0)
	{
		printf("|%9c%6.2f%9c|", ' ', monthStat[number][1], ' ');
		printf("|%11c%3.0f%11c|", ' ', monthStat[number][2], ' ');
		printf("|%11c%3.0f%11c||\n", ' ', monthStat[number][3], ' ');
	}
	else
	{
		printf("|%8c%s%8c|", ' ', "Not data", ' ');
		printf("|%9c%s%8c|", ' ', "Not data", ' ');
		printf("|%9c%s%8c||\n", ' ', "Not data", ' ');
	}
}
//Функция печати статистики за год
void printStatYear(float *yearStat)
{
	printf("\n|| Temperature statistics for the year:");
	printf(" Middle Year = %6.2f", yearStat[0]);
	printf(" Minimum Year = %3.f", yearStat[1]);
	printf(" Maximum Year = %3.0f  ||\n", yearStat[2]);
	
	for(int i = 0; i < 102; i++)
		printf("%c", '=');
}
//Функция печати ошибок в данных
void printError(uint32_t countMeasurements)
{
	int countErr = 0, temp = 0;
	
	FILE *err;
	err = fopen("Error_Data", "r");	
	
	printf("\n||%41c%s%41c||", ' ', "Statictics Error", ' ');
	printf("\n||%98c||", ' ');
	
	while(!feof(err))
	{
		fscanf(err, "%d", &temp);

		if(temp != 0)
		{
			printf("\n|| Data file error in line %6d%67c||", temp, ' ');
			countErr++;
		}
	}

	if(countErr == 0)
	{
		printf("\n|| Not Error Data%83c||", ' ');
		printf("\n||%98c||", ' ');
		printf("\n|| For the year the data loss was %5.2f%%.", (float)(MAX_COUNT_YEAR_T - countMeasurements) / (float)MAX_COUNT_YEAR_T * 100);
		printf(" %6d error data. %6d no measurement.%17c||\n", countErr, MAX_COUNT_YEAR_T - countMeasurements - countErr, ' ');
	}
	else
	{
		printf("\n||%98c||", ' ');
		printf("\n|| For the year the data loss was %5.2f%%.", (float)(MAX_COUNT_YEAR_T - countMeasurements) / (float)MAX_COUNT_YEAR_T * 100);
		printf(" %6d error data. %6d no measurement.%17c||\n", countErr, MAX_COUNT_YEAR_T - countMeasurements - countErr, ' ');
	}

	for(int i = 0; i < 102; i++)
		printf("%c", '=');
		
	fclose(err);
}
//функция для печати статистики
void printStat(float (*monthStat)[4], float *yearStat, uint32_t countMeasurements, uint8_t monthNumber)	
{
	printNameTable();
	printHeadTable();
	
	if(monthNumber == 0)
		for(int i = 0; i < 12; i++)
			printStatMonth(i, monthStat);
	else
		printStatMonth(monthNumber, monthStat);
		
	for(int i = 0; i < 102; i++)
		printf("%c", '=');
		
	printStatYear(yearStat);
	
	printError(countMeasurements);
}	
