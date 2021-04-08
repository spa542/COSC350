twoPipesParent: twoPipesParent.o twoPipesChild
	gcc -o twoPipesParent twoPipesParent.o -g
twoPipesChild: twoPipesChild.o
	gcc -o twoPipesChild twoPipesChild.o -g
twoPipesParent.o: twoPipesParent.c
	gcc -c twoPipesParent.c -g
twoPipesChild.o: twoPipesChild.c
	gcc -c twoPipesChild.c -g
clean:
	rm -f *.o twoPipesChild twoPipesParent
