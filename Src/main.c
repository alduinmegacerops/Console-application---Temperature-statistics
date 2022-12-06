#include "../Inc/main.h"

int main(int argc, char **argv)
{
	//структура для хранения данных по датчику
	data sensor;
	//массивы для хранения статистики
	float statMonth[12][4] = {0};
	float statYear[3] = {0};
	//строки для входных данных с ключей
	char inNameFile[100];
	char inNumberMonth[3];
	char inAddDataLine[21];
	char inDelDataLine[21];
	char inDateRange[34];
	//переменная для обработки ключей
	int key = 0;
	//перепенная для номера месяца
	uint8_t numberMonth = 0;
	//инициализация строк для входных данных с ключей
	memset(inNameFile, 0, sizeof(inNameFile));
	memset(inNumberMonth, 0, sizeof(inNumberMonth));
	memset(inAddDataLine, 0, sizeof(inAddDataLine));
	memset(inDelDataLine, 0, sizeof(inDelDataLine));
	memset(inDateRange, 0, sizeof(inDateRange));
	//проверяем что аргументы есть
	if(argc == 1)
	{
		printf("\nNot argument. Try -h for help.\n");
		return 1;
	}
	//обрабатываем ключи
	while((key = getopt(argc, argv, "hba:d:f:m:p:")) != -1)
	{
		switch(key)
		{
			case 'a':
				strcpy(inAddDataLine, optarg);
			break;
			
			case 'b':
				if(strlen(inNameFile) == 0)
					printf("\nThe <filename.csv> file directory is not set or key <b> specified before key <f> .\n");
				else
					backup(inNameFile);
			break;
			
			case 'd':
				strcpy(inDelDataLine, optarg);
			break;
			
			case 'f':
				strcpy(inNameFile, optarg);
			break;
			
			case 'h':
				printf("\n-h - List of keys that handles the given application and their purpose.\n\n");
				printf("-a - <year>:<month>:<day>:<hour>:<minute>:<temperature> - adding new data.\n");
				printf("%5cExample: 2021:1:2:3:4:-10 or 2021:01:02:03:04:-10\n\n", ' ');
				printf("-b - Creates a backup copy <filename_backup.csv> of the file <filename.csv> in the same directory.\n\n");
				printf("-d - <year>:<month>:<day>:<hour>:<minute>:<temperature> - delete data.\n");
				printf("%5cExample: 2021:1:2:3:4:-10 or 2021:01:02:03:04:-10\n\n", ' ');
				printf("-f - <filename.csv> - directory input csv file to process.\n\n");
				printf("-m - <number month> - if this key is given, then it is displayed only statistics for the specified month.\n\n");
				printf("-p - <year_begin>:<month_begin>:<day_begin>:<hour_begin>:<minute_begin>-<year_end>:<month_end>:<day_end>:<hour_end>:<minute_end> -\n");
				printf("%5crange date for print. Example: 2021:1:2:3:4-2021:5:6:7:8 or 2021:01:02:03:04-2021:05:06:07:08\n", ' ');
				return 3;
			break;
			
			case 'm':
				strcpy(inNumberMonth, optarg);
				numberMonth = atoi(inNumberMonth);
			break;
			
			case 'p':
				strcpy(inDateRange, optarg);
			break;
			
			case '?':
				printf("\nUnknown: %s. Try -h for help.\n", argv[optind-1]);
				return 2;
			break;
		}
	}
	//обрабатываем файл и заполняем структуру данных
	addDataTemperature(&sensor, inNameFile);
	//добавляем и удаляем данные если были заданы соответствующие ключи
	addData(&sensor, inAddDataLine, inNameFile);
	delData(&sensor, inDelDataLine, inNameFile);
	//сортируем получившуюся структуру данных
	sortByDate(&sensor, inNameFile);
	//считаем статистику по месяцам
	middleTemperatureMonth(&sensor, statMonth);
	minTemperatureMonth(&sensor, statMonth);
	maxTemperatureMonth(&sensor, statMonth);
	//считаем статистику за год
	statYear[0] = middleTemperatureYear(&sensor);
	statYear[1] = minTemperatureYear(&sensor);
	statYear[2] = maxTemperatureYear(&sensor);
	//печатаем данные за указанный диапазон если задан ключ -p
	printDataTemperature(&sensor, inDateRange);
	//выводим статистику
	printStat(&sensor, statMonth, statYear, numberMonth);
	//Печатаем статистику по ошибкам
	printError(&sensor);
	//освобождаем память
	free(sensor.dataTemperature);
	free(sensor.lineFileDataError);
	free(sensor.dataError);
	
	return 0;
}
