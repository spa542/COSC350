/*
 * task3.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/1/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<unistd.h> // pipe()
#include<sys/types.h> // pid_t

/*
 * A parent process asks for two integers from the command line and 
 * sends them to the child by using a pipe. The chiild process makes sure
 * that the two inputs are valid integers. The child process then calculates
 * the sum of the two integers and outputs them to standard output. The child
 * process process continues until input from the parent is EOF.
 */
int main(int argc, char** argv) {

    return 0;
}
