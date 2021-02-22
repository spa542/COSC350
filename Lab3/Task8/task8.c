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
    bool isNum = true;
    for (i = 0; num[i] != '\0'; i++) {
        // Check each character to make sure it is a valid number
        if (num[i] < '0' || num[i] > '9') {
            // If invalid, isNum will be false
            isNum = false;
            break;
        }
        result = result * 10 + num[i] - '0';
    }
    // If the loop states the the number is not a number,
    // return -1 -> This will be handled in the calling process
    if (!isNum) {
        return -1;
    }
    return result;
}

/*
 * Pass a text file as input and an output file name as
 * CLI. Open the input file as READ ONLY and open the output
 * file as rw for all modes. Finally, encode each character
 * to it's corresponding ASCII code number and output it to the
 * file. Consider argument number errors and open file errors.
 * Use custom atoi function from previous task.
 */
int main(int argc, char** argv) {

    return 0;
}
