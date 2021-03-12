/*
 * task1.c
 * Ryan Rosiak
 * COSC 350-750
 * 3/11/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<string.h> // String functions

/*
 * mygetenv Function:
 * This functon will take a string parameter which is the name of
 * the environment variable and the function will return the value
 * of the environement variable
 */
char *mygetenv(const char* name, char** envp) {
    
    int i = 0;
    /*
    while (envp[i]) {
        // Compare each string path to each string environment variable 
        if (strcmp(name, envp[i]) == 0) {
            return envp[i];
        }
    }
    */
    // Test print
    while (envp[i]) {
        printf("%s\n", envp[i]);
        i++;
    }

    return NULL;
}

/*
 * Write your own getenv() function called mygetenv() which has the same
 * syntax and semantics.
 * Write a simple c program to show that mygetenv() works well.
 */
int main(int argc, char** argv, char** envp) {

    // Call mygetenv()
    char* myEnv = mygetenv("$HOME", envp);

    printf("Your $HOME path variable is: %s\n", myEnv);


    return 0;
}
