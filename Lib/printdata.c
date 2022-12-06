#include "../Inc/temp_functions.h"

//функция проверки диапазона дат введенных после ключа -p
uint8_t checkDateRangeIn(char *strCheck)
{
	//флаговые переменные
	uint8_t tempCount = 0, flag = 0, flagDate = 0;
	//строки для начальной даты и конечной
	char *checkBeginDate, *checkEndDate;
	//делаем промежуточную строка чтобы главная строка не поменялась 
	char checkDateRange[34];
	strcpy(checkDateRange, strCheck);
	//объявляем буфферную структуру и выделяем память под буфферную структуру
	struct sensorTemperature *checkBuffer;
	checkBuffer = malloc(sizeof(struct sensorTemperature) * 2);
	//считаем разделители
	for(int i = 0; i < strlen(checkDateRange); i++)
	{
		if(checkDateRange[i] == ':' && checkDateRange[strlen(checkDateRange) - 1] != ':')
			tempCount++;
		if(checkDateRange[i] == '-' && i == 16)
			flag = 1;
	}
	//проверка корректность записи разделителей диапазона	
	if(tempCount == 8 && flag == 1)
	{
		//делим строку на 2 строки начальная дата и конечнаяя дата
		checkBeginDate = strtok(checkDateRange, "-");
		checkEndDate = strtok(NULL, "-");
		//вписываем в буффер дату начало
		sscanf(checkBeginDate, "%d:%d:%d:%d:%d",	&checkBuffer -> year,
													&checkBuffer -> month,
													&checkBuffer -> day,
													&checkBuffer -> hour,
													&checkBuffer -> minute);
		//вписывем в буффер дату конец
		sscanf(checkEndDate, "%d:%d:%d:%d:%d",	&(checkBuffer + 1) -> year,
												&(checkBuffer + 1) -> month,
												&(checkBuffer + 1) -> day,
												&(checkBuffer + 1) -> hour,
												&(checkBuffer + 1) -> minute);
		//проверяем что начальная дата меньше конечной даты
		if(dateToInt(checkBuffer, 0) <= dateToInt(checkBuffer, 1))
		{
			//проверка на корректность введенного месяца
			if(checkBuffer -> month > 0 && checkBuffer -> month < 13 && (checkBuffer + 1) -> month > 0 && (checkBuffer + 1) -> month < 13)
			{
				for(int i = 0; i < 2; i++)
				{
					//проверка высокосного года	начальной даты
					if((checkBuffer + i) -> month  == 2 && (checkBuffer + i) -> year % 4 == 0 )
					{
						//проверка на корректность введенных дня, часа, минуты
						if((checkBuffer + i) -> day > 0 && (checkBuffer + i) -> day < 30 && (checkBuffer + i) -> hour >= 0 && (checkBuffer + i) -> hour < 24 && (checkBuffer + i) -> minute >= 0 && (checkBuffer + i) -> minute < 60)
							flagDate++;
					}
					//проверка не высокосного года
					else if((checkBuffer + i) -> month == 2 && (checkBuffer + i) -> year % 4 != 0)
					{
						//проверка на корректность введенных дня, часа, минуты
						if((checkBuffer + i) -> day > 0 && (checkBuffer + i) -> day < 29 && (checkBuffer + i) -> hour >= 0 && (checkBuffer + i) -> hour < 24 && (checkBuffer + i) -> minute >= 0 && (checkBuffer + i) -> minute < 60)
							flagDate++;
					}
					//проверка на 31 день в месяце
					else if((checkBuffer + i) -> month == 1 || (checkBuffer + i) -> month == 3 || (checkBuffer + i) -> month == 5 || (checkBuffer + i) -> month == 7 || (checkBuffer + i) -> month == 8 || (checkBuffer + i) -> month == 10 || (checkBuffer + i) -> month == 11)
					{
						//проверка на корректность введенных дня, часа, минуты
						if((checkBuffer + i) -> day > 0 && (checkBuffer + i) -> day < 32 && (checkBuffer + i) -> hour >= 0 && (checkBuffer + i) -> hour < 24 && (checkBuffer + i) -> minute >= 0 && (checkBuffer + i) -> minute < 60)
							flagDate++;
					}
					//проверка на 30 дней в месяце
					else if((checkBuffer + i) -> month == 4 || (checkBuffer + i) -> month == 6 || (checkBuffer + i) -> month == 9 || (checkBuffer + i) -> month == 11)
					{
						//Проверка на корректность введенных дня, часа, минуты
						if((checkBuffer + i) -> day > 0 && (checkBuffer + i) -> day < 31 && (checkBuffer + i) -> hour >= 0 && (checkBuffer + i) -> hour < 24 && (checkBuffer + i) -> minute >= 0 && (checkBuffer + i) -> minute < 60)
							flagDate++;
					}
				}
				//проверка корректности дат
				if(flagDate == 2)
				{
					return 1;
				}
				else
				{
					free(checkBuffer);
					return 0;
				}
			}
			else
			{
				free(checkBuffer);
				return 0;
			}
		}
		else
		{
			free(checkBuffer);
			return 0;
		}
	}
	else
	{
		free(checkBuffer);
		return 0;
	}
}
//функция печати имени таблицы данных
void printNameTableData(char *beginDate, char *endDate)
{
	for(int i = 0; i < 102; i++)
		printf("%c", '=');
				
	printf("\n||%19c%s %s-%s%20c||\n", ' ', "Data Temperature in range", beginDate, endDate, ' ');
	printf("||%98c||\n", ' ');
}

