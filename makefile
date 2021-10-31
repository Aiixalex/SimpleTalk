TARGET = test
OBJS = test.o list.o

CFLAGS = -Wall -g -D_POSIX_C_SOURCE=199309L
CC = gcc

all: clean $(TARGET)

%.o : %.c
	$(CC) -c $(CFLAGS) $<

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
