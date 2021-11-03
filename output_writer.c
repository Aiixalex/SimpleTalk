#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#include "list.h"
#include "message_queue.h"
#include "handle_error.h"

static pthread_t output_writer_thread;
static pthread_mutex_t output_writer_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t output_writer_cond = PTHREAD_COND_INITIALIZER;

void* WriteOutput(void* message_queue) {
    while(1) {
        pthread_mutex_lock(&output_writer_mutex);
        pthread_cond_wait(&output_writer_cond, &output_writer_mutex);
        pthread_mutex_unlock(&output_writer_mutex);

        char* message = message_dequeue(message_queue);
        if (message == NULL) {
            fprintf(stderr, "message dequeue failed.");
            continue;
        }

        int msg_size = write(STDOUT_FILENO, message, strlen(message));
        if(msg_size == -1) {
            handle_error("Output function write() failed.");
        }

        if(strcmp(message, "!\n") == 0) {
            free(message);
            return NULL;
        }

        free(message);
    }
    return NULL;
}

void SignalOutputWriter() {
    pthread_mutex_lock(&output_writer_mutex);

    pthread_cond_signal(&output_writer_cond);

    pthread_mutex_unlock(&output_writer_mutex);
}

void InitOutputWriter(List* message_queue) {
    int error_num = pthread_create(&output_writer_thread, NULL, &WriteOutput, message_queue);
    if (error_num != 0) {
        handle_error_en(error_num, "pthread_create output_writer_thread failed.");
    }
}

void ShutDownOutputWriter() {
    int error_num = pthread_join(output_writer_thread, NULL);
    if (error_num != 0) {
        handle_error_en(error_num, "pthread_join output_writer_thread failed.");
    }
}

void CancelOutputWriter() {
    int error_num = pthread_cancel(output_writer_thread);
    if (error_num != 0) {
        handle_error_en(error_num, "pthread_cancel output_writer_thread failed.");
    }
}