/*
 * task5.c
 * Ryan Rosiak
 * COSC 350-750
 * 3/11/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<unistd.h> // fork(), exec()
#include<sys/types.h> // pid_t, getpid()
#include<sys/wait.h> // wait()

/*
 * Write a c program that receives an input file name as an 
 * argument and op[ens the file for input. Then, create a child 
 * process. The input file must open only once and the file descriptor
 * will be shared by the parent and child process. Bothe parent and the
 * child will read one byte at a time from the input file and write
 * output to independent files (parent.txt and child.txt). The parent
 * process collects numeric characters and the child collects non-numeric
 * characters. Without any form of synchronization, the parent and child will
 * create wrong output files.
 * Modify the program to synchronize and get correct output for each process.
 * **Do not open the input file twice for synchronization
 * **Define your own function to check if the character is numeric
 * **Do not use vfork(), sleep(), wait(), or waitpid() for synchronization
 * **Check all possible errors for system calls
 */
int main(int argc, char** argv) {



    return 0;
}
