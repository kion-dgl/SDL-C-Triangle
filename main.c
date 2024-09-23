#include <SDL2/SDL.h>
#include <GLES2/gl2.h>
#include <stdio.h>

// Vertex Shader source
const char* vertexShaderSource = R"(
    attribute vec4 position;
    void main() {
        gl_Position = position;
    }
)";

// Fragment Shader source
const char* fragmentShaderSource = R"(
    // precision mediump float;
    void main() {
        gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
    }
)";

// Compile shader
GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char* infoLog = (char*)malloc(infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            printf("Error compiling shader: %s\n", infoLog);
	    printf("%s", source);
            free(infoLog);
        }
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

// Link shaders into a program
GLuint createProgram(const char* vertexSource, const char* fragmentSource) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint infoLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char* infoLog = (char*)malloc(infoLen);
            glGetProgramInfoLog(program, infoLen, NULL, infoLog);
            printf("Error linking program: %s\n", infoLog);
            free(infoLog);
        }
        glDeleteProgram(program);
        return 0;
    }

    return program;
}

// Main
int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Create SDL window with OpenGL ES 2.0 context
    SDL_Window* window = SDL_CreateWindow("OpenGL ES 2.0 Triangle",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          640, 480, SDL_WINDOW_OPENGL);
    if (!window) {
        printf("Failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Set OpenGL ES version to 2.0
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    // Create OpenGL context
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        printf("Failed to create OpenGL context: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Load shaders and create program
    GLuint program = createProgram(vertexShaderSource, fragmentShaderSource);
    if (!program) {
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Define triangle vertices
    GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f,  // Top
       -0.5f, -0.5f, 0.0f,  // Bottom left
        0.5f, -0.5f, 0.0f   // Bottom right
    };

    // Main loop
    int running = 1;
    SDL_Event event;
    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Set viewport
        glViewport(0, 0, 640, 480);

        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        glUseProgram(program);

        // Get the position attribute location, enable it, and pass the vertex data
        GLint positionLoc = glGetAttribLocation(program, "position");
        glEnableVertexAttribArray(positionLoc);
        glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 0, vertices);

        // Draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Disable position attribute
        glDisableVertexAttribArray(positionLoc);

        // Swap buffers to display the triangle
        SDL_GL_SwapWindow(window);
    }

    // Clean up
    glDeleteProgram(program);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

