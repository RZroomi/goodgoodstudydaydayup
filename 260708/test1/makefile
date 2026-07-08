CC  :=gcc
CFLAGS :=-Wall -g
LDFLAGS:=
SRC_DIR:=.
INC_DIR:=.
OBJ_DIR:=obj
MODE   ?=debug

SRC :=$(wildcard *.c)
OBJ :=$(patsubst %.c,%.o,$(SRC))

TARGET :=app

all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) *.o


