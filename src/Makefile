all: ../build/jparse
	../build/jparse

../build/jparse: main.o
	gcc main.o -o ../build/jparse

main.o: main.c
	gcc -c main.c

clean:
	rm -rf ../build/*
	rm -rf *.o