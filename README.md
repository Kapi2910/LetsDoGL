# OpenGL

Created: May 12, 2021 3:46 AM
Git: https://github.com/Kapi2910/LetsDoGL/

[Intro To Modern OpenGL Tutorial](https://www.youtube.com/playlist?list=PLEETnX-uPtBXT9T-hD0Bj31DSnwio-ywh)
# Contents
- [OpenGL](#opengl)
- [Contents](#contents)
	- [OpenGL Windows 12-May-2021](#opengl-windows-12-may-2021)
	- [Graphics Pipeline 12-May-2021](#graphics-pipeline-12-may-2021)
		- [Processing - Shaders 12 May 2021](#processing---shaders-12-may-2021)
		- [Data - Meshes 13-May-2021](#data---meshes-13-may-2021)
	- [Texture 16-May-2021](#texture-16-may-2021)
		- [Texture Loading](#texture-loading)
		- [Texture Mapping](#texture-mapping)

## OpenGL Windows 12-May-2021

Creates C++ header files using #define and not #pragma once

```cpp
#ifndef DISPLAY_H
#define DISPLAY_H
	//Class Definition
#endif //DISPLAY_H
```

SDL2 is used only for windowing. Windowing is an OS-dependant operation, hence you need such libraries to create it universally. In this case, SDL2 initialization is done within the constructor and destructor of the class. This is only if SDL2 is used for windowing alone.

> ***Why create a GL Context:*** When SDL2 is asked to create a window, it commands the OS to create a window (because OS is in-charge of windowing). SDL sends the window data to the OS, and the OS creates a window. But when we issue OpenGL commands, these commands are sent to the GPU, and not the OS, which is in-charge windows. The GPU has no control over the window. Hence, we enable an OpenGL Context. Under this context, the OS transfers ***MOST*** of the control to the GPU, and hence we can render graphics using it.

> ***Double Buffering:*** If the window is reading data to draw, while the GPU is writing the data to be drawn, many artefacts occur on the screen. Hence, there exists two window buffers - front and back. The GPU always writes to the back buffer, while the window always displays the front buffer. When, the GPU is done write the back buffer entirely, the pointers of front and back are swapped.

Initializing SDL2 is easy: 

```cpp
SDL_Init(SDL_INIT_EVERYTHING)
```

Setting certain OpenGL attributes and then Creating a Window:

```cpp
//OpenGL Attribuets - This ensures minimum requirements, actual value can be greater
SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // Sets the number of shades of RED color
SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // Sets the number of shades of GREEN color
SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); // Sets the number of shades of BLUE color
SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // Sets the number of shades of ALPHA color
SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // Sets the size of the color buffer (R, G, B, A). Value is 32, because we want each Color size to be 8
SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Enables Double Buffer

//Creating Window
window = SDL_CreateWindow(title /*Must be a C String*/, x position on screen, y position on screen, width, height, FLAGS);
SDL_GL_CreateContext(window); // Creates an OpenGL Context
```

## Graphics Pipeline 12-May-2021

![OpenGL%20a2d214e4802c458fbbd63f750688c119/Untitled.png](OpenGL%20a2d214e4802c458fbbd63f750688c119/Untitled.png)

> ***Rasterization:*** It is the process of converting the given vertices into their corresponding shapes. 
This is a 2 step process:
1. Connect the vertices
2. Fill them with Pixels

### Processing - Shaders 12 May 2021

> ***Shader:*** Piece of code that runs on the GPU. Vertex shader converts the [mesh] data sent to the GPU into some thing rasterizable. Fragment Shader calculates the per pixel property values (e.g. color) on the rasterized data.

```cpp
//Shader Class Definition using #ifndef code pattern
class Shader
{
private:
		static const unsigned int NUM_SHADER = 2; //Specifies the number of shader types you are working with e.g. Vertex, Fragment, [Geometry, Teselllation]
		GLuint program; //Keeps track of the shaders to be bound
		GLuint shaders[NUM_SHADER]; // TODO: Using enums rather than array
public:
		Shader(std::string& shaderFile); //The constructor does some compilation on the shader file before sending it to the GPU
		virtual ~Shader();

		void Bind(); //Binding puts the GPU in a state that uses the Shader, the GPU is bound to.

}
```

```cpp
//Shader Class Implementation

//Helper Functions
static std::string LoadShader(const std::string& shaderFile);
static void CheckError(GLint shader, GLint flag, bool isProgram, const std::string& errorMsg);
static GLuint CreateShader(const std::string& shaderText, GLenum shaderType);

Shader::Shader(std::string& shaderFile)
{
	//CreateProgram

	//Create every shader type. Create a helper function for this

	//for each shader, attach that shader to the program created

	//Bind an attribute to its shader counterpart
	glBindAttribLocation(program, 0, "positions");
	

	//Link the program and check for errors

	//Validate the Program and check for errors
}
Shader::~Shader()
{
	//For each shader type, detach from program and delete the shader

	//Delete the program itself
}

void Shader::Bind()
{
	glUseProgram(program);
}

static GLuint CreateShader(const std::string& shaderText, GLenum shaderType)
{
	//Create a Shader
	shader = glCreateShader(shaderType);
	//Error Handling: Check whether shader was created
	
	
	//Add the source files to the shader
	//Compile the shader
	
	//Check for errors using the CheckError helper function
	
	return shader;
}
static std::string LoadShader(const std::string& shaderFile)
{
	std::ifstream ifShader;
	ifShader.open(shaderFile.c_str());
	
	std::string output, line;

	if(ifShader.is_open())
	{
		while(ifShader.good())
		{
			getline(ifShader, line);
			output.append(line + '\n');
		}
	}
	else
	{
		std::cerr << //Some error message
	}
	ifShader.close();

	return output;
}

static void CheckError(GLint shader, GLint flag, bool isProgram, const std::string& errorMsg)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if(isProgram)
		glGetProgramiv(/*required args*/);
	else
		glGetShaderiv(/*required args*/);

	if(success == GL_FALSE)
	{
			//Get the Log using glGetProgramLogInfo or ShaderLogInfo accordingly 
			//display the log
	}
}
```

### Data - Meshes 13-May-2021

> ***Mesh:*** 3D data that the GPU processes to render graphics

```cpp
//This class represents 3D coordinates using glm:vec3
class Vertex
{
	private:
		glm::vec3 pos;
	public:
		Vertex(const glm::vec3 pos)
		{
			this->pos = pos;
		} 
}
```

> ***Vertex Attributes:*** These are the per vertex values that are later interpolated to get the per pixel values of the same attributes. These attributes can be position, color, texture coordinates, etc.

```cpp
//Define a Mesh class using the #ifndef pattern
//OpenGL expects the data to be in 3D (x,y,z) coordinates
class Mesh
{
	public:
		/*
			Mesh(Vertex* vertexList, unsigned int vertexLength) does a few things:
			1. Creates the vertexArrayObject & binds it 
			2. Creates the vertexArrayBuffer, binds it, & sends data to it http://docs.gl/gl4/glBufferData
			3. Enable & Assign Vertex Attributes http://docs.gl/gl4/glVertexAttribPointer
			
		*/
		Mesh(Vertex* vertexList, unsigned int vertexLength);
		

		void Draw(); //Responsible for sending the data into our Graphics Pipeline, basically binds the vertexm class the glDrawArrays and then unbinds it
		virtual ~Mesh();
	private:
		//Data
		enum
		{
			POSITIONS,
			NUM_BUFFERS
		}
		GLuint vertexArrayObjects; //Contains the vertex data
		GLuint vertexArrayBuffers[NUM_BUFFERS];
		unsigned int drawCount; //Keeps track of how vertexArrayObjects to be counted
}
```

## Texture 16-May-2021

NOTE: Using SOIL2 for texture loading

### Texture Loading

Create a Texture class

```cpp
class Texture
{
public:
	Texture(std::string& textureFile);
	virtual ~Texture();
	void Bind(unsigned int unit);
	
private:
	GLuint texture;
} 
```

> **Constructor Functions:**

1. Loads data using stb_image
2. Sets generates and binds a texture buffer
3. Sets Texture Parameters
    1.  Min & Mag Filtes
    2. S & T wrapping
4. loads in the texture
5. free the texture memory

```cpp
Texture::Texture(const std::string& textureFile)
{
	unsigned int width, height, components; //variables that store the width, height & component information of the texture loaded
	unsigned char* texData = stbi_load(textureFile.c_str(), &width, &height, &components, 4);

	if(texData == NULL) std::cerr << "\nNo texture data loaded from " << textureFile;
	glGenTextures(1, &texture);
	glBindTextures(GL_TEXTURE_2D, texture);

	glTextureParameters(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTextureParameters(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTextureParameters(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameters(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData); // docs: http://docs.gl/gl4/glTexImage2D

	stbi_image_free(texData);
	
} 
```

> **Destructor:** Deletes the generated texture

```cpp
Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}
```

> **Bind:** Sets the active texture unit and then binds the texture to that unit

```cpp
void Texture::Bind(unsigned int unit)
{
	//if unit is between 0 and 31

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texture);
}
```

### Texture Mapping

> OpenGL takes its textures in a separate coordinate system known as texture coordinate (texcoords or uv-coords). These coordinaties make the texture loading resolution independant

These texcoords can be packed into the vertex data of our mesh, making it convienient for us to read the these new set of coords

The vertex class changes so:

```cpp
class Vertex
{
private:
	glm::vec3 pos;
	glm::vec2 uv; //CHANGE:
public:
	Vertex(const glm::vec3 pos, const glm::vec2 uv)
	{
		this->pos = pos;
		this->uv = uv;
	}

	inline glm::vec3* GetPos() { return pos; }
	inline glm::vec2* GetUV() { return uv; }
};
```

The mesh class contructor also changes:

```cpp
Mesh::Mesh(Vertex* vertexList, unsigned int vertexLength)
{
/*
		Mesh(Vertex* vertexList, unsigned int vertexLength) does a few things:
		1. Creates the vertexArrayObject & binds it
		2. Creates the vertexArrayBuffer, binds it, & sends data to it http://docs.gl/gl4/glBufferData
		3. Enable & Assign Vertex Attributes http://docs.gl/gl4/glVertexAttribPointer

*/

	drawCount = vertexLength;

	//1
	glGenVertexArrays(1, &vertexArrayObjects);
	glBindVertexArray(vertexArrayObjects);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> uvs;

	positions.reserve(vertexLength);
	uvs.reserve(vertexLength);

	for(int i = 0; i < vertexLength; i++)
	{
		positions.push_back(*vertexList[i].GetPos());
		uvs.push_back(*vertexList[i].GetUV());
	}
	
	//2
	glGenBuffers(1, vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION]);
	glBufferData(GL_ARRAY_BUFFER, vertexLength * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	//3
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[UV]);
	glBufferData(GL_ARRAY_BUFFER, vertexLength * sizeof(uvs[0]), &uvs[0], GL_STATIC_DRAW);

	//3
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);

}
```

Until now we just  setup the mesh to be able to send data to the GPU

Now we let's setup the shader and the actual data that needs to be rendered:

> Change vertices list in main.cpp

```cpp
Vertex vertices[] = {
        Vertex(glm::vec3(-0.5, -0.5,  0.0), glm::vec2(0.0, 0.0)),
        Vertex(glm::vec3( 0.0,  0.5,  0.0), glm::vec2(0.5, 1.0)),
        Vertex(glm::vec3( 0.5, -0.5,  0.0), glm::vec2(1.0, 0.0))
    };
```

> Add the uv attribute to the shader class

```cpp
glBindAttribLocation(program, 1, "uv");//Bind an attribute to its shader counterpart
```
