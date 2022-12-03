#include "../Inc/temp_functions.h"

//функци перевода даты и временив в uint64_t
uint64_t dateToInt(struct sensorTemperature *dataTemperature, uint32_t i)
{
	return 	dataTemperature[i].minute + 
			dataTemperature[i].hour * 100 + 
			dataTemperature[i].day * 10000 + 
			dataTemperature[i].month * 1000000 + 
			dataTemperature[i].year * 100000000;
}
//функция меняет местами i-й элемент с j-ым элементом
void swap(data *sensor, uint32_t i, uint32_t j)
{
	struct sensorTemperature temp;
	temp = sensor -> dataTemperature[i];
	sensor -> dataTemperature[i] = sensor -> dataTemperature[j];
	sensor -> dataTemperature[j] = temp;
}
//функция сортировки шейкером
void sortByDate(data *sensor, char *nameFile)
{
	uint32_t right = sensor -> countSensorMeasurements - 1;
	uint32_t left = 0;
	uint8_t flag = 1;
	
	while(left < right && flag > 0)
	{
		flag = 0;
		for(int i = left; i < right; i++)
		{
			if(dateToInt(sensor -> dataTemperature, i) > dateToInt(sensor -> dataTemperature, i + 1))
			{
				swap(sensor, i, i + 1);
				flag = 1;
			}
		}
		right--;
		for(int i = right; i > left; i--)
		{
			if(dateToInt(sensor -> dataTemperature, i) < dateToInt(sensor -> dataTemperature, i - 1))
			{
				swap(sensor, i, i - 1);
				flag = 1;
			}
		}
		left++;
	}
}
