#ifndef _OUTPUT_WRITER_H_
#define _OUTPUT_WRITER_H_

#include "list.h"

void* WriteOutput(void* message_queue);
void SignalOutputWriter();
void InitOutputWriter(List* message_queue);
void ShutDownOutputWriter();

#endif