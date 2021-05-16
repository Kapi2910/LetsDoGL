#include "shader.h"
#include <fstream>
#include <iostream>

//Helper Functions
static std::string LoadShader(const std::string& shaderFile);
static void CheckError(GLint shader, GLint flag, bool isProgram, const std::string& errorMsg);
static GLuint CreateShader(const std::string& shaderText, GLenum shaderType);

Shader::Shader(const std::string& shaderFile)
{
	program = glCreateProgram();//CreateProgram
	
	shaders[0] = CreateShader(LoadShader(shaderFile + ".vert"), GL_VERTEX_SHADER);//Create every shader type. Create a helper function for this
	shaders[1] = CreateShader(LoadShader(shaderFile + ".frag"), GL_FRAGMENT_SHADER);//Create every shader type. Create a helper function for this

	//for each shader, attach that shader to the program created
	for (unsigned int i = 0; i < NUM_SHADER; ++i)
		glAttachShader(program, shaders[i]);
	
	glBindAttribLocation(program, 0, "position");//Bind an attribute location. why??
	glBindAttribLocation(program, 1, "uv");//Bind an attribute location. why??
	

	//Link the program and check for errors
	glLinkProgram(program);
	CheckError(program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	//Validate the Program and check for errors
	glValidateProgram(program);
	CheckError(program, GL_VALIDATE_STATUS, true, "Error: Program invalid: ");
}

Shader::~Shader()
{
	//For each shader type, detach from program and delete the shader
	for (unsigned int i = 0; i < NUM_SHADER; ++i)
	{
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	//Delete the program itself
	glDeleteProgram(program);
}

void Shader::Bind()
{
	glUseProgram(program);
}

static GLuint CreateShader(const std::string& shaderText, GLenum shaderType)
{
	//Create a Shader
	 GLuint shader = glCreateShader(shaderType);
	//Error Handling: Check whether shader was created
	 if (shader == 0)
		 std::cerr << "\n Error: Shader Creation Failed " << std::endl;

	 const GLchar* p[1];
	 p[0] = shaderText.c_str();
	 GLint lengths[1];
	 lengths[0] = shaderText.length();

	//Add the source files to the shader
	glShaderSource(shader, 1, p, lengths);

	//Compile the shader
	glCompileShader(shader);

	//Check for errors using the CheckError helper function
	CheckError(shader, GL_COMPILE_STATUS, false, "Error: Shader Not Compiled: ");

	return shader;
}

static std::string LoadShader(const std::string& shaderFile)
{
	std::ifstream ifShader;
	ifShader.open(shaderFile.c_str());

	std::string output, line;

	if (ifShader.is_open())
	{
		while (ifShader.good())
		{
			getline(ifShader, line);
			output.append(line + '\n');
		}
	}
	else
	{
		std::cerr << "\n Unable to load Shader: " << shaderFile << std::endl;
	}
	ifShader.close();

	return output;
}

static void CheckError(GLint shader, GLint flag, bool isProgram, const std::string& errorMsg)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		//Get the Log using glGetProgramLogInfo or ShaderLogInfo accordingly 
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		//display the log
		std::cerr << errorMsg << ": '" << error << "'" << std::endl;
	}
}