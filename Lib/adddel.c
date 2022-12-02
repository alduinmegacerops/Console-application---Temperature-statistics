#include "../Inc/temp_functions.h"

//функция проверки данных введенных после ключа -a и -d
uint8_t checkDataIn(char *strChek)
{
	uint8_t tempCount = 0;
	
	struct sensorTemperature temp;
	
	for(int i = 0; i < strlen(strChek); i++)
		if(strChek[i] == ';' && strChek[strlen(strChek) - 1] != ';')
			tempCount++;
			
	if(tempCount == 5)
	{
		sscanf(strChek, "%d;%d;%d;%d;%d;%d", 	&temp.year,
												&temp.month,
												&temp.day,
												&temp.hour,
												&temp.minute,
												&temp.temperature);
		//проверка на корректность введенного месяца
		if(temp.month > 0 && temp.month < 13)
		{
			//проверка высокосного года	
			if(temp.month == 2 && (temp.year - 2000) % 4 == 0)
			{
				//проверка на корректность введенных дня, часа, минуты и температуры
				if(temp.day > 0 && temp.day < 30 && temp.hour >= 0 && temp.hour < 24 && temp.minute >= 0 && temp.minute < 60 && temp.temperature > -100 && temp.temperature < 100)
					return 1;
				else
					return 0;
			}
			else if(temp.month == 2 && (temp.year - 2000) % 4 != 0)
			{
				//проверка на корректность введенных дня, часа, минуты и температуры
				if(temp.day > 0 && temp.day < 29 && temp.hour >= 0 && temp.hour < 24 && temp.minute >= 0 && temp.minute < 60 && temp.temperature > -100 && temp.temperature < 100)
					return 1;
				else
					return 0;
			}
			//проверка на 31 день в месяце
			else if(temp.month == 1 || temp.month == 3 || temp.month == 5 || temp.month == 7 || temp.month == 8 || temp.month == 10 || temp.month == 11)
			{
				//проверка на корректность введенных дня, часа, минуты и температуры
				if(temp.day > 0 && temp.day < 32 && temp.hour >= 0 && temp.hour < 24 && temp.minute >= 0 && temp.minute < 60 && temp.temperature > -100 && temp.temperature < 100)
					return 1;
				else
					return 0;	
			}
			//проверка на 30 дней в месяце
			else if(temp.month == 4 || temp.month == 6 || temp.month == 9 || temp.month == 11)
			{
				//Проверка на корректность введенных дня, часа, минуты и температуры
				if(temp.day > 0 && temp.day < 31 && temp.hour >= 0 && temp.hour < 24 && temp.minute >= 0 && temp.minute < 60 && temp.temperature > -100 && temp.temperature < 100)
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
	if(strlen(dataLine) > 1)
	{
		//увеличиваем счетчик валидных данных
		sensor -> countSensorMeasurements++;
		//переопределяем память под новые данные
		sensor -> dataTemperature = realloc(sensor -> dataTemperature, sizeof(struct sensorTemperature) * (sensor -> countSensorMeasurements + 1));
		//добавляем новые данные
		sscanf(dataLine, "%d;%d;%d;%d;%d;%d",	&sensor -> dataTemperature[sensor -> countSensorMeasurements - 1].year, 
												&sensor -> dataTemperature[sensor -> countSensorMeasurements - 1].month,
												&sensor -> dataTemperature[sensor -> countSensorMeasurements - 1].day,
												&sensor -> dataTemperature[sensor -> countSensorMeasurements - 1].hour,
												&sensor -> dataTemperature[sensor -> countSensorMeasurements - 1].minute,
												&sensor -> dataTemperature[sensor -> countSensorMeasurements - 1].temperature);
		//текущее положение новых данных
		int count = sensor -> countSensorMeasurements - 1;
		//проверяем есть ли данные на дату новых данных
		for(int i = 0; i < sensor -> countSensorMeasurements - 1; i++)
		{
			if(dateToInt(sensor, count) == dateToInt(sensor, i))
			{
				count = -1;
				break;
			}
		}
		//printf("%d", sensor -> countSensorMeasurements);
		if(count != -1)
		{
			//перносим данные согласно сортирвке по дате и времени
			while(dateToInt(sensor, count) < dateToInt(sensor, count - 1) && count > 1)
			{
				swap(sensor, count, count - 1);
				count--;
			}
			//Добавляем строку в исходный файл
			FILE *newData;
			//открываем файл
			newData = fopen(nameFile, "a");
			//записываем строку в конец файла
			fprintf(newData, "%s\n", dataLine);
			
			fclose(newData);
		}
		else
		{
			sensor -> countSensorMeasurements--;
			sensor -> dataTemperature = realloc(sensor -> dataTemperature, sizeof(struct sensorTemperature) * (sensor -> countSensorMeasurements + 1));
			printf("The data for the specified date already exists.\n");
			printf("To replace, delete the old data by the specified date.\n");
		}
	}
}
//функция удаления данных введеных с ключа -d
/*void delData(data *sensor, char *dataLine, char *nameFile)
{
	if(strlen(dataLine) > 1)
	{
		//увеличиваем счетчик валидных данных
		sensor -> countSensorMeasurements++;
		//переопределяем память под новые данные
		sensor -> dataTemperature = realloc(sensor -> dataTemperature, sizeof(struct sensorTemperature) * (sensor -> countSensorMeasurements + 1));
		//текущее положение новых данных
		int count = sensor -> countSensorMeasurements - 1;
		//проверяем есть ли данные на дату новых данных
		for(int i = 0; i < sensor -> countSensorMeasurements - 1; i++)
		{
			if(dateToInt(sensor, count) == dateToInt(sensor, i))
			{
				count = -1;
				break;
			}
		}
		if(count != -1)
		{
			//перносим данные согласно сортирвке по дате и времени
			while(dateToInt(sensor, count) < dateToInt(sensor, count - 1))
			{
				swap(sensor, count, count - 1);
				count--;
			}
			//Добавляем строку в исходный файл
			FILE *newData;
			//открываем файл
			newData = fopen(nameFile, "a");
			//записываем строку в конец файла
			fprintf(newData, "%s\n", dataLine);
			
			fclose(newData);
		}
		else
		{
			sensor -> countSensorMeasurements--;
			sensor -> dataTemperature = realloc(sensor -> dataTemperature, sizeof(struct sensorTemperature) * (sensor -> countSensorMeasurements + 1));
			printf("The data for the specified date already exists.\n");
			printf("To replace, delete the old data by the specified date.\n");
		}
	}
}*/
