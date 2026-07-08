CC=gcc
MODE ?=DEBUG

SRC :=$(wildcard *.c)
OBJ :=$(patsubst %.c,%.o,$(SRC))

ifeq ($(MODE), DEBUG)
    CFLAGS := -Wall -g -DDEBUG
else ifeq ($(MODE), release)
    CFLAGS := -Wall -g -O2 
endif
	
target =app

$(target):$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(target) *.o
