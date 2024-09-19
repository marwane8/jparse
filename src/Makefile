all: ../build/jparse
	../build/jparse

../build/jparse: main.o strvec.o
	gcc main.o strvec.o -o ../build/jparse

main.o: main.c strvec.h
	gcc -c main.c

strvec.o: strvec.h
	gcc -c strvec.c

clean:
	rm -rf ../build/*
	rm -rf *.o