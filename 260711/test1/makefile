CC     := gcc
CFLAGS := -Wall -g
LDFLAGS:= -lpthread

TARGET := app

SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,%.o,$(OBJ))

$(TARGET) : $(SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o:%.c
	$(CC) $(CFLAGS)	-c $<

clean:
	rm -f $(TARGET) *.o




