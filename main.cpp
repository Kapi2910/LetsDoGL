#include <iostream>
#include "display/display.h"
#include "shader/shader.h"

int wmain() //called wmain instead of main because visual studio :/
{
    Display display(800, 600, "Hello Window");
    Shader shader("res/Shaders/BasicShader");

    while(!display.IsClosed())
    {
        display.ClearDisplay(0.8f, 0.3f, 0.5f, 1.0f);

        shader.Bind();

        display.Update();
    }

    return 0;
}
