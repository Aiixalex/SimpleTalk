#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include <errno.h>
#include <pthread.h>

#include "list.h"
#include "message_queue.h"
#include "handle_error.h"
#include "udp_client.h"
#include "udp_server.h"
#include "output_writer.h"

#define MAXBUFSIZE 4096

static pthread_t input_reader_thread;

void* ReadInput(void* message_queue) {
    char buf[MAXBUFSIZE];
    int buf_size = 0;

    while (1) {
        memset(&buf, 0, MAXBUFSIZE);
        buf_size = read(STDIN_FILENO, buf, MAXBUFSIZE);
        if (buf_size == -1) {
            handle_error("Input function read() failed");
        }

        char* message = malloc((buf_size + 1) * sizeof(char));
        strncpy(message, buf, buf_size); // a null byte is written by strncpy() to message[buf_size]

        if (MessageEnqueue(message_queue, message) == LIST_FAIL) {
            fprintf(stderr, "message enqueue failed: %s", message);
        }

        if (strcmp(message, "!\n") == 0) {
            SignalUdpClient();
            CancelUdpServer();
            CancelOutputWriter();
            return NULL;
        }

        SignalUdpClient();
    }

    return NULL;
}

void InitInputReader(List* message_queue) {
    int error_num = pthread_create(&input_reader_thread, NULL, &ReadInput, message_queue);
    if (error_num != 0) {
        handle_error_en(error_num, "pthread_create input_reader_thread failed.");
    }
}

void ShutDownInputReader() {
    int error_num = pthread_join(input_reader_thread, NULL);
    if (error_num != 0) {
        handle_error_en(error_num, "pthread_join input_reader_thread failed.");
    }
}

void CancelInputReader() {
    int error_num = pthread_cancel(input_reader_thread);
    if (error_num != 0) {
        handle_error_en(error_num, "pthread_cancel input_reader_thread failed.");
    }
}