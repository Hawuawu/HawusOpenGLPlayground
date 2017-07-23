#include "VXLEVoxel.h"

/*
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
}*/

VXLEVoxelMesh::VXLEVoxelMesh()
{

}

VXLESurface4::VXLESurface4() {
	a = glm::vec3{ 0, 0, 0 };
	b = glm::vec3{ 0, 0, 0 };
	c = glm::vec3{ 0, 0, 0 };
	d = glm::vec3{ 0, 0, 0 };
}

VXLESurface4::VXLESurface4(
	GLfloat ax, GLfloat ay, GLfloat az,
	GLfloat bx, GLfloat by, GLfloat bz,
	GLfloat cx, GLfloat cy, GLfloat cz,
	GLfloat dx, GLfloat dy, GLfloat dz
) {
	a = glm::vec3{ ax, ay, az };
	b = glm::vec3{ bx, by, bz };
	c = glm::vec3{ cx, cy, cz };
	d = glm::vec3{ dx, dy, dz };
}

VXLEVoxelColor::VXLEVoxelColor()
{
	red = 0;
	green = 0;
	blue = 0;
}

VXLEVoxelColor::VXLEVoxelColor(GLfloat r, GLfloat g, GLfloat b)
{
	red = r;
	green = g;
	blue = b;
}

VXLEVoxel::VXLEVoxel(int x, int y, int z) : x(x), y(y), z(z)
{
	front = VXLESurface4(
		x + 0.0, y + 0.0, z + 0.0,
		x + 1.0, y + 0.0, z + 0.0,
		x + 1.0, y + 1.0, z + 0.0,
		x + 0.0, y + 1.0, z + 0.0
	);

	back = VXLESurface4(
		x + 0.0, y + 0.0, z - 1.0,
		x + 1.0, y + 0.0, z - 1.0,
		x + 1.0, y + 1.0, z - 1.0,
		x + 0.0, y + 1.0, z - 1.0
	);

	left = VXLESurface4(
		x + 0.0, y + 0.0, z + 0.0,
		x + 0.0, y + 0.0, z - 1.0,
		x + 0.0, y + 1.0, z - 1.0,
		x + 0.0, y + 1.0, z + 0.0
	);

	right = VXLESurface4 (
		x + 1.0, y + 0.0, z + 0.0,
		x + 1.0, y + 0.0, z - 1.0,
		x + 1.0, y + 1.0, z - 1.0,
		x + 1.0, y + 1.0, z + 0.0
	);

	top = VXLESurface4(
		x + 0.0, y + 1.0, z + 0.0,
		x + 1.0, y + 1.0, z + 0.0,
		x + 1.0, y + 1.0, z - 1.0,
		x + 0.0, y + 1.0, z - 1.0
	);

	bottom = VXLESurface4(
		x + 0.0, y + 0.0, z + 0.0,
		x + 1.0, y + 0.0, z + 0.0,
		x + 1.0, y + 0.0, z - 1.0,
		x + 0.0, y + 0.0, z - 1.0
	);


	voxelColor = VXLEVoxelColor(1, 1, 1);
}

VXLEVoxelMesh VXLEVoxel::getMesh()
{
	VXLEVoxelMesh mesh;

	GLfloat vertices[VOXEL_VERTICES_COUNT] = {
		front.a.x, front.a.y, front.a.z,
		front.b.x, front.b.y, front.b.z,
		front.c.x, front.c.y, front.c.z,
		front.d.x, front.d.y, front.d.z,
		back.a.x, back.a.y, back.a.z,
		back.b.x, back.b.y, back.b.z,
		back.c.x, back.c.y, back.c.z,
		back.d.x, back.d.y, back.d.z,
		left.a.x, left.a.y, left.a.z,
		left.b.x, left.b.y, left.b.z,
		left.c.x, left.c.y, left.c.z,
		left.d.x, left.d.y, left.d.z,
		right.a.x, right.a.y, right.a.z,
		right.b.x, right.b.y, right.b.z,
		right.c.x, right.c.y, right.c.z,
		right.d.x, right.d.y, right.d.z,
		top.a.x, top.a.y, top.a.z,
		top.b.x, top.b.y, top.b.z,
		top.c.x, top.c.y, top.c.z,
		top.d.x, top.d.y, top.d.z,
		bottom.a.x, bottom.a.y, bottom.a.z,
		bottom.b.x, bottom.b.y, bottom.b.z,
		bottom.c.x, bottom.c.y, bottom.c.z,
		bottom.d.x, bottom.d.y, bottom.d.z,
	};

	memcpy(mesh.vertices, vertices, sizeof vertices);

	GLfloat colors[VOXEL_VERTICES_COUNT] = {
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue,
		voxelColor.red, voxelColor.green, voxelColor.blue
	};

	memcpy(mesh.colors, colors, sizeof colors);
	return mesh;
}
/*
GLfloat *VXLEVoxel::verticesArray()
{
	

	GLfloat *p = arr;
	return p;
}
int VXLEVoxel::verticesArraySize()
{
	return VOXEL_VERTICES_COUNT;
}

GLfloat *VXLEVoxel::colorsArray()
{
	

	GLfloat *p = arr;
	return p;
}

int VXLEVoxel::colorsArraySize()
{
	return VOXEL_VERTICES_COUNT;
}
*/
VXLEVoxel::~VXLEVoxel()
{

}