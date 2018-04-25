//
// Created by 도병수 on 2018. 4. 25..
//

#include "BSApp.h"
#include <iostream>
#include <chrono>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <fstream>
#include <sstream>

BSApp::BSApp() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Faild to init SDL\n";
    }

    main_window = SDL_CreateWindow(
            "My Opengl",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            640, 480,
            SDL_WINDOW_OPENGL);

    if (!main_window)
    {
        std::cout << "Unable to create window\n";
        check_sdl_error(__LINE__);
    }

    set_opengl_attribute();

    main_context = SDL_GL_CreateContext(main_window);

    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;
    glewInit();

    printf("----------------------------------------------------------------\n");
    printf("Graphics Successfully Initialized\n");
    printf("OpenGL Info\n");
    printf("    Version: %s\n", glGetString(GL_VERSION));
    printf("     Vendor: %s\n", glGetString(GL_VENDOR));
    printf("   Renderer: %s\n", glGetString(GL_RENDERER));
    printf("    Shading: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("----------------------------------------------------------------\n");

    startup();
}

bool BSApp::set_opengl_attribute() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    return true;
}

BSApp::~BSApp() {

    shutdown();

    // Delete our OpengL context
    SDL_GL_DeleteContext(main_context);

    // Destroy our window
    SDL_DestroyWindow(main_window);

    // Shutdown SDL 2
    SDL_Quit();

}

void BSApp::check_sdl_error(int line)
{
    std::string error = SDL_GetError();

    if (!error.empty())
    {
        std::cout << "SDL Error : " << error << std::endl;

        if (line != -1)
            std::cout << "\nLine : " << line << std:: endl;

        SDL_ClearError();
    }
}

void BSApp::startup() {
    rendering_program = compile_shader();
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void BSApp::render() {
    // Loop draw
    const GLfloat color[] = {
            0.0f, 0.2f, 0.0f, 1.0f
    };
    glClearBufferfv(GL_COLOR, 0, color);

    glUseProgram(rendering_program);
    glDrawArrays(GL_TRIANGLES, 0, 3);

}

void BSApp::shutdown() {
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(rendering_program);
    glDeleteVertexArrays(1, &vao);
}

void BSApp::start_loop() {
    while (loop)
    {
        timer = std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();

        render();

        // Event
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                loop = false;

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        loop = false;
                        break;
                    case SDLK_r:
                        // Cover with red and update
                        glClearColor(1.0, 0.0, 0.0, 1.0);
                        glClear(GL_COLOR_BUFFER_BIT);

                        break;
                    case SDLK_g:
                        // Cover with green and update
                        glClearColor(0.0, 1.0, 0.0, 1.0);
                        glClear(GL_COLOR_BUFFER_BIT);

                        break;
                    case SDLK_b:
                        // Cover with blue and update
                        glClearColor(0.0, 0.0, 1.0, 1.0);
                        glClear(GL_COLOR_BUFFER_BIT);

                        break;
                    default:
                        break;
                }
            }
        }

        // SDL
        SDL_GL_SwapWindow(main_window);
    }
}

std::string BSApp::import_file(std::string filename) {
    std::ifstream file(filename);
    std::stringstream stream;

    file.open(filename);
    stream << file.rdbuf();
    file.close();

    return stream.str();
}

GLuint BSApp::compile_shader() {
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint program;

    std::string v = import_file("glsl/vertex.glsl");
    std::string f = import_file("glsl/fragment.glsl");
    const GLchar* vertex = v.c_str();
    const GLchar* frag   = f.c_str();

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex, nullptr);
    glCompileShader(vertex_shader);
    checkShaderError(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &frag, nullptr);
    glCompileShader(fragment_shader);
    checkShaderError(vertex_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

bool BSApp::checkShaderError(GLuint glIdentifier) {
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(glIdentifier, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(glIdentifier, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        return true;
    }
    return false;
}

