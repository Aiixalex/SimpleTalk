#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include <errno.h>

#include "list.h"
#include "input_reader.h"
#include "message_queue.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Arguments of s-talk should in format of:\n./s-talk [my port number] [remote machine name] [remote port number]\n");
        return -1;
    }

    char* my_port = argv[1];
    char* remote_name = argv[2];
    char* remote_port = argv[3];

    List* message_queue = List_create();

    init_input_reader(message_queue);

    List_free(message_queue, free);
}