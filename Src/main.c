#include "../Inc/temp_functions.h"

int main(int argc, char **argv)
{
	struct sensorTemperature *dataTemperature = NULL;
	
	uint32_t countSensorMeasurements = 0;
	uint8_t numberMonth = 0;
	int key = 0;
	
	float statMonth[12][4] = {0};
	float statYear[3] = {0};
	
	char nameDirr[100] = "Data/temperature_medium.csv";
	
	//Выделение памяти под массив структур и проверка выделилась ли память
	if (!(dataTemperature = malloc(MAX_COUNT_YEAR_T * sizeof(struct sensorTemperature))))
	{
		printf("Error: can't allocate memory");
		exit(1);
	}
	
	/*while( (key = getopt(argc, argv, "hf:m::")) != -1)
	{
		switch(key)
		{
			case 'h':
			
			break;
			
			case 'f':
			
			break;
			
			case 'm':
			
			break;
			
			default:
			
			break;
		}
	}*/
	
	addDataTemperature(dataTemperature, &countSensorMeasurements, nameDirr);
	
	sortByDate(dataTemperature, countSensorMeasurements, nameDirr);
	
	middleTemperatureMonth(dataTemperature, countSensorMeasurements, statMonth);
	minTemperatureMonth(dataTemperature, statMonth);
	maxTemperatureMonth(dataTemperature, statMonth);
	
	statYear[0] = middleTemperatureYear(dataTemperature, countSensorMeasurements);
	statYear[1] = minTemperatureYear(dataTemperature, countSensorMeasurements);
	statYear[2] = maxTemperatureYear(dataTemperature, countSensorMeasurements);
	
	//printf("\n%6.2f %3.f %3.0f\n", statYear[0], statYear[1], statYear[2]);
		
	//printDataTemperature(dataTemperature, countSensorMeasurements);
	
	printStat(statMonth, statYear, countSensorMeasurements, numberMonth);
	
	//printf("Not ERROR");
	
	return 0;
}
