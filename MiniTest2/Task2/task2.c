#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<stdbool.h>

int st_to_int(char* num) {
    // Subtract the ASCII 0 from each digit and then multiply by each
    // decimal place to get out number back
    int i, result = 0;
    bool isNum = true, isNegative = false;
    for (i = 0; num[i] != '\0'; i++) {
        // Check to see if they input a negative number
        if (num[i] == '-' && i == 0) {
            isNegative = true;
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
    // Convert to a negative number if the argument is passed as negative
    if (isNegative) {
        result *= -1;
    }
    // If the loop states the the number is not a number,
    // return -0 -> This will be handled in the calling process
    if (!isNum) {
        return -0;
    }
    return result;
}

void printSum(int argc, char** argv) {
    // Declare the counter and initialize the sum
    int i, j, sumEven = -1, sumOdd = -1, check;
    bool isFirstRealNum = true;
    // Loop through the strings and the chars
    for (i = 1; i < argc; i++) {
        // Need to check if the argument is a valid integer
        if ((check = st_to_int(argv[i])) != -0) {
            if (isFirstRealNum) {
                isFirstRealNum = false;
                sumEven = 0;
                sumOdd = 0;
            }
            if (check % 2 == 0) {
                sumEven += check;
            } else {
                sumOdd += check;
            }
        }
    }
    // isFirstRealNum should be false if we convert at least ONE real number
    // from ASCII to integer
    if (isFirstRealNum) {
        puts("*** There is not at least one integer on the command line. ***");
    } else {
        printf("Sum of even numbers: %d\n", sumEven);
        printf("Sum of odd numbers: %d\n", sumOdd);
    }
}

int main(int argc, char** argv) {

    // Make sure the argument count is correct
    if (argc < 2) {
        puts("*** Invalid # of args ***");
        return 1; // Return because the number of arguments was incorrect
    }

    // Print the sum of the digits of the argument
    printSum(argc, argv);

    return 0;
}
