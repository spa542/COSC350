/*
 * task3.c
 * Ryan Rosiak
 * COSC 350-750
 * 3/25/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<unistd.h> // fork(), close(), read(), write()
#include<fcntl.h> // open()
#include<sys/wait.h> // wait()
#include<sys/types.h> // pid_t
#include<string.h> // strlen(), strcpy(), strcat()

/*
 * Write C program in which a child process writes a message "Hi, Mom" to a file
 * named foo. The parent process reads the message and prints it to stdout =>
 * "My son said Hi Mom". The part of the message "Hi Mom" should be gotten
 * from the file foo. Assume that all system calls success. (No need to error
 * check). Use only low-level file operations (fork, wait, open, close, read,
 * write, lseek). You must make sure that the child process terminates first.
 */
int main(void) {

    // Create a spot for saving the id 
    // Create the child
    pid_t myID = fork();
     
    // I am the child
    if (myID == 0) {
        // Create the buffer
        char buff[] = "Hi, Mom";
        // Create the file descriptor and open the file foo
        int fd = open("foo", O_WRONLY | O_CREAT, 0666);
        // Write the specified buffer to the file
        write(fd, buff, strlen(buff));
        // Close the file
        close(fd);
        // All done!
        _exit(0);
    }
    // Parent must wait for the child to be done it's task
    int stat_val = 0;
    int return_pid = wait(&stat_val);

    // Now we need to create a buffer that can contain both the answer
    // from the parent and the string Hi, Mom from the file
    char buff1[] = "My son said ";
    // Create the buffer to read the file
    char tmpBuff[8]; // (size of Hi, Mom)
    
    // Open the file
    int fd = open("foo", O_RDONLY);

    // Read in from the file
    read(fd, tmpBuff, 8);

    // Add the null terminator
    tmpBuff[7] = '\0';

    // Close the file
    close(fd);

    // Start doing some string manipulation to get the messages together
    // Create the final buffer
    char finalBuff[strlen(buff1)+strlen(tmpBuff)+1];
    strcpy(finalBuff, buff1);
    strcat(finalBuff, tmpBuff);
    
    write(1, finalBuff, sizeof(finalBuff));
    puts("");

    return 0;
}
