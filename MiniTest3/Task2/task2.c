#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

int main(int argc, char** argv) {
    srand(time(NULL));

    if (argc != 2) {
        puts("*** Incorrect # of arguments ***");
        exit(1);
    }

    int argument = atoi(argv[1]);

    if (argument < 1) {
        puts("*** Argument is not a positive integer >= 1 ***");
        exit(2);
    }

    char array[argument]; 
    memset(array, 0, argument);

    int i;
    for (i = 0; i < argument; i++) {
        array[i] = rand() % 26 + 'a';
    }

    write(1, array, argument);
    puts("");

    exit(0);
}
