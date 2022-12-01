#include "../Inc/temp_functions.h"

//функци перевода даты и временив в uint64_t
uint64_t dateToInt(data *sensor, uint32_t i)
{
	return 	sensor -> dataTemperature[i].minute + 
			sensor -> dataTemperature[i].hour * 100 + 
			sensor -> dataTemperature[i].day * 10000 + 
			sensor -> dataTemperature[i].month * 1000000 + 
			sensor -> dataTemperature[i].year * 100000000;
}
//функция меняет местами i-й элемент с j-ым элементом
void swap(data *sensor, uint32_t i, uint32_t j)
{
	struct sensorTemperature temp;
	temp = sensor -> dataTemperature[i];
	sensor -> dataTemperature[i] = sensor -> dataTemperature[j];
	sensor -> dataTemperature[j] = temp;
}
//функция сортировки пузырьком
void sortByDate(data *sensor, char *nameFile)
{
	if(strcmp(nameFile, "Data/temperature_big.csv") && strcmp(nameFile, "Data/temperature_big_t.csv"))
		for(int i = 0; i < sensor -> countSensorMeasurements; ++i)
			for (int j = i; j < sensor -> countSensorMeasurements; ++j)
				if(dateToInt(sensor, i) >= dateToInt(sensor, j))
					swap(sensor, i, j);
}
