all: signals.o
	gcc -o test signals.o

signals.o: signals.c
	gcc -c signals.c

run:
	./test

clean:
	rm *.o
