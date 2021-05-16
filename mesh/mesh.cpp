#include "mesh.h"
#include <vector>

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

	for (int i = 0; i < vertexLength; i++)
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
