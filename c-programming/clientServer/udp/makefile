CC = gcc
CFLAGS = -g -Wall
CLIENT = p1
SERVER = p2
CLIENT_SRC = client.c
SERVER_SRC = server.c

.PHONY: all clean leak run

all: $(CLIENT) $(SERVER)

$(CLIENT): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_SRC)

$(SERVER): $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_SRC)

clean:
	rm -f $(CLIENT) $(SERVER)

leak: $(SERVER)
	valgrind --leak-check=full --track-origins=yes ./$(SERVER)

run: $(CLIENT) $(SERVER)
	@echo "Running Server and Client..."
	./$(SERVER) & sleep 1 && ./$(CLIENT)