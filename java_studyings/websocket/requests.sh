#!/bin/bash

clear
URL="ws://localhost:8080"
USER_NAME="ScriptBot"

echo "Compiling the files"
javac -d . *.java &

echo "Running the Server"
java java_studyings.websocket.WebSocketServer &
SERVER_ID=$!

while ! nc -z localhost 8080; do
    sleep 1
done 

send_message() {
    local message=$1
    echo "Sending: $message"
    
    (
      echo "$USER_NAME"
      sleep 1
      echo "$message"
      sleep 1
    ) | wscat --connect $URL > /dev/null
}

send_message "Hello everyone! This is an automated broadcast."

TARGET_USER="Rodolfo"
send_message "/pm $TARGET_USER Hey Rodolfo, the build is complete!"

echo "Messages dispatched."