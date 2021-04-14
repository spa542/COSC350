#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<stdbool.h>

#define BUFFER_SIZE 256

int main(void) {

    FILE* fh;
    char buffer[BUFFER_SIZE];
    int temp1, temp2;

    fh = popen("./anyinput", "r");

    while(true) {
        if (fgets(buffer, BUFFER_SIZE, fh) == NULL) {
            break; 
        }
        if (fputs(buffer, stdout) == EOF) {
            printf("*** Error writing to standard output ***\n");
        }
        if (sscanf(buffer, "%d%d", &temp1, &temp2) == 2) {
            printf("%d * %d = %d\n", temp1, temp2, temp1*temp2);
        } else {
            puts("invalid inputs: two integers");
        }
    }

    return 0;
}
