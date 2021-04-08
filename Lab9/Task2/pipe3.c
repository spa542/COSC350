/*
 * pipe3.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/8/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<unistd.h> // fork(), pipe()
#include<string.h> // String Functions
#include<sys/wait.h> // wait()
#include<sys/types.h> // pid_t

int main(void) {
    int data_processed;
    int file_pipes[2];
    const char some_data[] = "123";
    char buffer[BUFSIZ + 1];
    pid_t fork_result;
    memset(buffer, '\0', sizeof(buffer));
    if (pipe(file_pipes) == 0) {
        fork_result = fork();
        if (fork_result == (pid_t)-1) {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }
        if (fork_result == 0) {
            // Close the file descriptor of the read end of the pipe on the
            // child's side
            close(file_pipes[0]);
            sprintf(buffer, "%d", file_pipes[1]);
            // Pass the write end of the pipe to the child as a cli
            (void)execl("pipe4", "pipe4", buffer, (char *)0);
            exit(EXIT_FAILURE);
        }
        else {
            int stat_val;
            // Close the file descriptor of the write end of the pipe on the
            // parent's side
            close(file_pipes[1]); 
            // Have the parent wait for the child
            pid_t return_val = wait(&stat_val);
            data_processed = write(file_pipes[1], some_data, strlen(some_data));
            printf("%d - wrote %d bytes\n", getpid(), data_processed);
        }
    }
    exit(EXIT_SUCCESS);
}
