#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"

class Cube : public SceneObject
{
private:

	//Cube class position variables
	float x;
	float y;
	float z;

public:
	//Cube constructor/destructor declaration
	Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Cube();

	//Main functions
	//void Draw();
	void Update();
	//void DrawMaterial(Material* _material);
};
