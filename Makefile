# Compiler
CC = gcc

# Output file name
TARGET = triangle

# Source files
SRC = main.c

# Compiler flags
CFLAGS = -Wall

# Include directories
INCLUDE = 

# Libraries
LIBS = -lSDL2 -lGLESv2

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

# Clean rule
clean:
	rm -f $(TARGET)

