#include "mesh.h"


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

	//2
	glGenBuffers(1, vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION]);
	glBufferData(GL_ARRAY_BUFFER, vertexLength * sizeof(vertexList[0]), vertexList, GL_STATIC_DRAW);

	//3
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);

}

void Mesh::Draw()
{
	glBindVertexArray(vertexArrayObjects);

	glDrawArrays(GL_TRIANGLES, 0, drawCount);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObjects);
}
