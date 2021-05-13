//Shader Class Definition
#ifndef SHADER_H
#define SHADER_H

#include <gl/glew.h>
#include <string>

class Shader
{
private:
	static const unsigned int NUM_SHADER = 2; //Specifies the number of shader types you are working with e.g. Vertex, Fragment, [Geometry, Teselllation]
	GLuint program; //Keeps track of the shaders to be bound
	GLuint shaders[NUM_SHADER]; // TODO: Using enums rather than array

public:
	Shader(const std::string& shaderFile); //The constructor does some compilation on the shader file before sending it to the GPU
	virtual ~Shader();

	void Bind(); //Binding puts the GPU in a state that uses the Shader, the GPU is bound to.

};

#endif // SHADER_H