/*
 * msgQsnd.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/22/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<sys/msg.h> // Message Queue Stuff
#include<sys/types.h> // Types
#include<unistd.h> // read()
#include<string.h> // sscanf()
#include<sys/ipc.h> // IPC Stuff

#define BUFFER_SIZE 80

typedef struct my_msgbuff {
    long mtype;
    int buff[2];
} msgbuff;

/*
 * Create message queue with rw-r-r. To create a message queue, use existing 
 * file name "msgQsnd.c" for creating a key value.
 * Ask a message for two integer values and send to the message queue.
 * Keep asking for a message until EOF (CTR-D).
 * Remove the message queue with termination.
 */
int main(void) {

    // Message queue id
    int msqid;
    // Integer variables to send to the queue
    int sendBuff[2];
    // Key value
    key_t key;
    // Read buffer
    char buffer[BUFFER_SIZE];
    // Byte check
    int nbyte;
    // Check
    int check;
    // Message buffer
    msgbuff send;

    // Get the key for the message queue
    if ((key = ftok("msgQsnd.c", 'B')) == -1) {
        puts("*** Error tokenizing the file ***");
        return 1; // Returning because there was an error tokenizing the file
    }

    // Create the message queue
    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        puts("*** Error creating the message queue ***");
        return 2; // Returning because there was an error creating the message queue
    }

    // Read from the user until CTR-D
    while ((nbyte = read(0, buffer, BUFFER_SIZE)) > 0) {
        if (sscanf(buffer, "%d%d", &sendBuff[0], &sendBuff[1]) == 2) {
            send.mtype = 1;
            send.buff[0] = sendBuff[0];
            send.buff[1] = sendBuff[1];
            if ((check = msgsnd(msqid, (msgbuff*)&send, sizeof(send), 0)) == -1) {
                puts("*** Error sending message ***");
            }
        } else {
            puts("*** Invalid inputs (must be two integers) ***");
        }
    }

    // Remove the message queue
    if ((check = msgctl(msqid, IPC_RMID, NULL)) == -1) {
        puts("*** Error removing the message queue ***");
        return 3; // Returning because there was an error removing the message queue
    }

    // All done!
    return 0;
}
