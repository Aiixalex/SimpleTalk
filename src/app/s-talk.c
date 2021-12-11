#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include <errno.h>

#include "../io/input_reader.h"
#include "../io/output_writer.h"
#include "../utils/list.h"
#include "../utils/message_queue.h"

#include "../client/udp_client.h"
#include "../server/udp_server.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Arguments of s-talk should in format of:\n./s-talk [my port number] [remote machine name] [remote port number]\n");
        return -1;
    }

    char* my_port = argv[1];
    char* remote_name = argv[2];
    char* remote_port = argv[3];

    List* input_queue = List_create();
    List* output_queue = List_create();

    InitInputReader(input_queue);
    InitUdpClient(input_queue, remote_name, remote_port);
    InitUdpServer(output_queue, my_port);
    InitOutputWriter(output_queue);

    ShutDownInputReader();
    ShutDownUdpClient();
    ShutDownUdpServer();
    ShutDownOutputWriter();

    List_free(input_queue, free);
    List_free(output_queue, free);
}