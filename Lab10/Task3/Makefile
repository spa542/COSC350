task3: task3.o buildsem
	gcc -o task3 task3.o -g -pthread
buildsem: buildsem.o
	gcc -o buildsem buildsem.o -g
task3.o: task3.c
	gcc -c task3.c -g -pthread
buildsem.o: buildsem.c
	gcc -c buildsem.c -g
clean:
	rm -f *.o task3 buildsem
