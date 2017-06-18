#pragma once

#ifndef VXLEShaderProgram_H
#define VXLEShaderProgram_H

#include <GL/glew.h>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class VXLEShader {
public:
	VXLEShader(string shaderFile, int type);
	string shaderFile;
	int type;
};

class VXLEShaderProgram {
public:
	GLuint compile(VXLEShader oneshader);
	GLuint compile(vector<VXLEShader> shaders);
};

#endif //!VXLEShaderProgram_H