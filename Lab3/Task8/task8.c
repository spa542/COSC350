/*
 * task8.c
 * Ryan Rosiak
 * COSC 350-750
 * 2/22/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard library 
#include<string.h> // String functions
#include<fcntl.h> // open()
#include<unistd.h> // read(), write()
#include<stdbool.h> // bool alias
#include<sys/stat.h> // umask()

#define BUFFER_SIZE 1

/*
 * myAtoI Function:
 * Converts a single character to it's ASCII representation
 */
char* myAtoItoA(char num, char* buffer) {
    // Subtract the ASCII 0 from each digit and then multiply by each
    // decimal place to get out number back
    int asciiInt = 0;
    asciiInt = num - '\0';

    printf("%d\n", asciiInt);
    int i = 0;
    while (asciiInt != 0) {
        buffer[i++] = asciiInt % 10 + '0';
        asciiInt /= 10;
    }
    buffer[i] = '\0';
    printf("%s\n", buffer);
    return buffer;
}

/*
 * Pass a text file as input and an output file name as
 * CLI. Open the input file as READ ONLY and open the output
 * file as rw for all modes. Finally, encode each character
 * to it's corresponding ASCII code number and output it to the
 * file. Consider argument number errors and open file errors.
 */
int main(int argc, char** argv) {

    // Create buffer
    char buff[BUFFER_SIZE];
    // Create full path buffer
    char fullpath[120]; // Large in case of abnormally long path
    // For home variable
    char* homedir;

    // Make sure the correct # of args are passed
    if (argc != 3) {
        puts("*** Invalid # of arguments ***");
        return 1; // Returning because the # of arguments passed is invalid
    }

    // No special case, just append directly into fullpath variable
    strcpy(fullpath, argv[1]);

    // Open the first file as READ ONLY
    int readfd = open(fullpath, O_RDONLY);
    // Check if the file opened correctly
    if (readfd == -1) {
        puts("*** Read error ***");
        return 3; // Returning because there was a read error
    }
    // Set the umask to 0 so that specific permissions can be set
    umask(0);
    // Open the second file as rw-rw-rw-
    int writefd = open(argv[2], O_WRONLY | O_CREAT, 0666);
    // Check if the file opened correctly
    if (writefd == -1) {
        puts("*** Write error ***");
        close(readfd);
        return 4; // Returning because there was a write error
    }

    // Create a check byte variable
    int nbyte;
    // Create a char buffer that can be filled when converting the int to ascii
    char fillBuff[3];
    while((nbyte = read(readfd, buff, BUFFER_SIZE)) > 0) {
        if (buff[0] == '\n') {
            break; 
        }
        myAtoItoA(buff[0], fillBuff);
        if (write(writefd, fillBuff, 3) != nbyte) {
            puts("*** Write error ***");
            close(readfd);
            close(writefd);
            return 5; // Returning because there was a write error in the loop
        }
    }
    if (nbyte < 0) {
        puts("*** Read error ***");
        close(readfd);
        close(writefd);
        return 6; // Returning because there was a read error in the loop
    }

    // Close the file descriptors
    close(readfd);
    close(writefd);

    return 0;
}
