// TestOpenGl.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

#define GLFW_INCLUDE_GLU
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdio>

#include "VXLEngine.h"

using namespace std;

VXLEngineSettings engineSettings;
VXLEFirstPersonControls *engineControls;
VXLECamera *engineCamera;

struct SRTMPartialVoxel {
	short x;
	short y;
	short z;
};

struct SRTMVoxelBlock {
	short numberOfVoxels;
	vector<SRTMPartialVoxel> voxels;
};

void mouseMove(GLFWwindow* window, double mouseX, double mouseY)
{
	engineControls->lastMouseX = mouseX;
	engineControls->lastMouseY = mouseY;
}

void mouseClicked(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			engineControls->movingMouse = true;
		}
		else {glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			engineControls->movingMouse = false;
		}
	}
}

void controls(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		break;

	case GLFW_KEY_W:
	case GLFW_KEY_UP:
		if (action == GLFW_PRESS)
		{
			engineControls->forward = true;
		}
		else if (action == GLFW_RELEASE){
			engineControls->forward = false;
		}
		break;

	case GLFW_KEY_A:
	case GLFW_KEY_LEFT:
		if (action == GLFW_PRESS)
		{
			engineControls->leftStrafe = true;
		}
		else if (action == GLFW_RELEASE) {
			engineControls->leftStrafe = false;
		}
		break;

	case GLFW_KEY_D:
	case GLFW_KEY_RIGHT:
		if (action == GLFW_PRESS)
		{
			engineControls->rightStrafe = true;
		}
		else if (action == GLFW_RELEASE) {
			engineControls->rightStrafe = false;
		}
		break;


	case GLFW_KEY_S:
	case GLFW_KEY_DOWN:
		if (action == GLFW_PRESS)
		{
			engineControls->backward = true;
		}
		else if (action == GLFW_RELEASE) {
			engineControls->backward = false;
		}
		break;
	}

}

GLFWwindow* initWindow(const int resX, const int resY)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing  

									 // Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(resX, resY, "TEST", NULL, NULL);

	if (window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return NULL;
	}


	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, controls);
	glfwSetCursorPosCallback(window, mouseMove);
	glfwSetMouseButtonCallback(window, mouseClicked);

	// Get info of GPU and supported OpenGL version
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

	glEnable(GL_DEPTH_TEST); // Depth Testing
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	return window;
}

void drawCube()
{
	GLfloat vertices[] =
	{
		-1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
		 1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
		-1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
		-1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
		-1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
		-1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
	};

	GLfloat colors[] =
	{
		0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
		1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
		0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
		0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
		0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
	};

	static float alpha = 0;
	//attempt to rotate cube
	//glRotatef(alpha, 0, 1, 0);

	/* We have a color array and a vertex array */
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	/* Send data : 24 vertices */
	glDrawArrays(GL_QUADS, 0, 24);

	/* Cleanup states */
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	alpha += 1;
}

