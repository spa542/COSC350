/*
 * msgQrcv.c
 * Ryan Rosiak
 * COSC 350-750
 * 4/22/21
 */
#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard Library
#include<sys/msg.h> // Message Queue Stuff
#include<sys/types.h> // Types
#include<sys/ipc.h> // IPC Stuff
#include<stdbool.h> // bool alias

#define BUFFER_SIZE 2

typedef struct my_msgbuff {
    long mtype;
    int buff[2];
} msgbuff;

/*
 * Receive a message (two integers) from the message queue created by msgQsnd.c
 * Calculate the sum of the two integers and display the result to 
 * standard output. Keep reading messages untl EOF.
 */
int main(void) {

    // Key value
    key_t key;
    // Message queue id
    int msqid;
    // Receive buffer
    int rcvBuff[BUFFER_SIZE];
    // Check byte
    int nbyte;
    // Check
    int check;
    // Get the msgid_ds structure
    struct msqid_ds data;
    // Receive
    msgbuff rcv;

    // Tokenize the message queue
    if ((key = ftok("msgQsnd.c", 'B')) == -1) {
        puts("*** Error tokenizing the message queue ***");
        return 1; // Returning because there was an error tokenizing the message queue
    }

    // Get the message queue
    if ((msqid = msgget(key, 0644)) == -1) {
        puts("*** Error getting the message queue ***");
        return 2; // Returning because there was an error getting the message queue
    }

    // Get the messages from the message queue
    while (true) {
        if ((check = msgrcv(msqid, (msgbuff*)&rcv, sizeof(rcv), 0, 0)) == -1) {
            puts("*** Error receiving the message ***");
            return 4; // Returning because there was an error receiving the message
        }
        printf("%d + %d = %d\n", rcv.buff[0], rcv.buff[1], rcv.buff[0]+rcv.buff[1]);
    }

    // All done!
    return 0;
}