//функция для печати данныз за период указанный в диапазоне
void printDataTemperature(data *sensor, char *rangeDate)	
{
	if(strlen(rangeDate) > 1)
	{
		if(checkDateRangeIn(rangeDate) == 1)
		{
			//флаговая переменная
			uint8_t flag = 0;
			//строки для начальной даты и конечной
			char *beginDate, *endDate;
			//делим строку на 2 строки начальная дата и конечнаяя дата
			beginDate = strtok(rangeDate, "-");
			endDate = strtok(NULL, "-");
			//объявляем буфферную структуру и выделяем память под буффер
			struct sensorTemperature *buffer;
			buffer = malloc(sizeof(struct sensorTemperature) * 2);
			//вписываем в буффер дату начало
			sscanf(beginDate, "%d:%d:%d:%d:%d",	&buffer -> year,
												&buffer -> month,
												&buffer -> day,
												&buffer -> hour,
												&buffer -> minute);
			//вписывем в буффер дату конец
			sscanf(endDate, "%d:%d:%d:%d:%d",	&(buffer + 1) -> year,
												&(buffer + 1) -> month,
												&(buffer + 1) -> day,
												&(buffer + 1) -> hour,
												&(buffer + 1) -> minute);
			//печатаем имя таблицы данных
			printNameTableData(beginDate, endDate);
			//печать данных
			for(int i = 0; i < sensor -> countSensorMeasurements; i++)
			{	
				while(dateToInt(buffer, 0) <= dateToInt(sensor -> dataTemperature, i) && dateToInt(buffer, 1) >= dateToInt(sensor -> dataTemperature, i))
				{
					flag = 1;
					
					printf("|| %4d-", sensor -> dataTemperature[i].year);
					printf("%02d-",sensor -> dataTemperature[i].month);
					printf("%02d ",sensor -> dataTemperature[i].day);
					printf("%02d:",sensor -> dataTemperature[i].hour);
					printf("%02d", sensor -> dataTemperature[i].minute);
					printf(" T=%4d", sensor -> dataTemperature[i].temperature);
					printf("%74c||\n", ' ');
					
					i++;
				}
			}
			//если данныее не найдены
			if(flag == 0)
			{
				printf("||%98c||\n", ' ');
				printf("|| There is no data in the specified range.%57c||\n", ' ');
				printf("||%98c||\n", ' ');
			}
		
			free(buffer);
		}
		else
		{
			printf("\nThe date range is specified incorrectly.");
			printf("\nCheck if the date are entered correctly.");
			printf("\nTry -h for help.\n\n");
		}
		
	}
}
