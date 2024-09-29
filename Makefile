CC = gcc
EMCC = emcc
CFLAGS = -Wall -I/usr/include/SDL2
LDFLAGS = -lSDL2 -lGLESv2
SRCS = main.c
OBJS = $(SRCS:.c=.o)
TARGET_NATIVE = triangle
WEB_DIR = ./docs
TARGET_WEB = $(WEB_DIR)/index.html

# Build for native
all: $(TARGET_NATIVE)

$(TARGET_NATIVE): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET_NATIVE) $(CFLAGS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and executables
clean:
	rm -f $(OBJS) $(TARGET_NATIVE) $(TARGET_WEB) $(WEB_DIR)/triangle.wasm $(WEB_DIR)/triangle.js

# Build for web using emcc
web:
	mkdir -p $(WEB_DIR)
	$(EMCC) $(SRCS) -s USE_SDL=2 -s FULL_ES2=1 -o $(TARGET_WEB)
