/*
 * task4.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/1/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<unistd.h> // pipe(), popen(), pclose()
#include<sys/types.h> // pid_t
#include<string.h> // String functions
#include<stdbool.h> // bool alias

#define BUFFER_SIZE 80

/*
 * Use popen() to create a child and a pipe. The parent process asks for two
 * arguments from the command line (a shell command and a file name). Then,
 * the the parent will send the data to the child using popen(). The child
 * process will implement the command with file as an input and then send
 * to the parent. The parent simply must then display output from the child 
 * on standard output.
 */
int main(int argc, char** argv) {
    
    // Argument # check
    if (argc != 3) {
        puts("*** Invalid # of arguments ***");
        return 1; // Returning because the # of arguments is invalid
    }

    // Create the buffer
    char buffer[BUFFER_SIZE];
    // Create the file pointer for the pipe
    FILE* fpin; 
    // Temp buffer for pass
    char* command = (char*)malloc((strlen(argv[1])+strlen(argv[2])+1)*sizeof(char));
    strcpy(command, argv[1]);
    strcat(command, " ");
    strcat(command, argv[2]);

    // Create the pipe for reading
    if ((fpin = popen(command, "r")) == NULL) {
        puts("*** Error calling popen ***");
        return 2; // Returning because there was an error with popen
    }

    // Read from the pipe and write the contents to standard output
    while (true) {
        if (fgets(buffer, BUFFER_SIZE, fpin) == NULL) { // Interesting way to get from pipe
            // All done reading from pipe
            break;
        }
        if (fputs(buffer, stdout) == EOF) { // Interesting way to write to standard output
            puts("*** Error writing to standard output ***");
        }
    }

    // Free
    free(command);

    return 0;
}
