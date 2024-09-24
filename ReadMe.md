# OpenGL ES 2.0 Blue Triangle Example

![Preview](./preview.png)

This is a simple C program that uses SDL2 and OpenGL ES 2.0 to create a window and render a blue triangle. It serves as a basic introduction to setting up an OpenGL ES 2.0 rendering context on Linux using SDL2.

## Requirements

- SDL2 library (`libsdl2-dev`)
- OpenGL ES 2.0 library (`libgles2-mesa-dev`)
- GCC or any C compiler that supports the above libraries

### Installation on Linux (Debian / Ubuntu)

Install the necessary libraries:

```bash
sudo apt update
sudo apt install libsdl2-dev libgles2-mesa-dev gcc make
```

### How to Build

Clone this repository:

```bash
git clone <your-repo-url>
cd <your-repo-directory>
```

Build the project using the provided Makefile:

```bash
make
```

Run the executable:

```bash
./triangle
```

## Compile for Web

Requires [emcc](https://emscripten.org/docs/getting_started/downloads.html)

```bash
emcc main.c -o docs/index.html -s USE_SDL=2 -s FULL_ES2=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s WASM=1
```

## Project Structure

```
.
├── main.c          # The main C program
├── Makefile        # Makefile to build the project
├── .gitignore      # Files to be ignored by Git
├── preview.png     # Preview of the example output
└── README.md       # This README file
```

## License

MIT License
