#include "../Inc/temp_functions.h"

//функция проверки данных введенных после ключа -a и -d
uint8_t checkDataIn(char *strChek)
{
	uint8_t tempCount = 0;
	
	struct sensorTemperature checkBuffer;
	
	for(int i = 0; i < strlen(strChek); i++)
		if(strChek[i] == ':' && strChek[strlen(strChek) - 1] != ':')
			tempCount++;
			
	if(tempCount == 5)
	{
		sscanf(strChek, "%d:%d:%d:%d:%d:%d", 	&checkBuffer.year,
												&checkBuffer.month,
												&checkBuffer.day,
												&checkBuffer.hour,
												&checkBuffer.minute,
												&checkBuffer.temperature);
		//проверка на корректность введенного месяца
		if(checkBuffer.month > 0 && checkBuffer.month < 13)
		{
			//проверка высокосного года	
			if(checkBuffer.month == 2 && (checkBuffer.year - 2000) % 4 == 0)
			{
				//проверка на корректность введенных дня, часа, минуты и температуры
				if(checkBuffer.day > 0 && checkBuffer.day < 30 && checkBuffer.hour >= 0 && checkBuffer.hour < 24 && checkBuffer.minute >= 0 && checkBuffer.minute < 60 && checkBuffer.temperature > -100 && checkBuffer.temperature < 100)
					return 1;
				else
					return 0;
			}
			else if(checkBuffer.month == 2 && (checkBuffer.year - 2000) % 4 != 0)
			{
				//проверка на корректность введенных дня, часа, минуты и температуры
				if(checkBuffer.day > 0 && checkBuffer.day < 29 && checkBuffer.hour >= 0 && checkBuffer.hour < 24 && checkBuffer.minute >= 0 && checkBuffer.minute < 60 && checkBuffer.temperature > -100 && checkBuffer.temperature < 100)
					return 1;
				else
					return 0;
			}
			//проверка на 31 день в месяце
			else if(checkBuffer.month == 1 || checkBuffer.month == 3 || checkBuffer.month == 5 || checkBuffer.month == 7 || checkBuffer.month == 8 || checkBuffer.month == 10 || checkBuffer.month == 11)
			{
				//проверка на корректность введенных дня, часа, минуты и температуры
				if(checkBuffer.day > 0 && checkBuffer.day < 32 && checkBuffer.hour >= 0 && checkBuffer.hour < 24 && checkBuffer.minute >= 0 && checkBuffer.minute < 60 && checkBuffer.temperature > -100 && checkBuffer.temperature < 100)
					return 1;
				else
					return 0;	
			}
			//проверка на 30 дней в месяце
			else if(checkBuffer.month == 4 || checkBuffer.month == 6 || checkBuffer.month == 9 || checkBuffer.month == 11)
			{
				//Проверка на корректность введенных дня, часа, минуты и температуры
				if(checkBuffer.day > 0 && checkBuffer.day < 31 && checkBuffer.hour >= 0 && checkBuffer.hour < 24 && checkBuffer.minute >= 0 && checkBuffer.minute < 60 && checkBuffer.temperature > -100 && checkBuffer.temperature < 100)
					return 1;
				else
					return 0;	
			}
			else
				return 0;
		}
		else
			return 0;
	}
	else
		return 0;
}
//функция добавления данных введеных с ключа -a
void addData(data *sensor, char *dataLine, char *nameFile)
{
	struct sensorTemperature checkBuffer;

	int count = 0;
	
	if(strlen(dataLine) > 1)
	{
		//заполняем временную структуру
		sscanf(dataLine, "%d:%d:%d:%d:%d:%d", 	&checkBuffer.year,
												&checkBuffer.month,
												&checkBuffer.day,
												&checkBuffer.hour,
												&checkBuffer.minute,
												&checkBuffer.temperature);
		
		//проверяем есть ли данные на дату новых данных
		for(int i = 0; i < sensor -> countSensorMeasurements; i++)
		{
			if(dateToInt(&checkBuffer, 0) == dateToInt(sensor -> dataTemperature, i))
			{
				printf("\nThe data for the specified date already exists.\n");
				printf("To replace, delete the old data by the specified date.\n\n");
				count = -1;
				break;
			}
		}
		//если данных на заданную дату нет
		if(count != -1)
		{
			//увеличиваем счетчик валидных данных
			sensor -> countSensorMeasurements++;
			//переопределяем память под новые данные
			sensor -> dataTemperature = (struct sensorTemperature*)realloc(sensor -> dataTemperature, sizeof(struct sensorTemperature) * (sensor -> countSensorMeasurements + 1));
			//добавляем новые данные
			sscanf(dataLine, "%d:%d:%d:%d:%d:%d",	&sensor -> dataTemperature[sensor -> countSensorMeasurements - 1].year, 
													&sensor -> dataTemperature[sensor -> countSensorMeasurements - 1].month,
													&sensor -> dataTemperature[sensor -> countSensorMeasurements - 1].day,
													&sensor -> dataTemperature[sensor -> countSensorMeasurements - 1].hour,
													&sensor -> dataTemperature[sensor -> countSensorMeasurements - 1].minute,
													&sensor -> dataTemperature[sensor -> countSensorMeasurements - 1].temperature);
			//Добавляем строку в исходный файл
			FILE *newData;
			//открываем файл
			newData = fopen(nameFile, "a");
			//записываем строку в конец файла
			fprintf(newData, "%d;%d;%d;%d;%d;%d\n",	sensor -> dataTemperature[sensor -> countSensorMeasurements - 1].year, 
													sensor -> dataTemperature[sensor -> countSensorMeasurements - 1].month,
													sensor -> dataTemperature[sensor -> countSensorMeasurements - 1].day,
													sensor -> dataTemperature[sensor -> countSensorMeasurements - 1].hour,
													sensor -> dataTemperature[sensor -> countSensorMeasurements - 1].minute,
													sensor -> dataTemperature[sensor -> countSensorMeasurements - 1].temperature);
			
			fclose(newData);
		}
	}
}
//функция удаления данных введеных с ключа -d
void delData(data *sensor, char *dataLine, char *nameFile)
{
	struct sensorTemperature checkBuffer;

	int count = 0;
	
	if(strlen(dataLine) > 1)
	{
		//заполняем временную структуру
		sscanf(dataLine, "%d:%d:%d:%d:%d:%d", 	&checkBuffer.year,
												&checkBuffer.month,
												&checkBuffer.day,
												&checkBuffer.hour,
												&checkBuffer.minute,
												&checkBuffer.temperature);
		
		//проверяем существуют ли удаляемые данные
		for(int i = 0; i < sensor -> countSensorMeasurements; i++)
		{
			if(dateToInt(&checkBuffer, 0) == dateToInt(sensor -> dataTemperature, i))
			{
				//меняем местами удаляемую строку и последнюю строку
				if(i != sensor -> countSensorMeasurements - 1)
					swap(sensor, i, sensor -> countSensorMeasurements - 1);
				//увеличиваем счетчик валидных данных
				sensor -> countSensorMeasurements--;
				//переопределяем память под новое количество данных
				sensor -> dataTemperature = (struct sensorTemperature*)realloc(sensor -> dataTemperature, sizeof(struct sensorTemperature) * (sensor -> countSensorMeasurements + 1));
				//Убираем строку из исходного файла
				FILE *oldData;
				//открываем файл
				oldData = fopen(nameFile, "w");
				//перезаписываем исходные файлы
				for(int i = 0; i < sensor -> countSensorMeasurements; i++)
				{
					fprintf(oldData, "%d;%d;%d;%d;%d;%d\n",	sensor -> dataTemperature[i].year, 
															sensor -> dataTemperature[i].month,
															sensor -> dataTemperature[i].day,
															sensor -> dataTemperature[i].hour,
															sensor -> dataTemperature[i].minute,
															sensor -> dataTemperature[i].temperature);
				}
				for(int i = 0; i < sensor -> errorCount; i++)
				{
					fprintf(oldData, "%s\n", sensor -> dataError[i]);
				}
				fclose(oldData);
				count = -1;
				break;
			}
		}
		//если данных на заданную дату нет
		if(count != -1)
		{
			printf("\nThere is no data for the specified date.\n\n");
		}
	}
}
