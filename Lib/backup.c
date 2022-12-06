#include "../Inc/temp_functions.h"

//функция резервного копирования
void backup(char *nameFile)
{
	char outNameFile[100];
	char name[100];
	char *buffer;
	char buffer_write[21];
	
	memset(outNameFile, 0, sizeof(outNameFile));
	memset(name, 0, sizeof(name));
	memset(buffer_write, 0, sizeof(buffer_write));
	
	FILE *in;
	FILE *out;
	//переписывамя имя в файла
	strcat(name, nameFile);
	//обрезаем часть с расширением
	buffer = strtok(name, ".");
	//собираем название файла backuo
	strcat(outNameFile, name);
	strcat(outNameFile, "_backup.csv");
	//открываем файл на чтение
	in = fopen(nameFile, "r");
	//проверяем задан ли существующий файл на обработку
	if(in != NULL)
	{
		//открываем файл на запись
		out = fopen(outNameFile, "w");
		//переписывамя файл в новый
		while(fscanf(in, "%21[^\n]", buffer_write) != -1)
		{
			char tmp;
			//цикл пропускает оставшиеся символы до конца файла или строки (на случай, если строка была чересчур длинной
			do
			{
				tmp = fgetc(in);
			}
			while(tmp != EOF && tmp != '\n');
			
			fprintf(out, "%s\n", buffer_write);
			memset(buffer_write, 0, sizeof(buffer_write));
		}
	}
	
	fclose(in);
	fclose(out);
}
