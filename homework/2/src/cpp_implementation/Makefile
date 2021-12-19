SRC = main.cpp task.cpp task1.cpp task2.cpp task3.cpp bonus.cpp
HEADERS = $(wildcard *.h)

CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -g
LDFLAGS = -lm

TARGET = main

build: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(TARGET) 

clean:
	rm -f main

.PHONY: build clean
