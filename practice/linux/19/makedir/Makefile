main: main.o fun.o main.h
	gcc *.o -o main
main.o: main.c main.h
	gcc -c main.c
fun.o: fun.c main.h
	gcc -c fun.c
clean:
	rm main *.o
rebuild: clean main
