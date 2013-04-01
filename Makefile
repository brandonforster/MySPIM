all: runme

runme: project.o spimcore.o
	gcc project.o spimcore.o -o RunMe

project.o: project.c
	gcc -c project.c

spimcore.o: spimcore.c
	gcc -c spimcore.c

clean:
	rm -rf *o RunMe
