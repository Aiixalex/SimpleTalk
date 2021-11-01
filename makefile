TARGET = s-talk
OBJS = s-talk.o list.o message_queue.o input_reader.o

CFLAGS = -Wall -g -D_POSIX_C_SOURCE=199309L
CC = gcc

all: clean $(TARGET)

%.o : %.c
	$(CC) -c $(CFLAGS) $<

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -lpthread

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
