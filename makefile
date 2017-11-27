 
all: catarata
 
catarata: main.o ppm.o
	gcc -o catarata main.o ppm.o -lm
 
main.o: main.c ppm.h
	gcc -o main.o main.c -c
 
ppm.o: ppm.c ppm.h
	gcc -o ppm.o ppm.c -c 
 
clean:
	rm  *.o catarata
