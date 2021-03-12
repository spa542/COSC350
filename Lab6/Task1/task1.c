/*
 * task1.c Ryan Rosiak
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
    // We don't want to check with $, so if the copy pointer name's first
    // element is a $, then just move it up
    if (name[0] == '$') {
        name++;
    }
    // Counter
    int i = 0;
    // Buffer size of copyBuff
    int bufferSize = 100;
    // Copy buffer for tokenized string
    char copyBuff[bufferSize]; // No environment variable is larger than this
    // Initialize the buffer
    memset(copyBuff, 0, bufferSize);
    // Token
    char token[] = {'='};
    // Return tmp pointer
    char* tmpRtn;
    // Return pointer that will be malloc'd later
    char* rtnPtr;
    // Start loop
    while (envp[i]) {
        // Create the tmp buffer that is the size of string
        char buff[strlen(envp[i])];
        // Copy envp[i] into buff
        strcpy(buff, envp[i]);
        // Tokenize the string by '='
        strtok(buff, token);
        // Copy the buffer into the copyBuff to be compared
        strcpy(copyBuff, buff);
        // Compare the strings
        // strcmp will only compare up to the null terminator => the main argument of copyBuff
        if (strcmp(name, copyBuff) == 0) {
            // Now return the value of that environment variable
            // Get the substring from the original buffer in order to get the value
            // Get the original string to be manipulated
            char tmpBuff[strlen(envp[i])];
            strcpy(tmpBuff, envp[i]);
            // Set the pointer to the right spot
            tmpRtn = strstr(tmpBuff, "=");
            // Increment once to exclude the '='
            tmpRtn++;
            // Now copy that substring into a variable to be returned
            rtnPtr = (char*)malloc((strlen(tmpRtn)+1)*sizeof(char)); 
            strcpy(rtnPtr, tmpRtn);

            // NOTE: Make sure to free later
            return rtnPtr; // Return the value of that environment variable
        }
        // Reset buffer and move to next iteration of the loop 
        memset(copyBuff, 0, bufferSize); 
        i++;
    }

    // If we dont find anything just return NULL
    return NULL;
}

/*
 * Write your own getenv() function called mygetenv() which has the same
 * syntax and semantics.
 * Write a simple c program to show that mygetenv() works well.
 */
int main(int argc, char** argv, char** envp) {

    // Print all of the environment variables for testing
    int i = 0;
    while(envp[i]) {
        printf("%s\n", envp[i]);
        i++;
    }

    // Call mygetenv()
    char* myEnv1 = mygetenv("$HOME", envp);
    char* myEnv2 = mygetenv("$PWD", envp);
    char* myEnv3 = mygetenv("LS_COLORS", envp); // Notice you can call with or without $
    char* myEnv4 = mygetenv("YEET", envp); // NOTE: This is not an environment variable

    // Print out results
    printf("Your $HOME environment variable is: %s\n", myEnv1);

    printf("Your $PWD environment variable is: %s\n", myEnv2);

    printf("Your $LS_COLORS environment variable is: %s\n", myEnv3);

    printf("Your YEET environment variable is: %s\n", myEnv4);


    // Free those pointers at the end
    free(myEnv1);
    free(myEnv2);
    free(myEnv3);
    free(myEnv4);

    return 0;
}
