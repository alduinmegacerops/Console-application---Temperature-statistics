#include "../Inc/temp_functions.h"

int main(int argc, char **argv)
{
	struct sensorTemperature *dataTemperature = NULL;
	
	uint32_t countSensorMeasurements = 0;
	uint8_t numberMonth = 4;
	
	float statMonth[12][4] = {0};
	
	char nameDirr[100] = "Data/temperature_medium.csv";
	
	//Выделение памяти под массив структур и проверка выделилась ли память
	if (!(dataTemperature = malloc(MAX_COUNT_YEAR_T * sizeof(struct sensorTemperature))))
	{
		printf("Error: can't allocate memory");
		exit(1);
	}
	
	addDataTemperature(dataTemperature, &countSensorMeasurements, nameDirr);
	
	sortByDate(dataTemperature, countSensorMeasurements, nameDirr);
	
	middleTemperatureMonth(dataTemperature, countSensorMeasurements, statMonth);
	minTemperatureMonth(dataTemperature, statMonth);
	maxTemperatureMonth(dataTemperature, statMonth);
	
	for(int i = 0; i < 12; i++)
	{
		if(statMonth[i][0] == 0)
			printf("%05.2f %3.0f %3.0f\n", statMonth[i][1], statMonth[i][2], statMonth[i][3]);
		else
			printf("Not temperature in %02d month\n", i + 1);
	}
	
	printDataTemperature(dataTemperature, countSensorMeasurements);
	
	printf("Not ERROR");
	
	return 0;
}
