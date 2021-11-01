all: main.o
	gcc -o main.out main.o

main.o: main.c
	gcc -c main.c

run:
	./main.out

clean:
	rm *.o
	rm main.out

comprun: all
	./main.out
