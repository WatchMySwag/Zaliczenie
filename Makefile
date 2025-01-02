CC = gcc
CFLAGS = -Wall -std=c11
LDFLAGS = -lgetopt

TARGET = program

SRCS = main.c poziomy.c pliki.c

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)


