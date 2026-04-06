CC = gcc
CFLAGS = -g -Wall
TARGET1 = SingThreaded
TARGET2 = multiThreaded
FILE1 = single_threaded_server.c
FILE2 = multithreaded_server.c

.PHONY: all clean leak run

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(FILE1)
	$(CC) $(CFLAGS) -o $(TARGET1) $(FILE1) -lpthread -lm

$(TARGET2): $(FILE2)
	$(CC) $(CFLAGS) -o $(TARGET2) $(FILE2) -lpthread -lm

clean:
	rm -f $(TARGET)

leak: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

run: $(TARGET1) $(TARGET2)
	./$(TARGET2) 8081 & ./$(TARGET1) 8080

kill: 
	@echo "Limpando portas..."
	-fuser -k 8080/tcp 2>/dev/null || true
	-fuser -k 8081/tcp 2>/dev/null || true
	
