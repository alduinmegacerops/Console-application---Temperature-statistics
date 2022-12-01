#include "../Inc/main.h"

int main(int argc, char **argv)
{
	data sensor;
	
	float statMonth[12][4] = {0};
	float statYear[3] = {0};
	
	char inNameFile[100];
	char inNumberMonth[3];
	
	int key = 0;
	
	uint8_t numberMonth = 0;
	
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
				strcpy(inNameFile, optarg);
			break;
			
			case 'm':
				strcpy(inNumberMonth, optarg);
				numberMonth = atoi(inNumberMonth);
			break;
			
			case '?':
				printf("Unknown argument: %s Try -h for help\n", argv[optind-1]);
				return 2;
			break;
		}
	}
	
	addDataTemperature(&sensor, inNameFile);

	sortByDate(&sensor, inNameFile);

	middleTemperatureMonth(&sensor, statMonth);
	minTemperatureMonth(&sensor, statMonth);
	maxTemperatureMonth(&sensor, statMonth);
	
	statYear[0] = middleTemperatureYear(&sensor);
	statYear[1] = minTemperatureYear(&sensor);
	statYear[2] = maxTemperatureYear(&sensor);
		
	//printDataTemperature(&sensor);

	printStat(&sensor, statMonth, statYear, numberMonth);
	
	free(sensor.dataTemperature);
	free(sensor.lineFileDataError);
	
	return 0;
}
