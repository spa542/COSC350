/*
 * task7.c
 * Ryan Rosiak
 * COSC 350-750
 * 2/22/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard library
#include<string.h> // String functions
#include<stdbool.h> // bool alias

/*
 * myAtoI Function:
 * Converts an ASCII number to a decimal value while
 * checking to see if the converted ASCII number is a 
 * valid decimal number
 */
int myAtoI1(char* num) {
    // Subtract the ASCII 0 from each digit and then multiply by each
    // decimal place to get out number back
    int i, result = 0;
    bool isNum = true;
    for (i = 0; num[i] != '\0'; i++) {
        // Check to see if they input a negative number
        if (num[i] == '-' && i == 0) {
            continue;
        }
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
 * myAtoI2 Function:
 * Converts a single character to it's integer representation
 */
int myAtoI2(char item) {
    // Check to see if the char is a valid number
    if (item < '0' || item > '9') {
        return -1;
    }
    // Subtract the ASCII 0 from the number and then return 
    // it's integer value converted
    return (int)(item - '0');   
}

/*
 * printSum1 Function:
 * Loops through the arguments from the command line,
 * converts their integer value, and then prints the summed
 * result of all of the numbers to the screen
 */
void printSum1(int argc, char** argv) {
    // Declare the counter and initialize the sum
    int i, j, sum = -1, check;
    bool isFirstRealNum = true;
    // Loop through the strings and the chars
    for (i = 1; i < argc; i++) {
        // Need to check if the argument is a valid integer
        if ((check = myAtoI1(argv[i])) != -1) {
            if (isFirstRealNum) {
                isFirstRealNum = false;
                sum = 0;
            }
            sum += check;
        }
    }
    // isFirstRealNum should be false if we convert at least ONE real number
    // from ASCII to integer
    if (isFirstRealNum) {
        puts("*** There is not at least one integer on the command line. ***");
    } else {
        printf("Sum: %d\n", sum);
    }
}

/*
 * printSum2 Function:
 * This function will take one argument and convert it to 
 * an integer and then sum the digits and print the sum
 */
void printSum2(char* arg) {
    // Create some counter variables
    int i, sum = 0, check;
    // Convert using myAtoI
    for (i = 0; i < strlen(arg); i++) {
        check = myAtoI2(arg[i]);
        // Check to make sure myAtoI says that the number is valid
        if (check == -1) {
            puts("*** There is not at least one integer on the command line. ***");
            return; // Leave the function early
        } else {
            sum += check;
        }
    }
    printf("Sum: %d\n", sum);
}

/*
 * Write a program to receive a sequence of integers on the
 * command line and print the sum of the digits to the screen.
 * DEFINE your own atoi() function
 */
int main(int argc, char** argv) {

    // Make sure the argument count is correct
    if (argc != 2) {
        puts("*** Invalid # of args ***");
        return 1; // Return because the number of arguments was incorrect
    }

    // This is for the other way that the question was interpreted
    //printSum1(argc, argv);
    // Print the sum of the digits of the argument
    printSum2(argv[1]);

    return 0;
}
