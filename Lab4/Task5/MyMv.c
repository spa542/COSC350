/*
 * task5.c
 * Ryan Rosiak
 * COSC 350-750
 * 2/25/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard library
#include<fcntl.h> // open()
#include<unistd.h> // read(), write(), link(), unlink()
#include<sys/stat.h> // stat()
#include<string.h> // String functions

/*
 * Create your own mv program using link() and unlink().
 * The two arguments passed are the file name to move, and then
 * either a directory to move it to or a file to copy the contents
 * to and rename
 */
int main(int argc, char** argv) {

    // Check to make sure the arg # is correct
    if (argc != 3) {
        puts("*** Incorrect # of args ***");
        return 1; // Returning because the incorrect # of args was passed
    }

    // Use the struct stat to test if the path's given are files or directories
    struct stat s1;
    struct stat s2;
    // Make sure stat object can be found
    if (stat(argv[1], &s1) != 0) {
        puts("*** Error getting stats for first argument ***");
        return 2; // Returning because the stats could not be obtained from the first arg
    }

    // Make sure the first arg is a regular file
    if (!(s1.st_mode & S_IFREG)) {
        puts("*** First argument must be a file ***");
        return 3; // Returning because the first argument must be a regular file
    }

    if (stat(argv[2], &s2) != 0) {
        // This could happend because
        // a. The stat function could not get the stats of the file for any reason
        // b. The file in the first argument is going to be renamed to the second argument
        if (rename(argv[1], argv[2]) == -1) {
            puts("*** Error renaming file ***");
            return 4; // There was an error renaming the file
        }
        return 0; // Success! the file has been renamed and does not need to go forward
    }

    // Second file can either be a directory or a file
    // Two Cases:
    if (s2.st_mode & S_IFDIR) {
        // First Case: Directory -> Just unlink the file in the current directory and link 
        // the file to the new passed directory
        // Must add the file name appended to the new argument
        char tmpBuffer[80];
        char realBuffer[80];
        int bufferCounter = 0;
        int realCounter = 0;
        int fileNameCounter = strlen(argv[1]) - 1;
        while (argv[1][fileNameCounter] != '/') {
            tmpBuffer[bufferCounter] = argv[1][fileNameCounter]; 
            fileNameCounter--;
            bufferCounter++;
        }
        if (argv[2][strlen(argv[2]) - 1] != '/') {
           realBuffer[realCounter] = '/';
           realCounter++;
        }
        tmpBuffer[bufferCounter] = '\0';
        bufferCounter = strlen(tmpBuffer) - 1;
        while (tmpBuffer[bufferCounter] != '\0') {
            realBuffer[realCounter] = tmpBuffer[bufferCounter];
            bufferCounter--;
            realCounter++;
        }
        realBuffer[realCounter] = '\0';
        char finalString[strlen(argv[2]) + strlen(realBuffer)];
        strcpy(finalString, argv[2]);
        strcat(finalString, realBuffer);

        // Test print
        printf("%s\n", finalString);

        if (link(argv[1], finalString) == -1) {
            puts("*** Error linking file ***");
            return 5; // Returning because there was an error linking the file
        }
        if (unlink(argv[1]) == -1) {
            puts("*** Error unlinking the file ***");
            return 6; // Returning because there was an error unlinking the file
        }
    } else if (s2.st_mode & S_IFREG) {
        // Second Case: Regular File -> rename the file, unlink it, and link to the 
        // path given in the second arg
        // !!!!! This case will only happen if the file that is being "renamed" already exists
        if (rename(argv[1], argv[2]) == -1) {
            puts("*** Error renaming file ***");
            return 7; // Returning because there was an error renaming the file
        }
    } else {
        // This is an error -> The file is not a regular file or a directory
        // or something else weird happened
        puts("*** The second argument is not a regular file or a directory ***");
        return 8; // Returning because the file is not a regular file or directory
    }
    // Done! 

    return 0;
}
