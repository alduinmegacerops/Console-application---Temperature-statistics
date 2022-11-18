#include "../Inc/temp_functions.h"

int main(int argc, char **argv)
{
	struct sensorTemperature *dataTemperature = NULL;
	
	//dataTemperature = malloc(MAX_COUNT_YEAR_T * sizeof(struct sensorTemperature));
	//Выделение памяти пот массив структур и проверка выделилась ли память
	if (!(dataTemperature = malloc(MAX_COUNT_YEAR_T * sizeof(struct sensorTemperature))))
	{
		printf("Error: can't allocate memory");
		exit(1);
	}
	
	addDataTemperature(dataTemperature);
	
	printDataTemperature(dataTemperature);
	
	printf("\nNot error");
	
	return 0;
}
