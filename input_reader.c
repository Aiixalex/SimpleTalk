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

#define MAXBUFSIZE 4096

static pthread_t input_reader_thread;

void* process_input(void* message_queue) {
    char buf[MAXBUFSIZE];
    int buf_size = 0;
    char* message;

    do {
        memset(&buf, 0, MAXBUFSIZE);
        buf_size = read(STDIN_FILENO, buf, MAXBUFSIZE);
        if (buf_size == -1) {
            handle_error("Input function read() fails");
        }

        message = malloc((buf_size + 1) * sizeof(char));
        strncpy(message, buf, buf_size); // a null byte is written by strncpy() to message[buf_size]
        printf("%d %d\n", message[buf_size-1] == '\n', buf[buf_size] == '\0');

        if (message_enqueue(message_queue, message) != LIST_FAIL) {
            fprintf(stderr, "My message enqueue fails: %s", message);
        }

        printf("%d %s", buf_size, buf);
    } while (strcmp(message, "!\n") != 0);

    return NULL;
}

void init_input_reader(void* message_queue) {
    int error_num = pthread_create(&input_reader_thread, NULL, &process_input, message_queue);
    if (error_num != 0) {
        handle_error_en(error_num, "pthread_create");
    }
}

void input_reader_shut_down() {
    int error_num = pthread_join(input_reader_thread, NULL);
    if (error_num != 0) {
        handle_error_en(error_num, "pthread_join");
    }
}