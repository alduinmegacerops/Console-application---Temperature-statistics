#include "../Inc/temp_functions.h"

//функция печати ошибок в данных
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
	
	printf("\n");
}
