#ifndef _MESSAGE_QUEUE_UTILS_H_
#define _MESSAGE_QUEUE_UTILS_H_

#include "list.h"

int message_enqueue(List* list, char* message);
char* message_dequeue(List* list);
int get_message_queue_size(List* list);

#endif