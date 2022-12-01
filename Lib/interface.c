#include "../Inc/temp_functions.h"

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
void printError(data *sensor)
{	
	printf("\n||%41c%s%41c||", ' ', "Statictics Error", ' ');
	printf("\n||%98c||", ' ');
	
	for(int i = 0; i < sensor -> errorCount; i++ )
		printf("\n|| Data file error in line %6d%67c||", sensor -> lineFileDataError[i], ' ');

	if(sensor -> errorCount == 0)
	{
		printf("\n|| Not Error Data%83c||", ' ');
		printf("\n||%98c||", ' ');
		printf("\n|| For the year the data loss was %6.2f%%.", (float)(MAX_COUNT_YEAR_T - sensor -> countSensorMeasurements) / (float)MAX_COUNT_YEAR_T * 100);
		printf(" %6d error data. %6d no measurement.%16c||\n", sensor -> errorCount, MAX_COUNT_YEAR_T - sensor -> countSensorMeasurements - sensor -> errorCount, ' ');
	}
	else
	{
		printf("\n||%98c||", ' ');
		printf("\n|| For the year the data loss was %6.2f%%.", (float)(MAX_COUNT_YEAR_T - sensor -> countSensorMeasurements) / (float)MAX_COUNT_YEAR_T * 100);
		printf(" %6d error data. %6d no measurement.%16c||\n", sensor -> errorCount, MAX_COUNT_YEAR_T - sensor -> countSensorMeasurements - sensor -> errorCount, ' ');
	}

	for(int i = 0; i < 102; i++)
		printf("%c", '=');
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
	
	printError(sensor);
}
