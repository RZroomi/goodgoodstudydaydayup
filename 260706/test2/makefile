CC=gcc
CFLAGS=-Wall -g
TARGET=app

all:$(TARGET)

$(TARGET):main.o calc.o
	$(CC) $(CFLAGS) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f $(TARGET) *.o


