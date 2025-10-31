#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Gl\freeglut.h"
#include "Structures.h"
#include "Camera.h"
#include "Cube.h"
#include "SceneObject.h"

//class declarations
class Cube;
class Camera;

class OpenGLRenderer
{
public:
	//Renderer Constructor/Destructor
	OpenGLRenderer(int argc, char* argv[]);
	~OpenGLRenderer();
	
	//Move to display and standard update functions
	void Display();
	void Update();

	//IO functions declaration
	void Keyboard(unsigned char key, int x, int y);
	void Keyboard_Special(int key, int x, int y);
	void Mouse(int button, int state, int x, int y);
	void Mouse_Motion(int x, int y);
	void Mouse_PassiveMotion(int x, int y);
	void Timer();

	//Lightning and OpenGL functions
	void InitGL(int argc, char* argv[]);
	void InitObjects(Vector4* _lightPosition, Lighting* _lightData);

	//Polygon and text Draw functions
	//void DrawPolygon();
	//void DrawPolygon(GLfloat x, GLfloat y, GLfloat z, float rotation);
	void DrawString(const char* text, Vector3* position, Colour* colour);

	//Cube draw functions
	//void DrawCube();
	//void DrawIndexedCube();
	
private:
	//Light data pointers
	Vector4* _lightPosition;
	Lighting* _lightData;

	//Position variables
	float movement;
	float rotation;

	//Camera pointers
	Cube* _cube;
	Camera* _camera;
	SceneObject* _sceneObject;
	SceneObject* _objects[500];

	//camera position
	GLfloat _positionX = 0;
	GLfloat _positionY = 0;
	GLfloat _positionZ = 0;
	GLfloat _teapotSize = 1;
};
