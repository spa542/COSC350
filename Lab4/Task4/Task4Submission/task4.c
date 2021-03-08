/*
 * task4.c
 * Ryan Rosiak
 * COSC 350-750
 * 2/25/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard library
#include<unistd.h> // Macros
#include<sys/stat.h> // mkdir(), symlink()

/*
 * Create the directory structure from the pdf. Copy hello file under 
 * ~/Dir2/Dir21/. Make a symbolic link named toDir21 to directory Dir21.
 * Make a symbolic link named toHello to executable file ~/Dir21/hello.
 * Lastly, execute hello by using the symbolic link toHello. Try to delete 
 * a file and make a directory by using symbolic link to toDir21
 */
int main(void) {

    // Make the directory structure as stated in the lab
    if (mkdir("~/Dir1", S_IRWXU) == -1) {
        puts("*** Error creating the first directory ***");
        return 1; // Returning because the first directory couldnt be made
    }
    if (mkdir("~/Dir2", S_IRWXU) == -1) {
        puts("*** Error creating the second directory ***");
        return 2; // Returning because the second directory couldnt be made
    }
    if (mkdir("~/Dir2/Dir21", S_IRWXU) == -1) {
        puts("*** Error creating the third directory ***");
        return 3; // Returning because the third directory couldnt be made
    }
    // Move the hello executable file to the Dir21 directory
    if (rename("./hello", "~/Dir2/Dir21/hello") == -1) {
        puts("*** Error copying the file over the Dir21 directory ***");
        return 4; // Returning because the file did not get copied over correctly
    }
    // Make a symbolic link to Dir21 called toDir21
    // !!! symlink creates a link from the second parameter to the first parameter
    if (symlink("~/Dir2/Dir21", "~/Dir1/toDir21") == -1) {
        puts("*** Error creating the first symlink ***");
        return 5; // Returning because the first symlink could not be made
    }
    if (symlink("~/Dir2/Dir21/hello", "~/Dir1/toHello") == -1) {
        puts("*** Error creating the second symlink ***");
        return 6; // Returning because the second symlink could not be made
    }

    return 0;
}
