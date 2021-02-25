/*
 * task2.c
 * Ryan Rosiak
 * COSC 350-750
 * 2/25/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<fcntl.h> // open()
#include<unistd.h> // lseek(), read()
#include<string.h> // String functions
#include<ctype.h> // isdigit()
#include<stdbool.h> // bool alias

#define BUFFER_SIZE 81

/*
 * convIntToStr() Function:
 * Converts an int to a string using standard I/O
 * Returns the length of the string
 */
int convIntToStr(char* str, int x) {
    sprintf(str, "%d\n", x);
    return (strlen(str));
}

/*
 * myAtoI Function:
 * Converts an ASCII number to a decimal value while
 * checking to see if the converted ASCII number is a 
 * valid decimal number
 */
int myAtoI(char* num) {
    // Subtract the ASCII 0 from each digit and then multiply by each
    // decimal place to get out number back
    int i, result = 0;
    bool isNum = true, isNegative = false;
    for (i = 0; num[i] != '\0'; i++) {
        result = result * 10 + num[i] - '0';
    }
    return result;
}

/*
 * Write a C-Program that takes one command line argument, the name
 * of the input file. The input file contains exactly one integer spread
 * out over a single line of up to 80 characters. Open and read the input
 * file, accumulating the integers into a character array. Add 10 to the 
 * integer, and convert the sum back to a string using convIntToStr. Write
 * the string to standard output using a system call.
 */
int main(int argc, char** argv) {

    // Check to see if argument # is correct
    if (argc != 2) {
        puts("*** Invalid # of arguments ***");
        return 1; // Returning because the # of arguments is incorrect
    }

    // Create the file descriptor variable
    int infd;
    // Create the number buffer
    char numBuff[BUFFER_SIZE];
    // Create the read-in buffer
    char readBuff[BUFFER_SIZE];

    // Open the file
    infd = open(argv[1], O_RDONLY);
    if (infd == -1) {
        puts("*** Error opening the file ***");
        return 2; // Returning because there was an error opening the file
    }
    
    // Read error check variable
    int nbyte;
    // Read in up to 80 chars in the file
    if ((nbyte = read(infd, readBuff, BUFFER_SIZE)) == -1) {
        puts("*** Read error ***");
        close(infd);
        return 3; // Returning because there was a read error
    }

    // Counter for numBuff
    int counter = 0;
    int i; // Variable counter
    for (i = 0; readBuff[i] != '\0'; i++) {
        // Using isdigit to check if the char is a digit or not
        if (isdigit(readBuff[i])) {
            // Enter into the numBuff string and increment the outer counter
            numBuff[counter] = readBuff[i];
            counter++;
        }
    }
    numBuff[counter] = '\0'; // Append the null terminator to the end
    counter++; // This is now the length of the number that was read in

    // Print out the found string so it can be compared with the 
    // final output
    printf("String found: %s\n", numBuff);

    // Now convert the string to an integer
    int converted = myAtoI(numBuff);

    // Add 10 to the integer
    converted += 10;

    // Create a new buffer to hold the integer that will be converted
    // to a string
    char newStringBuff[BUFFER_SIZE];
    // Convert the ingeger to a string and get the length of it back
    int lengthOfNSB = convIntToStr(newStringBuff, converted);

    // Use a system call to write the string to standard output
    write(1, newStringBuff, lengthOfNSB);

    // Close the file descriptor
    close(infd);

    return 0;
}
