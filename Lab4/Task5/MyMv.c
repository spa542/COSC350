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

    /*
    // Make sure stat object can be found
    if (stat(argv[2], &s2) != 0) {
        puts("*** Error getting stats for second argument ***");
        return 4; // Returning because the stats could not be obtained from the second arg
    }
    */

    // Second file can either be a directory or a file
    // Two Cases:
    if (s2.st_mode & S_IFDIR) {
        // First Case: Directory -> Just unlink the file in the current directory and link 
        // the file to the new passed directory
        if (link(argv[1], argv[2]) == -1) {
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
        if (rename(argv[1], argv[2]) == -1) {
            puts("*** Error renaming file ***");
            return 7;
        }
    } else {
        // This is an error -> The file is not a regular file or a directory
        puts("*** The second argument is not a regular file or a directory ***");
        return 8; // Returning because the file is not a regular file or directory
    }
    // Done! 

    return 0;
}
