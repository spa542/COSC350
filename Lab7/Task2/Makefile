ctrlc1: ctrlc1.o ctrlc2
	gcc -o ctrlc1 ctrlc1.o
ctrlc2: ctrlc2.o
	gcc -o ctrlc2 ctrlc2.o
ctrlc1.o: ctrlc1.c
	gcc -c ctrlc1.c
ctrlc2.o: ctrlc2.c
	gcc -c ctrlc2.c
clean:
	rm -f *.o ctrlc1 ctrlc2
