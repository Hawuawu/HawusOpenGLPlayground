#pragma once

#ifndef VXLEVoxel_H
#define VXLEVoxel_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm\vec3.hpp"

#include <stdio.h>
#include <string.h>


#define VOXEL_VERTICES_COUNT 72

class VXLEVoxelMesh {
public:
	VXLEVoxelMesh();

	GLfloat vertices[VOXEL_VERTICES_COUNT];
	GLfloat colors[VOXEL_VERTICES_COUNT];
};

class VXLESurface4 {

public:
	VXLESurface4();

	VXLESurface4(
		GLfloat ax, GLfloat ay, GLfloat az,
		GLfloat bx, GLfloat by, GLfloat bz,
		GLfloat cx, GLfloat cy, GLfloat cz,
		GLfloat dx, GLfloat dy, GLfloat dz
	);

	glm::vec3 a;
	glm::vec3 b;
	glm::vec3 c;
	glm::vec3 d;
};

class VXLEVoxelColor {
public: 
	VXLEVoxelColor();
	VXLEVoxelColor(GLfloat r, GLfloat g, GLfloat b);

	GLfloat red = 0;
	GLfloat green = 0;
	GLfloat blue = 0;
};

class VXLEVoxel
{
public:

	VXLEVoxel(int x, int y, int z);
	~VXLEVoxel();

	int x = 0;
	int y = 0;
	int z = 0;

	bool enabled = 1;

	VXLEVoxelColor voxelColor;

	VXLEVoxelMesh getMesh();

	/*void setVertices(GLfloat vertices[VOXEL_VERTICES_COUNT]);
	void setVerticesColor(GLfloat colors[VOXEL_VERTICES_COUNT]);
	void openGLDraw(glm::vec3 origin);*/


	VXLESurface4 front;
	VXLESurface4 back;
	VXLESurface4 left;
	VXLESurface4 right;
	VXLESurface4 top;
	VXLESurface4 bottom;

private:
	/*
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
	};*/

/*	GLfloat vertices[72] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, -1.0f,
		1.0f, 0.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		0.0f, 1.0f, -1.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 1.0f, -1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, -1.0f,
		0.0f, 1.0f, -1.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f
	};*/

/*
	GLfloat colors[72] = {
		0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
		1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
		0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
		0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
	};
	*/

};

#endif // !VXLEVoxel_H
