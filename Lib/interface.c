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
uint64_t dateToInt(data *sensor, uint32_t i)
{
	return 	sensor -> dataTemperature[i].minute + 
			sensor -> dataTemperature[i].hour * 100 + 
			sensor -> dataTemperature[i].day * 10000 + 
			sensor -> dataTemperature[i].month * 1000000 + 
			sensor -> dataTemperature[i].year * 100000000;
}
//функция меняет местами i-й элемент с j-ым элементом
void swap(data *sensor, uint32_t i, uint32_t j)
{
	struct sensorTemperature temp;
	temp = sensor -> dataTemperature[i];
	sensor -> dataTemperature[i] = sensor -> dataTemperature[j];
	sensor -> dataTemperature[j] = temp;
}
//функция сортировки
void sortByDate(data *sensor, char *nameFile)
{
	if(strcmp(nameFile, "Data/temperature_big.csv") && strcmp(nameFile, "Data/temperature_big_t.csv"))
		for(int i = 0; i < sensor -> countSensorMeasurements; ++i)
			for (int j = i; j < sensor -> countSensorMeasurements; ++j)
				if(dateToInt(sensor, i) >= dateToInt(sensor, j))
					swap(sensor, i, j);
}
//функция для считывания и парсинга данных	
void addDataTemperature(data *sensor, char *nameFile)
{
	char buffer[21];
	uint32_t errorCount = 0;
	
	sensor -> dataTemperature = NULL;
	
	FILE *in;
	
	in = fopen(nameFile, "r");
	
	for(sensor -> countSensorMeasurements = 0; fscanf(in, "%21[^\n]", buffer) != -1; sensor -> countSensorMeasurements++)
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
		for(int i = 0; i < strlen(buffer); i++)
		{				
			if(buffer[i] == ';' || buffer[i] == '-' || buffer[i] == ' ' || buffer[i] == 0x0 || (buffer[i] >= '0' && buffer[i] <= '9'))
				flag = 0;
			else
			{
				flag = 1;
				errorCount++;
				errorData(sensor -> countSensorMeasurements + errorCount, errorCount);
				sensor -> countSensorMeasurements--;
				memset(buffer, 0, sizeof(buffer));
				break;
			}
		}
//парсим данные из буфера по полям структуры		
		if(flag == 0)
		{
			sensor -> dataTemperature = realloc(sensor -> dataTemperature, sizeof(struct sensorTemperature) * (sensor -> countSensorMeasurements + 1));
			
			sscanf(buffer, "%d;%d;%d;%d;%d;%d",	&sensor -> dataTemperature[sensor -> countSensorMeasurements].year, 
												&sensor -> dataTemperature[sensor -> countSensorMeasurements].month,
												&sensor -> dataTemperature[sensor -> countSensorMeasurements].day,
												&sensor -> dataTemperature[sensor -> countSensorMeasurements].hour,
												&sensor -> dataTemperature[sensor -> countSensorMeasurements].minute,
												&sensor -> dataTemperature[sensor -> countSensorMeasurements].temperature);

			memset(buffer, 0, sizeof(buffer));
		}
	}

	if(errorCount == 0)
		errorData(0, errorCount);
	
	fclose(in);
}
//функция для расчета среднемесячной температуры
void middleTemperatureMonth(data *sensor, float (*stat)[4])
{
	float sum[12] = {0}, counter[12] = {0};
	
	for(int i = 0; i < sensor -> countSensorMeasurements; i++)
	{
		sum[sensor -> dataTemperature[i].month - 1] += sensor -> dataTemperature[i].temperature;
		counter[sensor -> dataTemperature[i].month - 1]++;
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
void minTemperatureMonth(data *sensor, float (*stat)[4])
{
	int minMonth[12] = {0}, count = 0;
	
	for(int countMonth = 0; countMonth < 12; countMonth++)
	{
		minMonth[countMonth] = sensor -> dataTemperature[count].temperature;
		count++;
		while(sensor -> dataTemperature[count].month == countMonth + 1)
		{
			if(minMonth[countMonth] > sensor -> dataTemperature[count].temperature)
				minMonth[countMonth] = sensor -> dataTemperature[count].temperature;
			count++;
		}
	}
	
	for(int i = 0; i < 12; i++)
		stat[i][2] = minMonth[i];
}
//функция для нахождения максимальной температуры за месяц
void maxTemperatureMonth(data *sensor, float (*stat)[4])
{
	int maxMonth[12] = {0}, count = 0;
	
	for(int countMonth = 0; countMonth < 12; countMonth++)
	{
		maxMonth[countMonth] = sensor -> dataTemperature[count].temperature;
		count++;
		while(sensor -> dataTemperature[count].month == countMonth + 1)
		{
			if(maxMonth[countMonth] < sensor -> dataTemperature[count].temperature)
				maxMonth[countMonth] = sensor -> dataTemperature[count].temperature;
			count++;
		}
	}
	
	for(int i = 0; i < 12; i++)
		stat[i][3] = maxMonth[i];
}
//функция для расчета среднегодовой температуры
float middleTemperatureYear(data *sensor)
{
	float sumTemperatureYear = 0;
		
	for(int i = 0; i < sensor -> countSensorMeasurements; i++)
		sumTemperatureYear += sensor -> dataTemperature[i].temperature;
		
	return sumTemperatureYear / sensor -> countSensorMeasurements;
}
//функция для нахождения минимальной температуры за год
int minTemperatureYear(data *sensor)
{
	int minTempYear = sensor -> dataTemperature[0].temperature;
	
	for(int i = 1; i < sensor -> countSensorMeasurements; i++)
		if(minTempYear > sensor -> dataTemperature[i].temperature)
			minTempYear = sensor -> dataTemperature[i].temperature;
			
	return minTempYear;
}
//функция для нахождения максимальной температуры за год
int maxTemperatureYear(data *sensor)
{
	int maxTempYear = sensor -> dataTemperature[0].temperature;
	
	for(int i = 1; i < sensor -> countSensorMeasurements; i++)
		if(maxTempYear < sensor -> dataTemperature[i].temperature)
			maxTempYear = sensor -> dataTemperature[i].temperature;
			
	return maxTempYear;
}
//функция для печати счиатанных данных
void printDataTemperature(data *sensor)	
{
	printf("%d\n", sensor -> countSensorMeasurements);
	for(int i = 0; i < sensor -> countSensorMeasurements; i++)
	{	
		printf("%04d %02d %02d %02d %02d %3d\n",	sensor -> dataTemperature[i].year,
													sensor -> dataTemperature[i].month,
													sensor -> dataTemperature[i].day,
													sensor -> dataTemperature[i].hour,
													sensor -> dataTemperature[i].minute,
													sensor -> dataTemperature[i].temperature);
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
		
	printf("\n");
}
//Функция печати статистики за месяц
void printStatMonth(uint8_t number, float (*monthStat)[4])
{
	char months[12][4] = {{"JAN"}, {"FEB"}, {"MAR"}, {"APR"}, {"MAY"}, {"JUN"}, {"JUL"}, {"AUG"}, {"SEP"}, {"OCT"}, {"NOV"}, {"DEC"}}; 
	
	printf("||%8c%s%7c|", ' ', months[number], ' ');

	
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
		printf("\n|| For the year the data loss was %6.2f%%.", (float)(MAX_COUNT_YEAR_T - countMeasurements) / (float)MAX_COUNT_YEAR_T * 100);
		printf(" %6d error data. %6d no measurement.%16c||\n", countErr, MAX_COUNT_YEAR_T - countMeasurements - countErr, ' ');
	}
	else
	{
		printf("\n||%98c||", ' ');
		printf("\n|| For the year the data loss was %6.2f%%.", (float)(MAX_COUNT_YEAR_T - countMeasurements) / (float)MAX_COUNT_YEAR_T * 100);
		printf(" %6d error data. %6d no measurement.%16c||\n", countErr, MAX_COUNT_YEAR_T - countMeasurements - countErr, ' ');
	}

	for(int i = 0; i < 102; i++)
		printf("%c", '=');
		
	fclose(err);
}
//функция для печати статистики
void printStat(data *sensor, float (*monthStat)[4], float *yearStat, uint8_t monthNumber)	
{
	printNameTable();
	printHeadTable();
	
	if(monthNumber == 0)
		for(int i = 0; i < 12; i++)
			printStatMonth(i, monthStat);
	else
		printStatMonth(monthNumber - 1, monthStat);
		
	for(int i = 0; i < 102; i++)
		printf("%c", '=');
		
	printStatYear(yearStat);
	
	printError(sensor -> countSensorMeasurements);
}
