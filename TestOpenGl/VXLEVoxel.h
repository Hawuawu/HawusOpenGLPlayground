#pragma once

#ifndef VXLEVoxel_H
#define VXLEVoxel_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm\vec3.hpp"

#include <stdio.h>
#include <string.h>

#define VOXEL_VERTICES_COUNT 72


class VXLEVoxel
{
public:

	VXLEVoxel(int x, int y, int z);
	~VXLEVoxel();

	int x = 0;
	int y = 0;
	int z = 0;

	void setVertices(GLfloat vertices[VOXEL_VERTICES_COUNT]);
	void setVerticesColor(GLfloat colors[VOXEL_VERTICES_COUNT]);
	void openGLDraw(glm::vec3 origin);


private:
	GLfloat cubeVertices_[VOXEL_VERTICES_COUNT] = {
		-1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
		 1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
		-1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
		-1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
		-1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
		-1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
	};

	GLfloat cubeVerticesColors_[VOXEL_VERTICES_COUNT] = {
		0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
		1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
		0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
		0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
	};

};

#endif // !VXLEVoxel_H
