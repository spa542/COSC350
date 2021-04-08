/*
 * twoPipesChild.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/8/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<unistd.h> // read()
#include<string.h> // String Functions

int main(int argc, char** argv) {
    int data_processed;
    int data_processed2;
    char buffer[BUFSIZ + 1];
    const char message[] = "Hi, Mom";
    int file_descriptor;
    int file_descriptor2;
    memset(buffer, '\0', sizeof(buffer));
    sscanf(argv[1], "%d", &file_descriptor);
    sscanf(argv[2], "%d", &file_descriptor2);
    data_processed = read(file_descriptor, buffer, BUFSIZ);
    data_processed2 = write(file_descriptor2, message, strlen(message));
    printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
    printf("%d - wrote %d bytes\n", getpid(), data_processed2);
    exit(EXIT_SUCCESS);
}
