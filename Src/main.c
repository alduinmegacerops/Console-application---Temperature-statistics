#include "../Inc/main.h"
#include "../Inc/temp_functions.h"

int main(int argc, char **argv)
{
	data sensor;
	
	int key = 0;
	
	uint8_t numberMonth = 0;
	
	float statMonth[12][4] = {0};
	float statYear[3] = {0};
	
	char nameDirr[100];
	char numberM[10];

	
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
	
	addDataTemperature(&sensor, nameDirr);

	sortByDate(&sensor, nameDirr);

	middleTemperatureMonth(&sensor, statMonth);
	minTemperatureMonth(&sensor, statMonth);
	maxTemperatureMonth(&sensor, statMonth);
	
	statYear[0] = middleTemperatureYear(&sensor);
	statYear[1] = minTemperatureYear(&sensor);
	statYear[2] = maxTemperatureYear(&sensor);
		
	//printDataTemperature(&sensor);
	
	printStat(&sensor, statMonth, statYear, numberMonth);
	
	//free(dataTemperature);
	
	return 0;
}
