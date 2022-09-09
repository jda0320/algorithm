CC=gcc
CFLAGS=-g -Wall
TARGET-init=init
TARGET-ma=moving_average

all: $(TARGET-init) $(TARGET=ma)

$(TARGET-init): init.c
	$(CC) -o $@ $<

$(TARGET-ma): moving_average.c
	$(CC) -o $@ $<

clean:
	rm -f *.o
	rm -f $(TARGET-init) $(TARGET-ma)
