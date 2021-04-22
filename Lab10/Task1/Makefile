msgQsnd: msgQsnd.o msgQrcv
	gcc -o msgQsnd msgQsnd.o -g
msgQrcv: msgQrcv.o
	gcc -o msgQrcv msgQrcv.o -g
msgQsnd.o: msgQsnd.c
	gcc -c msgQsnd.c -g
msgQrcv.o: msgQrcv.c
	gcc -c msgQrcv.c -g
clean:
	rm -f *.o msgQsnd msgQrcv
