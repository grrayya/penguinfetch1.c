CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = penguinfetch
PREFIX ?= /usr/local

all: $(TARGET)

$(TARGET): penguinfetch.c
	$(CC) $(CFLAGS) -o $(TARGET) penguinfetch.c

run: $(TARGET)
	./$(TARGET)

install: $(TARGET)
	install -Dm755 $(TARGET) $(PREFIX)/bin/$(TARGET)

uninstall:
	rm -f $(PREFIX)/bin/$(TARGET)

clean:
	rm -f $(TARGET)
