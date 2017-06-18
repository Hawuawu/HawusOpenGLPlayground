#include "VXLEVoxel.h"


void VXLEVoxel::setVertices(GLfloat vertices[VOXEL_VERTICES_COUNT] )
{
	memcpy(cubeVertices_, vertices, sizeof(vertices));
}

void VXLEVoxel::setVerticesColor(GLfloat colors[VOXEL_VERTICES_COUNT] )
{
	memcpy(cubeVerticesColors_, colors, sizeof(colors));
}

void VXLEVoxel::openGLDraw(glm::vec3 origin)
{
	glTranslatef(x, y, z);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, cubeVertices_);
	glColorPointer(3, GL_FLOAT, 0, cubeVerticesColors_);

	glDrawArraysInstanced(GL_QUADS, 0, 24, 100);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glTranslatef(-x, -y, -z);
}

VXLEVoxel::VXLEVoxel(int x, int y, int z) : x(x), y(y), z(z)
{

}

VXLEVoxel::~VXLEVoxel()
{

}