/*
 * task4.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/1/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<unistd.h> // pipe(), popen(), pclose()
#include<sys/types.h> // pid_t

/*
 * Use popen() to create a child and a pipe. The parent rprocess asks for two
 * arguments from the command line (a shell command and a file name). Then,
 * the the parent will send the data to the child using popen(). The child
 * prcoess will implement the command with file as an input and then send
 * to the parent. The parent simply must then display output from the child 
 * on standard output.
 */
int main(int argc, char** argv) {

    return 0;
}
