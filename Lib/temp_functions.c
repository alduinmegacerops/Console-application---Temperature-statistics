#include "../Inc/temp_functions.h"

//функция для считывания и парсинга данных	
void addDataTemperature(data *sensor, char *nameFile)
{	
	//инициализируем структуру
	sensor -> dataTemperature = NULL;
	sensor -> errorCount = 0;
	sensor -> lineFileDataError = NULL;
	
	char buffer[21];
	//проверяем была ли задана дирректория с файлом на обработку
	if(strlen(nameFile) == 1)
		printf("The <filename.csv> file directory is not set.");
	
	FILE *in;
	//открываем файл на чтение
	in = fopen(nameFile, "r");
	//проверяем задан ли существующий файл на обработку
	if(in == NULL)
		printf("A non-existing file or directory with the file is specified <filename.csv>.");
	
	for(sensor -> countSensorMeasurements = 0; fscanf(in, "%21[^\n]", buffer) != -1; sensor -> countSensorMeasurements++)
	{
		char tmp;
		
		uint8_t flag = 1;
		//цикл пропускает оставшиеся символы до конца файла или строки (на случай, если строка была чересчур длинной
		do
		{
			tmp = fgetc(in);
		}
		while(tmp != EOF && tmp != '\n');
		//проверка буффера на корректность данных	
		for(int i = 0; i < strlen(buffer); i++)
		{				
			if(buffer[i] == ';' || buffer[i] == '-' || buffer[i] == ' ' || buffer[i] == 0x0 || (buffer[i] >= '0' && buffer[i] <= '9'))
				flag = 0;
			else
			{
				flag = 1;
				//обработка ошибок. Плюс новая ошибка	
				sensor -> errorCount++;
				//переопределяем память под новую ошибку
				sensor -> lineFileDataError = realloc(sensor -> lineFileDataError, sizeof(uint32_t) * (sensor -> errorCount + 1));
				//запоминаем номер линии где встретились битые данные
				sensor -> lineFileDataError[sensor -> errorCount - 1] = sensor -> countSensorMeasurements + sensor -> errorCount;
				//уменьшаем счетчик валидных данных
				sensor -> countSensorMeasurements--;
				//освобождаем буффер и заканчиваем проверку буффера
				memset(buffer, 0, sizeof(buffer));
				break;
			}
		}
		//парсим данные из буфера по полям структуры		
		if(flag == 0)
		{
			//переопределяем память под новые данные
			sensor -> dataTemperature = realloc(sensor -> dataTemperature, sizeof(struct sensorTemperature) * (sensor -> countSensorMeasurements + 1));
			//записываем новые данные
			sscanf(buffer, "%d;%d;%d;%d;%d;%d",	&sensor -> dataTemperature[sensor -> countSensorMeasurements].year, 
												&sensor -> dataTemperature[sensor -> countSensorMeasurements].month,
												&sensor -> dataTemperature[sensor -> countSensorMeasurements].day,
												&sensor -> dataTemperature[sensor -> countSensorMeasurements].hour,
												&sensor -> dataTemperature[sensor -> countSensorMeasurements].minute,
												&sensor -> dataTemperature[sensor -> countSensorMeasurements].temperature);
			//освобождаем буффер
			memset(buffer, 0, sizeof(buffer));
		}
	}
	
	fclose(in);
}
//функция для расчета среднемесячной температуры
void middleTemperatureMonth(data *sensor, float (*stat)[4])
{
	float sum[12] = {0}, counter[12] = {0};
	
	for(int i = 0; i < sensor -> countSensorMeasurements; i++)
	{
		sum[sensor -> dataTemperature[i].month - 1] += sensor -> dataTemperature[i].temperature;
		counter[sensor -> dataTemperature[i].month - 1]++;
	}
	
	for(int i = 0; i < 12; i++)
	{
		if(counter[i] == 0)
			stat[i][0] = 1;
		else
			stat[i][1] = sum[i] / counter[i];
	}
}
//функция для нахождения минимальной температуры за месяц
void minTemperatureMonth(data *sensor, float (*stat)[4])
{
	int minMonth[12] = {0}, count = 0;
	
	for(int countMonth = 0; countMonth < 12; countMonth++)
	{
		minMonth[countMonth] = sensor -> dataTemperature[count].temperature;
		
		while(sensor -> dataTemperature[count].month == countMonth + 1)
		{
			if(minMonth[countMonth] > sensor -> dataTemperature[count].temperature)
				minMonth[countMonth] = sensor -> dataTemperature[count].temperature;
			count++;
		}
	}
	
	for(int i = 0; i < 12; i++)
		stat[i][2] = minMonth[i];
}
//функция для нахождения максимальной температуры за месяц
void maxTemperatureMonth(data *sensor, float (*stat)[4])
{
	int maxMonth[12] = {0}, count = 0;
	
	for(int countMonth = 0; countMonth < 12; countMonth++)
	{
		maxMonth[countMonth] = sensor -> dataTemperature[count].temperature;

		while(sensor -> dataTemperature[count].month == countMonth + 1)
		{
			if(maxMonth[countMonth] < sensor -> dataTemperature[count].temperature)
				maxMonth[countMonth] = sensor -> dataTemperature[count].temperature;
			count++;
		}
	}
	
	for(int i = 0; i < 12; i++)
		stat[i][3] = maxMonth[i];
}
//функция для расчета среднегодовой температуры
float middleTemperatureYear(data *sensor)
{
	float sumTemperatureYear = 0;
		
	for(int i = 0; i < sensor -> countSensorMeasurements; i++)
		sumTemperatureYear += sensor -> dataTemperature[i].temperature;
		
	return sumTemperatureYear / sensor -> countSensorMeasurements;
}
//функция для нахождения минимальной температуры за год
int minTemperatureYear(data *sensor)
{
	int minTempYear = sensor -> dataTemperature[0].temperature;
	
	for(int i = 1; i < sensor -> countSensorMeasurements; i++)
		if(minTempYear > sensor -> dataTemperature[i].temperature)
			minTempYear = sensor -> dataTemperature[i].temperature;
			
	return minTempYear;
}
//функция для нахождения максимальной температуры за год
int maxTemperatureYear(data *sensor)
{
	int maxTempYear = sensor -> dataTemperature[0].temperature;
	
	for(int i = 1; i < sensor -> countSensorMeasurements; i++)
		if(maxTempYear < sensor -> dataTemperature[i].temperature)
			maxTempYear = sensor -> dataTemperature[i].temperature;
			
	return maxTempYear;
}
