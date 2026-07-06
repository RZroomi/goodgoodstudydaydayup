CC=gcc
TARGET=app
MODE ?=debug

SRC :=$(wildcard *.c)
OBJ :=$(patsubst %.c,%.o,$(SRC))

ifeq ($(MODE), debug)
    CFLAGS := -Wall -g -DDEBUG
else ifeq ($(MODE), release)
    CFLAGS := -Wall -O2	
endif

all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f $(TARGET) *.o


