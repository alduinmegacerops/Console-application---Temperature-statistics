#include "../Inc/temp_functions.h"

int main(int argc, char **argv)
{
	struct sensorTemperature *dataTemperature;
	
	uint32_t countSensorMeasurements = 0;
	int key = 0;
	uint8_t numberMonth = 0;
	
	float statMonth[12][4] = {0};
	float statYear[3] = {0};
	
	char nameDirr[100];
	char numberM[10];
	
	//Выделение памяти под массив структур
	//dataTemperature = malloc(sizeof(struct sensorTemperature));
	
	dataTemperature = NULL;
	
	if(argc == 1)
	{
		printf("Not argument. Try -h for help\n");
		return 1;
	}
	
	while((key = getopt(argc, argv, "hf:m:")) != -1)
	{
		switch(key)
		{
			case 'h':
				printf("-h - List of keys that handles the given application and their purpose.\n");
				printf("-f <filename.csv> - directory input csv file to process.\n");
				printf("-m <number month> - if this key is given, then it is displayed only statistics for the specified month.\n");
				return 3;
			break;
			
			case 'f':
				strcpy(nameDirr, optarg);
			break;
			
			case 'm':
				strcpy(numberM, optarg);
				numberMonth = atoi(numberM);
			break;
			
			case '?':
				printf("Unknown argument: %s Try -h for help\n", argv[optind-1]);
				return 2;
			break;
		}
	}
	
	addDataTemperature(dataTemperature, &countSensorMeasurements, nameDirr);
	printf("1");
	printf("%d", dataTemperature->year);
	sortByDate(dataTemperature, countSensorMeasurements, nameDirr);
	printf("2 ");
	middleTemperatureMonth(dataTemperature, countSensorMeasurements, statMonth);
	minTemperatureMonth(dataTemperature, statMonth);
	maxTemperatureMonth(dataTemperature, statMonth);
	
	statYear[0] = middleTemperatureYear(dataTemperature, countSensorMeasurements);
	statYear[1] = minTemperatureYear(dataTemperature, countSensorMeasurements);
	statYear[2] = maxTemperatureYear(dataTemperature, countSensorMeasurements);
		
	//printDataTemperature(dataTemperature, countSensorMeasurements);
	
	printStat(statMonth, statYear, countSensorMeasurements, numberMonth);
	
	free(dataTemperature);
	
	return 0;
}
