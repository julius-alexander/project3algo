CC = g++
CFLAGS = -std=c++17
SRC = $(wildcard *.cpp)
TARGET = maze

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f $(TARGET)
