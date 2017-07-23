#pragma once

#include <vector>
#include "VXLEVoxel.h"

#define DEFAULT_VOXEL_CHUNK_SIZE 24

using namespace std;

class VXLEVoxelChunk
{
public:
	VXLEVoxelChunk(GLfloat x, GLfloat y, GLfloat z);
	~VXLEVoxelChunk();

	GLfloat x = 0;
	GLfloat y = 0;
	GLfloat z = 0;

	GLfloat * verticesArray();
	GLint verticesArraySize();

	GLfloat * colorsArray();
	GLint colorsArraySize();

	void freeVoxels();
	void fillFullWithVoxels();


private:
	//vector<VXLEVoxel *> voxels_;
	VXLEVoxel* voxels_[DEFAULT_VOXEL_CHUNK_SIZE][DEFAULT_VOXEL_CHUNK_SIZE][DEFAULT_VOXEL_CHUNK_SIZE];

	vector<GLfloat> vertices_;
	vector<GLfloat> colors_;

	int chunkSize_;
};

