all: prog

prog: Src/main.o Lib/temp_functions.o Lib/sort.o Lib/interface.o
	gcc -o prog Lib/temp_functions.o Lib/sort.o Lib/interface.o Src/main.o

Src/main.o: Src/main.c Inc/main.h
	gcc -c --std=c99 -o Src/main.o  Src/main.c

Lib/temp_functions.o: Lib/temp_functions.c Inc/temp_functions.h
	gcc -c --std=c99 -o Lib/temp_functions.o  Lib/temp_functions.c
	
Lib/sort.o: Lib/sort.c
	gcc -c --std=c99 -o Lib/sort.o  Lib/sort.c
	
Lib/interface.o: Lib/interface.c
	gcc -c --std=c99 -o Lib/interface.o  Lib/interface.c