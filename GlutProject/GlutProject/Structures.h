#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"

struct Vector3
{
	float x, y, z;
};

struct Vertex
{
	GLfloat x, y, z;
};

struct Colour
{
	GLfloat r, g, b;
};

struct Vector4
{
	float x, y, z, w;
};

struct Lighting
{
	Vector4 ambient, diffuse, specular;
};

struct Material
{
	Vector4 ambient, diffuse, specular;
	float shininess;
};

struct TexCoord
{
	GLfloat u, v;
	TexCoord* TexCoords;
};

struct Mesh
{
	Vertex* Vertices;
	Vertex* Normals;
	Colour* Colours;
	GLushort* Indices;
	TexCoord* TexCoords;
	int VertexCount, NormalCount, ColourCount, IndexCount, TexCoordsCount;
};

namespace MeshLoad
{
	Mesh* Load(char* path);
};