CC = gcc
CFLAGS = -g -Wall
TARGET = p1
FILE = ex2.c

.PHONY: all clean leak run

all: $(TARGET)

$(TARGET): $(FILE)
	$(CC) $(CFLAGS) -o $(TARGET) $(FILE)

clean:
	rm -f $(TARGET)

leak: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

run: $(TARGET)
	./$(TARGET)