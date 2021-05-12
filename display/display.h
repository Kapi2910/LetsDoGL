#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <gl/glew.h>
#include <string>
#include <iostream>

class Display 
{
private:
   SDL_Window* window;
   SDL_GLContext glContext;
   bool isClosed;

public:
    Display(int width, int height, const std::string& title);
    virtual ~Display();

    void Update();
    void ClearDisplay(float r, float g, float b, float a);
    bool IsClosed();
};
#endif // DISPLAY_H
