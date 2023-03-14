all: geometry

geometry: geometry.c
	gcc -Wall geometry.c -o geometry -lm
run:
	./geometry test.txt