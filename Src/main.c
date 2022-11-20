#include "../Inc/temp_functions.h"

int main(int argc, char **argv)
{
	struct sensorTemperature *dataTemperature = NULL;
	
	uint32_t countSensorMeasurements = 0;
	
	char nameDirr[100] = "Data/temperature_big.csv";
	char test[100];
	
	//dataTemperature = malloc(MAX_COUNT_YEAR_T * sizeof(struct sensorTemperature));
	//Выделение памяти под массив структур и проверка выделилась ли память
	if (!(dataTemperature = malloc(MAX_COUNT_YEAR_T * sizeof(struct sensorTemperature))))
	{
		printf("Error: can't allocate memory");
		exit(1);
	}
	
	addDataTemperature(dataTemperature, &countSensorMeasurements, nameDirr);
	
	if(strcmp(nameDirr, "Data/temperature_big.csv"))
		sortByDate(dataTemperature, countSensorMeasurements);
	
	printDataTemperature(dataTemperature, countSensorMeasurements);
	
	printf("Not ERROR");
	
	return 0;
}
