forkExec: forkExec.o child
	gcc -o forkExec forkExec.o
child: child.o
	gcc -o child child.o
forkExec.o: forkExec.c
	gcc -c forkExec.c
child.o: child.c
	gcc -c child.c
clean:
	rm -f *.o forkExec child
