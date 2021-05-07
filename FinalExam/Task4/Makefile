one: task4a.o two
	gcc -o one task4a.o -g
two: task4b.o
	gcc -o two task4b.o -g
task4a.o: task4a.c
	gcc -c task4a.c -g
task4b.o: task4b.c
	gcc -c task4b.c -g
clean:
	rm -f *.o one two
