CC     := gcc
CFLAGS := -Wall -g
LDFLAGS:= -lpthread


TARGET :=app


$(TARGET) : main.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o:%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) *.o
