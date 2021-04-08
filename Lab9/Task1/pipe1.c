/*
 * pipe1.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/8/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<string.h> // String Functions
#include<unistd.h> // write(), read(), pipe()

// Global constants
#define READ_END 0
#define WRITE_END 1

/*
 * Copy pipe1.c from BLP page 532-533. Compile and run it. Reverse the 
 * order of the write and read and run the program again. Briefly describe
 * what happened with the reversed order and why the program behaved that 
 * way. Restore the read and write to their original order before proceeding.
 * Modify pipe1.c in the following ways:
 * a. It's a good idea to define two global integer constants
 *  1. READ_END = 0
 *  2. WRITE_END = 1
 * b. Dynamically allocate buffer so it's exaclty the right size for
 * some_data.
 * c. Copy the string from some_data into buffer
 * d. Modify the read so it's third argument is the exact size of buffer
 * (rather than the large BUFSIZ)
 */
int main(void) {
    int data_processed;
    int file_pipes[2];
    const char some_data[] = "123";
    char* buffer = (char*)malloc(strlen(some_data)*sizeof(char)+1);
    //memset(buffer, '\0', sizeof(buffer));
    strcpy(buffer, some_data);
    if (pipe(file_pipes) == 0) {
        data_processed = write(file_pipes[WRITE_END], some_data, strlen(some_data));
        printf("Wrote %d bytes\n", data_processed);
        data_processed = read(file_pipes[READ_END], buffer, strlen(buffer));
        printf("Read %d bytes: %s\n", data_processed, buffer);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}
