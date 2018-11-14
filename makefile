main: main.o list.o
	gcc -o main main.o list.o
main.o: main.c assignment3.h
	gcc -c main.c
list.o: list.c assignment3.h
	gcc -c list.c
clean:
	rm main main.o list.o