buildsm: buildsm.o removesm process1 process2
	gcc -o buildsm buildsm.o -g
removesm: removesm.o process1 process2
	gcc -o removesm removesm.o -g
process1: process1.o process2
	gcc -o process1 process1.o -g
process2: process2.o
	gcc -o process2 process2.o -g
buildsm.o: buildsm.c
	gcc -c buildsm.c -g
removesm.o: removesm.c
	gcc -c removesm.c -g
process1.o: process1.c
	gcc -c process1.c -g
process2.o: process2.c
	gcc -c process2.c -g
clean:
	rm -f *.o buildsm removesm process1 process2
