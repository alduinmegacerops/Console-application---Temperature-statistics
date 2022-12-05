#include "../Inc/temp_functions.h"

//функция печати имени таблицы статистики
void printNameTableStat()
{
	for(int i = 0; i < 102; i++)
		printf("%c", '=');
	printf("\n||%98c||", ' ');	
	printf("\n||%30c%s%30c||", ' ', "Temperature statistics from the sensor", ' ');
	printf("\n||%98c||\n", ' ');	
	
	for(int i = 0; i < 102; i++)
		printf("%c", '=');
}
//функция печати шапки таблицы статистики
void printHeadTableStat()
{
	printf("\n||%7c%s%6c|", ' ', "Month", ' ');
	printf("|%6c%s%6c|", ' ', "Middle Month", ' ');
	printf("|%6c%s%6c|", ' ', "Minimum Month", ' ');
	printf("|%6c%s%6c||\n", ' ', "Maximum Month", ' ');
	
	for(int i = 0; i < 102; i++)
		printf("%c", '=');
		
	printf("\n");
}
//функция печати статистики за месяц
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
//функция печати статистики за год
void printStatYear(float *yearStat)
{
	printf("\n||%98c||", ' ');
	printf("\n|| Temperature statistics for the year:");
	printf(" Middle Year = %6.2f", yearStat[0]);
	printf(" Minimum Year = %3.f", yearStat[1]);
	printf(" Maximum Year = %3.0f  ||\n", yearStat[2]);
	printf("||%98c||\n", ' ');
	
	for(int i = 0; i < 102; i++)
		printf("%c", '=');
}
//функция для печати статистики
void printStat(data *sensor, float (*monthStat)[4], float *yearStat, uint8_t monthNumber)	
{
	printNameTableStat();
	printHeadTableStat();
	
	if(monthNumber == 0)
		for(int i = 0; i < 12; i++)
			printStatMonth(i, monthStat);
	else
		printStatMonth(monthNumber - 1, monthStat);
		
	for(int i = 0; i < 102; i++)
		printf("%c", '=');
		
	printStatYear(yearStat);
}
