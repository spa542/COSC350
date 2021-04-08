/*
 * twoPipesParent.c
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
    int data_processed2;
    int file_pipes[2];
    int file_pipes2[2];
    const char some_data[] = "Hi there, Kiddo";
    char some_return_data[BUFSIZ + 1];
    char buffer[BUFSIZ + 1];
    char buffer2[BUFSIZ + 1];
    pid_t fork_result;
    memset(buffer, '\0', sizeof(buffer));
    memset(buffer2, '\0', sizeof(buffer2));
    memset(some_return_data, '\0', sizeof(some_return_data));
    if ((pipe(file_pipes) == 0) && (pipe(file_pipes2) == 0)) {
        fork_result = fork();
        if (fork_result == (pid_t)-1) {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }
        if (fork_result == 0) {
            close(file_pipes[1]);
            close(file_pipes2[0]);
            sprintf(buffer, "%d", file_pipes[0]);
            sprintf(buffer2, "%d", file_pipes2[1]);
            // Pass the write end of the pipe to the child as a cli
            (void)execl("twoPipesChild", "twoPipesChild", buffer, buffer2, (char *)0);
            exit(EXIT_FAILURE);
        }
        else {
            close(file_pipes[0]);
            close(file_pipes2[1]);
            data_processed = write(file_pipes[1], some_data, strlen(some_data));
            data_processed2 = read(file_pipes2[0], some_return_data, BUFSIZ);
            printf("%d - wrote %d bytes\n", getpid(), data_processed);
            printf("%d - read %d bytes: %s\n", getpid(), data_processed2, some_return_data);
        }
    }
    exit(EXIT_SUCCESS);
}
