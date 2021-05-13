#ifndef MESH_H
#define MESH_H

#include <gl/glew.h>
#include <glm/glm.hpp>

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
};

class Mesh
{
public:
	
	Mesh(Vertex* vertexList, unsigned int vertexLength);


	void Draw(); //Responsible for sending the data into our Graphics Pipeline, basically binds the vertexm class the glDrawArrays and then unbinds it
	virtual ~Mesh();
private:
	//Data
	enum
	{
		POSITION,
		NUM_BUFFERS
	};

	GLuint vertexArrayObjects; //Contains the vertex data
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	unsigned int drawCount; //Keeps track of how vertexArrayObjects to be counted
};
#endif // MESH_H
