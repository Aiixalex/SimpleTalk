#ifndef _UDP_SERVER_H_
#define _UDP_SERVER_H_

void* UdpRecv(void* message_queue);
void InitUdpServer(List* message_queue, char* my_port);
void ShutDownUdpServer();

#endif