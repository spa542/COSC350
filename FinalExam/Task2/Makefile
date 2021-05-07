one: task2a.o two three
	gcc -o one task2a.o -g
two: task2b.o three
	gcc -o two task2b.o -g
three: task2c.o
	gcc -o three task2c.o -g
task2a.o: task2a.c
	gcc -c task2a.c -g
task2b.o: task2b.c
	gcc -c task2b.c -g
task2c.o: task2c.c
	gcc -c task2c.c -g
clean:
	rm -f *.o one two three
