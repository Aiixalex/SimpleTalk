#ifndef _OUTPUT_WRITER_H_
#define _OUTPUT_WRITER_H_

#include "../utils/list.h"

void* WriteOutput(void* message_queue);
void SignalOutputWriter();
void InitOutputWriter(List* message_queue);
void ShutDownOutputWriter();
void CancelOutputWriter();

#endif