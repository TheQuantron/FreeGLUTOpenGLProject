#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "Texture2D.h"

//SceneObject class declaration
class SceneObject
{
private:
	//Class transform pointers

protected:
	//Class pointers
	Mesh* _mesh;
	Texture2D* _texture;
	GLfloat _rotation;
	Vector3 _position;

public:
	//Class pointer
	Material* _material;

	//SceneObject constructor/destructor declaration
	SceneObject(Mesh* mesh, Texture2D* texture);
	virtual ~SceneObject();
	
	//Main functions
	virtual void Update();
	virtual void Draw();
	void DrawMaterial();
};

