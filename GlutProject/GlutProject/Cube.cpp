#include <iostream>
#include <fstream>
#include "Cube.h"

using namespace std;

//Arrays handling Cube data for vertices, colours, indices
//Vertex Cube::indexedVertices[] = { 1,1,1, -1,1,1, -1,-1,1, 1,-1,1, 1,-1,-1, 1,1,-1, -1,1,-1, -1,-1,-1 };
//Colour Cube::indexedColours[] = { 1,1,1, 1,1,0, 1,0,0, 1,0,1, 0,0,1, 0,1,1, 0,1,0, 0,0,0 };
//GLushort Cube::indices[] = { 0,1,2, 2,3,0, 0,3,4, 4,5,0, 0,5,6, 6,1,0, 1,6,7, 7,2,1, 7,4,3, 3,2,7, 4,7,6, 6,5,4 };

//Constructor initialisation. Position handling
Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	//specify sceneobject handles in relation to cube
	//_mesh = mesh;
	//_texture = texture;
	_rotation = 0;

	_position.x = x;
	_position.y = y;
	_position.z = z;
}

//Draw function for OpenGL material and position initialisation/handling
//void Cube::Draw()
//{
//
//}

//Cube standard Update function
void Cube::Update()
{
	_rotation += 5.0f;
	if (_rotation >= 360)
	{
		_rotation = 0;
	}
}

//Destructor initialisation
Cube::~Cube()
{
	delete _mesh;
	_mesh = nullptr;
}
