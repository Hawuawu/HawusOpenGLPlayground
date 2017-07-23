#include "stdafx.h"
#include "VXLEVoxelChunk.h"


VXLEVoxelChunk::VXLEVoxelChunk(GLfloat x, GLfloat y, GLfloat z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


VXLEVoxelChunk::~VXLEVoxelChunk()
{
}

GLfloat * VXLEVoxelChunk::verticesArray()
{
	return &vertices_[0];
}
GLint VXLEVoxelChunk::verticesArraySize()
{
	return vertices_.size();
}

GLfloat * VXLEVoxelChunk::colorsArray()
{
	return &colors_[0];
}
GLint VXLEVoxelChunk::colorsArraySize()
{
	return colors_.size();
}


void VXLEVoxelChunk::freeVoxels() {
	
	for (int x = 0; x < DEFAULT_VOXEL_CHUNK_SIZE; x++) {
		for (int y = 0; y < DEFAULT_VOXEL_CHUNK_SIZE; y++) {
			for (int z = 0; z < DEFAULT_VOXEL_CHUNK_SIZE; z++) {
				delete voxels_[x][y][z];
			}
		}
	}

	vertices_.clear();
	colors_.clear();
}

void VXLEVoxelChunk::fillFullWithVoxels()
{
	freeVoxels();

	vector<GLfloat> vertices;
	vector<GLfloat> colors;

	for (int x = 0; x < DEFAULT_VOXEL_CHUNK_SIZE; x++) {
		for (int y = 0; y < DEFAULT_VOXEL_CHUNK_SIZE; y++) {
			for (int z = 0; z < DEFAULT_VOXEL_CHUNK_SIZE; z++) {
				VXLEVoxel *v = new VXLEVoxel((this->x * DEFAULT_VOXEL_CHUNK_SIZE)+x, (this->y* DEFAULT_VOXEL_CHUNK_SIZE) +y, (this->z* DEFAULT_VOXEL_CHUNK_SIZE) +z);
				voxels_[x][y][z] = v;

				if (y > 0 && y < DEFAULT_VOXEL_CHUNK_SIZE - 1 && x > 0 && x < DEFAULT_VOXEL_CHUNK_SIZE - 1 && z > 0 && z < DEFAULT_VOXEL_CHUNK_SIZE - 1 ) {
					v->enabled = false;
				}


				bool verticesCorrection = false;

				if (x > 0 && v->enabled) {
					VXLEVoxel *v = voxels_[x - 1][y][z];
					//previous left;
				}

				if (z > 0 && v->enabled) {
					VXLEVoxel *v = voxels_[x][y][z - 1];
					//previous back
				}

				if (y > 0 && v->enabled) {
					VXLEVoxel *v = voxels_[x][y - 1][z];
					//previous top
				}

				/* 
				Todo: Optimatization if left side touch previous voxel right side, if front touches previous voxel back or, when bottom touches previous voxel top
				*/

				if (!verticesCorrection && v->enabled) {
					VXLEVoxelMesh mesh = v->getMesh();

					GLfloat *vert = mesh.vertices;
					GLfloat *col = mesh.colors;

					vector<GLfloat> vv;
					vv.assign(vert, vert + VOXEL_VERTICES_COUNT);

					vector<GLfloat> cv;
					cv.assign(col, col + VOXEL_VERTICES_COUNT);

					vertices.insert(vertices.end(), vv.begin(), vv.end());
					colors.insert(colors.end(), cv.begin(), cv.end());
				}
			}
		}
	}

	vertices_ = vertices;
	colors_ = colors;
}