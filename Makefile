# Define the compiler
CC = gcc

# Define compiler flags (-Wall shows all warnings, -O2 optimizes the binary)
CFLAGS = -Wall -Wextra -O2

# Define the final executable name
TARGET = penguinfetch

# The default rule when you just type 'make'
all: $(TARGET)

# How to build the target
$(TARGET): penguinfetch.c
	$(CC) $(CFLAGS) -o $(TARGET) penguinfetch.c

# A rule to clean up the compiled binary so it doesn't clutter git
clean:
	rm -f $(TARGET)
