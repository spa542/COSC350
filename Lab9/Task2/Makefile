pipe3: pipe3.o pipe4
	gcc -o pipe3 pipe3.o -g
pipe4: pipe4.o
	gcc -o pipe4 pipe4.o -g
pipe3.o: pipe3.c
	gcc -c pipe3.c -g
pipe4.o: pipe4.c
	gcc -c pipe4.c -g
clean:
	rm -f *.o pipe3 pipe4
