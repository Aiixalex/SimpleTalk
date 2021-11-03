TARGET = s-talk
OBJS = s-talk.o list.o message_queue.o input_reader.o output_writer.o udp_client.o udp_server.o

CFLAGS = -Wall -g -D_POSIX_C_SOURCE=200112L
CC = gcc

all: clean $(TARGET)

%.o : %.c
	$(CC) -c $(CFLAGS) $<

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -lpthread

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
