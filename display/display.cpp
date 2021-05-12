#include "display.h"

Display::Display(int width, int height, const std::string& title)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    glContext = SDL_GL_CreateContext(window);

    GLenum status = glewInit();

    if(status != GLEW_OK)
    {
        std::cerr << "\nGLEW failed to initialize" << std::endl;
    }

    isClosed = false;
}

Display::~Display()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Display::ClearDisplay(float r, float g, float b, float a)
{
   glClearColor(r, g, b, a);
   glClear(GL_COLOR_BUFFER_BIT);
}

void Display::Update()
{
    SDL_GL_SwapWindow(window);

    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            isClosed = true;
        }

    }
}

bool Display::IsClosed()
{
    return isClosed;
}
