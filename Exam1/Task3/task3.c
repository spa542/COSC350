#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>

#define BUFFER_SIZE 81

int findNumOfDigits(int num) {
    int count = 0;

    num = num / 10;
    while (num != 0) {
        num = num / 10;
        count++;
    }
    count++;
    return count;
}

char *int_to_str(int num) {
    // Subtract the ASCII 0 from each digit and then multiply by each
    // decimal place to get out number back
    int asciiInt = 0;
    asciiInt = num - '\0';
    int numDigits = findNumOfDigits(num);

    char* buffer = (char*)malloc(numDigits*sizeof(char));
    memset(buffer, 0, numDigits);

    int i = numDigits - 1;
    while (asciiInt != 0) {
        buffer[i--] = asciiInt % 10 + '0';
        asciiInt /= 10;
    }

    return buffer;
}

int str_to_int(char* num) {
    // Subtract the ASCII 0 from each digit and then multiply by each
    // decimal place to get out number back
    int i, result = 0;
    for (i = 0; num[i] != '\0'; i++) {
        result = result * 10 + num[i] - '0';
    }
    return result;
}

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
    // Set the buffer so no weird conditional jumps
    memset(readBuff, 0, BUFFER_SIZE);

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
        if (readBuff[i] >= '0' && readBuff[i] <= '9') {
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
    int converted = str_to_int(numBuff);

    // Add 100 to the integer
    converted += 100;

    // Convert the string to an integer
    char* finalString = int_to_str(converted);
    // Find the num of digits so that we can write it to standard output
    int numOfDigits = findNumOfDigits(converted);

    // Use a system call to write the string to standard output
    write(1, finalString, numOfDigits);
    puts("");

    // Close the file descriptor
    close(infd);
    // Make sure to clear the memory
    free(finalString);

    return 0;
}
