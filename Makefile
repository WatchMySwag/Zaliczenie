CFLAGS = -Wall -std=c11

TARGET = program

SRCS = main.c poziomy.c pliki.c

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)



