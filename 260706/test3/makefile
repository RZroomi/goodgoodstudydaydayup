C=gcc
CFLAGS=-Wall -g
TARGET=app

SRC :=$(wildcard *.c)
OBJ :=$(patsubst %.c,%.o,$(SRC))


all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f $(TARGET) *.o


