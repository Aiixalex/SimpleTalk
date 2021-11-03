#ifndef _INPUT_READER_H_
#define _INPUT_READER_H_

#include "list.h"

void ReadInput(void* message_queue);
void InitInputReader(List* message_queue);
void ShutDownInputReader();

#endif