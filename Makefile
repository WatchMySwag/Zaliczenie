CC = gcc
CFLAGS = -Wall -std=c11

TARGET = program


SRCS = main.c poziomy.c pliki.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

test1: $(TARGET)
	./$(TARGET) -l 1

test2: $(TARGET)
	./$(TARGET) -l 2

test3: $(TARGET)
	./$(TARGET) -l 3

test4: $(TARGET)
	./$(TARGET) -l 4

test-file: $(TARGET)
	./$(TARGET) -f testowy.txt



