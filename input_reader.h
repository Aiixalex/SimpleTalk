#ifndef _INPUT_READER_H_
#define _INPUT_READER_H_

#include "list.h"

void process_input(void* message_queue);
void init_input_reader(void* message_queue);
void input_reader_shut_down();

#endif