void drawGround(float groundLevel)
{
	GLfloat extent = 600.0f; // How far on the Z-Axis and X-Axis the ground extends
	GLfloat stepSize = 20.0f;  // The size of the separation between points

							   // Set colour to white
	glColor3ub(255, 255, 255);

	// Draw our ground grid
	glBegin(GL_LINES);
	for (GLint loop = -extent; loop < extent; loop += stepSize)
	{
		// Draw lines along Z-Axis
		glVertex3f(loop, groundLevel, extent);
		glVertex3f(loop, groundLevel, -extent);

		// Draw lines across X-Axis
		glVertex3f(-extent, groundLevel, loop);
		glVertex3f(extent, groundLevel, loop);
	}
	glEnd();
}
void display(GLFWwindow* window)
{

	VXLEShaderProgram geometryShadersProgram;
	GLuint geometryShadersProgramInt = geometryShadersProgram.compile (
		VXLEShader("shaders/translate_voxel.geom", GL_VERTEX_SHADER)
	);

	glm::vec2 translations[100];
	int index = 0;
	GLfloat offset = 0.1f;
	for (GLint y = -10; y < 10; y += 2)
	{
		for (GLint x = -10; x < 10; x += 2)
		{
			glm::vec2 translation;
			translation.x = (GLfloat)x / 10.0f + offset;
			translation.y = (GLfloat)y / 10.0f + offset;
			translations[index++] = translation;
		}
	}

	// Store instance data in an array buffer
	GLuint instanceVBO;
	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Generate quad VAO
	GLfloat quadVertices[] = {
		// Positions   // Colors
		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
		0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
		-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
		0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
		0.05f,  0.05f,  0.0f, 1.0f, 1.0f
	};
	GLuint quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	// Also set instance data
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1); // Tell OpenGL this is an instanced vertex attribute.
	glBindVertexArray(0);

	std::string file = "D:/SRTM/N48E011.vxlmap";
	ifstream input_file(file.c_str(), ios::in | ios::binary);
	
	cout << input_file.good();

	bool read = true;
	int counter = 0;
	while (!input_file.eof()) {
		short numberOfVoxels;
		input_file.read((char*)&numberOfVoxels, sizeof(short));

		short * voxels = new short[numberOfVoxels * 3];		
		input_file.read((char*)voxels, numberOfVoxels * 3 * sizeof(short));

		delete[] voxels;
		/*for (int i = 0; i < (numberOfVoxels * 3); i+=3) {
			cout << voxels[i] << "-" << voxels[i+1] << "-" << voxels[i+2] << "\n";
		}*/
		/*
		for (int i = 0; i < numberOfVoxels; i++) {
			short x;
			input_file.read((char*)&x, sizeof(short));

			short y;
			input_file.read((char*)&y, sizeof(short));

			short z;
			input_file.read((char*)&z, sizeof(short));
		}
		*/
		counter++;
	}
	cout << counter;
	/*

	while ((input_file.read((char *) & block, sizeof(SRTMVoxelBlock)))) {
		//input_file.read((char*)&b, sizeof(short));
		cout << "-------------------------------------------------------\n";
		cout << block.numberOfVoxels << "-" << block.voxels.size() << "\n";//block.numberOfVoxels << " - " << block.voxels.size();
		for (int i = 0; i < block.numberOfVoxels; i++) {
			SRTMPartialVoxel voxel = block.voxels.at(i);
			cout << voxel.x << "-" << voxel.y << "-" << voxel.z;

		}
		cout << "-------------------------------------------------------\n";
	}
	*/
	while (!glfwWindowShouldClose(window))
	{
		// Scale to window size
		GLint windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);

		// Draw stuff
		glClearColor(0.0, 0.8, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION_MATRIX);
		glLoadIdentity();
		gluPerspective(60, (double)windowWidth / (double)windowHeight, 2.0f, 1500.0f);

		glMatrixMode(GL_MODELVIEW_MATRIX);
		//glTranslatef(0, 0, -100);

		// Check for any input, or window movement
		glfwPollEvents();

		glTranslatef(0, 0, -5);

		if (engineControls->movingMouse) {
			glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
		}
		engineCamera->recalculate();
		glRotatef(engineCamera->getDirection().x, 1.0f, 0.0f, 0.0f); // Rotate our camera on the x-axis (looking up and down)
		glRotatef(engineCamera->getDirection().y, 0.0f, 1.0f, 0.0f); // Rotate our camera on the  y-axis (looking left and right)


	    glTranslatef(-1 * engineCamera->getPosition().x, -1 * engineCamera->getPosition().y, -1 * engineCamera->getPosition().z);

//		glUseProgram(geometryShadersProgramInt);

		glBindVertexArray(quadVAO);
		//glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100); // 100 triangles of 6 vertices each
		glBindVertexArray(0);

    	glm::vec3 origin;
		origin.x = 0;
		origin.y = 0;
		origin.z = 0;

		VXLEVoxel *voxel = new VXLEVoxel(0,0,0);
	//	voxel->openGLDraw(origin);
		delete voxel;


		//drawCube();

	//	glm::vec3 origin;

		
		
/*		glm::vec3 origin;
		origin.x = 0;
		origin.y = 0;
		origin.z = 0;*/


		for (int i = 0; i < 32; i += 2) {
			for (int j = 0; j < 32; j += 2)
			{
				for (int k = 0; k < 32; k += 2)
				{
					VXLEVoxel *voxel = new VXLEVoxel(i, j, k);
					voxel->openGLDraw(origin);
					delete voxel;
				}
			}
		}

		

		drawGround(-100.0f);
		drawGround(100.0f);

		// Update Screen
		glfwSwapBuffers(window);

	
	}
}


int main(int argc, char** argv)
{
	GLFWwindow* window = initWindow(1024, 620);

	glewInit();

	GLint windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	engineSettings.containerWidth = windowWidth;
	engineSettings.containerHeight = windowHeight;

	engineControls = new VXLEFirstPersonControls();
	engineCamera = new VXLECamera(engineSettings, engineControls);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK); 

	if (NULL != window)
	{
		display(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}