#include "Texture2D.h"
#include <fstream>
#include <iostream>

using namespace std;

//Constructor Initialisation
Texture2D::Texture2D()
{

}

//Texture2D Load function for textures and file initiation
bool Texture2D::Load(char* path, int width, int height)
{
	//variable declaration memory allocation
	char* temptextureData;
	int filesize;
	ifstream inFile;
	_width = width;
	_height = height;

	//Error print if the file cannot be accessed
	inFile.open(path, ios::binary);
	if (!inFile.good())
	{
		cerr << "Can't open texture file " << path << endl;
		return false;
	}

	//File checking, reading and placement handling
	inFile.seekg(0, ios::end);
	filesize = (int)inFile.tellg();
	temptextureData = new char[filesize];
	inFile.seekg(0, ios::beg);
	inFile.read(temptextureData, filesize);
	inFile.close();

	//OpenGL texture genereration within application
	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, temptextureData);
	
	//deletion of temporary data
	delete[] temptextureData;
	return true;
}

//Deconstructor initialisation
Texture2D::~Texture2D() {}