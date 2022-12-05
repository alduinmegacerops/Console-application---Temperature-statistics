all: stattemp

stattemp: Src/main.o Lib/temp_functions.o Lib/sort.o Lib/printstat.o Lib/adddel.o Lib/printdata.o
	gcc -o stattemp Lib/temp_functions.o Lib/sort.o Lib/printstat.o Lib/adddel.o Lib/printdata.o Src/main.o

Src/main.o: Src/main.c Inc/main.h
	gcc -c --std=c99 -o Src/main.o  Src/main.c

Lib/temp_functions.o: Lib/temp_functions.c Inc/temp_functions.h
	gcc -c --std=c99 -o Lib/temp_functions.o  Lib/temp_functions.c
	
Lib/sort.o: Lib/sort.c
	gcc -c --std=c99 -o Lib/sort.o  Lib/sort.c
	
Lib/printstat.o: Lib/printstat.c
	gcc -c --std=c99 -o Lib/printstat.o  Lib/printstat.c
	
Lib/adddel.o: Lib/adddel.c
	gcc -c --std=c99 -o Lib/adddel.o  Lib/adddel.c

Lib/printdata.o: Lib/printdata.c
	gcc -c --std=c99 -o Lib/printdata.o  Lib/printdata.c
	
clean:
	del Lib\*.o
	del Src\*.o
	del stattemp.exe