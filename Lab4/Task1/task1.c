/*
 * task1.c
 * Ryan Rosiak
 * COSC 350-750
 * 2/25/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard library
#include<unistd.h> // read(), write()
#include<fcntl.h> // open()
#include<string.h> // String functions

/*
 * myAtoI Function:
 * Converts an ASCII number to a decimal value
 * with a given buffer size
 */
int myAtoI(char* num, int buffSize) {
    // Subtract the ASCII 0 from each digit and then multiply by each
    // decimal place to get out number back
    int i, result = 0;
    for (i = 0; i < buffSize; i++) {
        result = result * 10 + num[i] - '0';
    }
    return result;
}

/*
 * Use the output from Task 8 in lab 3 as input for this program.
 * Decode the encoded file by converting all of the ascii numbers in the file
 * to their original char and output the original file back
 */
int main(int argc, char** argv) {
    
    // Check to make sure the # of args is correct
    if (argc != 3) {
        puts("*** Invalid # of args ***");
        return 1; // Returning because the # of args is incorrect
    }

    // Input file descriptor
    int infd;
    // Output file descriptor
    int outfd;

    // Open the first file for reading
    infd = open(argv[1], O_RDONLY);
    // Check to make sure the file opened correctly
    if (infd == -1) {
        puts("*** Error opening the first file ***");
        return 2; // Returning because there was an error opening the first file
    }
    // Open the second file for writing
    outfd = open(argv[2], O_CREAT | O_WRONLY, 0666);
    // Check to make sure the file was created/opened correctly
    if (outfd == -1) {
        puts("*** Error opening/creating the second file ***");
        close(infd);
        return 3; // Returning because there was an error opening/reading the second file
    }

    // Create the read buffer
    char readBuff[1];
    // Create the number buffer
    char numBuff[3];
    // Zero out the buffer
    memset(numBuff, 0, 3);
    // Create endline buffer
    char endlineBuff[] = {'\n'};
    // Create the write buff
    char writeBuff[1];
    // Read byte
    int nbyte;
    // numbuff counter
    int counter = 0;
    // Temp conversion int
    int temp; 
    // Start reading the file
    while ((nbyte = read(infd, readBuff, 1)) > 0) {
        if (readBuff[0] == ' ') {
            // Convert the buffer to an integer
            temp = myAtoI(numBuff, counter); 
            // Convert the integer to a char
            writeBuff[0] = (char)temp; 
            // Write that char to a file
            if (write(outfd, writeBuff, 1) != 1) {
                puts("*** Write Error ***");
                close(infd);
                close(outfd);
                return 4; // Returning because there was an error writing to the file
            }
            // Reset buffer and counter
            memset(numBuff, 0, 3);
            counter = 0;
        } else if (readBuff[0] == '\n') {
            if (write(outfd, endlineBuff, 1) != 1) {
                puts("*** Write error ***");
                close(infd);
                close(outfd);
                return 5; // Returning because there was a write error
            }
        } else {
            numBuff[counter++] = readBuff[0];
        }
    }
    if (nbyte == -1) {
        puts("*** Read error ***");
        close(infd);
        close(outfd);
        return 6; // Returning because there was a read error
    }

    // Close the files
    close(infd);
    close(outfd);

    return 0;
}
