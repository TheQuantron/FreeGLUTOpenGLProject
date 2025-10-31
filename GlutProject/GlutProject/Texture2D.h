#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

class Texture2D
{
private:
	//Texture2D pointers
	GLuint _textureID;
	int _width, _height;

public:
	//Texture2D class constructor/destructor
	Texture2D();
	~Texture2D();

	bool Load(char* path, int width, int height);

	GLuint GetID() const { return _textureID; }
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }
};