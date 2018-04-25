//
// Created by 도병수 on 2018. 4. 25..
//

#ifndef SUPERBIBLE6_BSAPP_H
#define SUPERBIBLE6_BSAPP_H

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>
#include <string>
#include <GL/glew.h>

class BSApp {
public:
    BSApp();
    ~BSApp();
    bool set_opengl_attribute();
    void check_sdl_error(int line = -1);

    void startup();
    void render();
    void shutdown();

    void start_loop();

    GLuint compile_shader();
    std::string import_file(std::string filename);
    bool checkShaderError(GLuint glIdentifier);

private:
    SDL_Window *main_window;
    SDL_GLContext main_context;
    double timer;
    bool loop = true;

    GLuint rendering_program;
    GLuint vao;

};


#endif //SUPERBIBLE6_BSAPP_H
