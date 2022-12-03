#include "../Inc/main.h"

int main(int argc, char **argv)
{
	data sensor;
	
	float statMonth[12][4] = {0};
	float statYear[3] = {0};
	
	char inNameFile[100];
	char inNumberMonth[3];
	char inAddDataLine[21];
	char inDelDataLine[21];
	
	int key = 0;
	
	uint8_t numberMonth = 0;
	
	memset(inAddDataLine, 0, sizeof(inAddDataLine));
	memset(inDelDataLine, 0, sizeof(inDelDataLine));
	
	if(argc == 1)
	{
		printf("Not argument. Try -h for help.\n");
		return 1;
	}
	
	while((key = getopt(argc, argv, "ha:d:f:m:")) != -1)
	{
		switch(key)
		{
			case 'a':
				if(checkDataIn(optarg) == 0)
				{
					printf("The data for adding data is not set correctly.");
					printf("\nCheck if the date and temperature are entered correctly.");
					printf("\nTry -h for help.");
					return 4;
				}
				else
					strcpy(inAddDataLine, optarg);
			break;
			
			case 'd':
				if(checkDataIn(optarg) == 0)
				{
					printf("The data for adding data is not set correctly.");
					printf("\nCheck if the date and temperature are entered correctly.");
					printf("\nTry -h for help.");
					return 5;
				}
				else
					strcpy(inDelDataLine, optarg);
			break;
			
			case 'f':
				strcpy(inNameFile, optarg);
			break;
			
			case 'h':
				printf("\n-h - List of keys that handles the given application and their purpose.\n\n");
				printf("-a - <year>;<month>;<day>;<hour>;<minute>;<temperature> - adding new data.\n");
				printf("%5cExample of input data: 2021;1;2;3;4;-10 or 2021;01;02;03;04;-10\n\n", ' ');
				printf("-d - <year>;<month>;<day>;<hour>;<minute>;<temperature> - delete data.\n");
				printf("%5cExample: 2021;1;2;3;4;-10 or 2021;01;02;03;04;-10\n\n", ' ');
				printf("-f - <filename.csv> - directory input csv file to process.\n\n");
				printf("-m - <number month> - if this key is given, then it is displayed only statistics for the specified month.\n");
				return 3;
			break;
			
			case 'm':
				strcpy(inNumberMonth, optarg);
				numberMonth = atoi(inNumberMonth);
			break;
			
			case '?':
				printf("Unknown argument: %s. Try -h for help.\n", argv[optind-1]);
				return 2;
			break;
		}
	}
	
	addDataTemperature(&sensor, inNameFile);
	
	sortByDate(&sensor, inNameFile);

	addData(&sensor, inAddDataLine, inNameFile);
	delData(&sensor, inDelDataLine, inNameFile);

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
