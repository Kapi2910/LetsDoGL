#include <iostream>
#include "display/display.h"
#include "shader/shader.h"
#include "mesh/mesh.h"

int wmain() //called wmain instead of main because visual studio :/
{
    Vertex vertices[] = {
        glm::vec3(-0.5, -0.5,  0.0),
        glm::vec3( 0.0,  0.5,  0.0),
        glm::vec3( 0.5, -0.5,  0.0)
    };
    
    Display display(800, 600, "Hello Window");
    Shader shader("res/Shaders/BasicShader");
    Mesh mesh(vertices, (sizeof(vertices) / sizeof(vertices[0])));

    while(!display.IsClosed())
    {
        display.ClearDisplay(0.8f, 0.3f, 0.5f, 1.0f);

        shader.Bind();
        mesh.Draw();
        display.Update();
    }

    return 0;
}
