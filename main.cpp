#include <stdio.h>
#include "SDL2/SDL.h"
#include "OpenGL/gl3.h"

#include "matrix4.h"
#include "gl_shader_compiler.h"

#define WIDTH 900
#define HEIGHT 500

int main(int argc, char** argv){
    SDL_Window* window = SDL_CreateWindow("Rotations", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    glClearColor(0, 0.5, 1, 1);

    char* vertexShaderFile = readFileToCharArray("vertex_shader.glsl");
    char* fragmentShaderFile = readFileToCharArray("fragment_shader.glsl");
    unsigned int shaderProgram = compileShaderVF(vertexShaderFile, fragmentShaderFile);
    delete[] vertexShaderFile;
    delete[] fragmentShaderFile;

    glUseProgram(shaderProgram);
    int positionId = glGetAttribLocation(shaderProgram, "position");
    int projectionMatId = glGetUniformLocation(shaderProgram, "projectionMatrix");
    int modelMatId = glGetUniformLocation(shaderProgram, "modelMatrix");
    Matrix4 projectionMatrix(1);
    float hW = WIDTH / 2;
    float hH = HEIGHT / 2;
    projectionMatrix.setOrthoganalProjectionMatrix(-hW, hW, -hH, hH);
    glUniformMatrix4fv(projectionMatId, 1, false, &projectionMatrix.m[0][0]);
    float vertices[] = {
        -1, -1,
        0, 1,
        1, -1
    };
    unsigned int vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(positionId, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(positionId);


    SDL_Event event;
    bool isRunning = true;

    float rot = 0.1;

    Matrix4 modelMatrix(1);
    modelMatrix.scale2D(25, 25);
    
    while(isRunning){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:{
                    isRunning = false;
                }
                case SDL_KEYDOWN:{
                    if(event.key.keysym.sym == SDLK_ESCAPE){
                        isRunning = false;
                    }
                }
            }
        }
        glClear(GL_COLOR_BUFFER_BIT);

        modelMatrix.rotateZ(rot);
        
        glUniformMatrix4fv(modelMatId, 1, false, &modelMatrix.m[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
    }
    
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);

    return 0;
}