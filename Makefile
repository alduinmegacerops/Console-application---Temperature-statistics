all: prog

prog: Src/main.o Lib/temp_functions.o
	gcc -o prog Lib\temp_functions.o Src\main.o

Src/main.o: Src/main.c Inc/main.h
	gcc -c --std=c99 -o Src\main.o  Src\main.c

Lib/temp_functions.o: Lib/temp_functions.c Inc/temp_functions.h
	gcc -c --std=c99 -o Lib\temp_functions.o  Lib\temp_functions.c