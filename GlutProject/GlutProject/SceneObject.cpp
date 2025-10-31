#include <fstream>
#include <iostream>
#include "SceneObject.h"

using namespace std;

//Constructor initialisation
SceneObject::SceneObject(Mesh* mesh, Texture2D* texture)
{
	_mesh = mesh;
	_texture = texture;
	//_texture = texture;
	//_mesh = mesh;
	DrawMaterial();
}

//SceneObject standard Update function
void SceneObject::Update()
{
	//_rotation = 5.0f;
}

//Material draw function using predefined data
void SceneObject::DrawMaterial()
{
	_material = new Material();
	_material->ambient.x = .8;
	_material->ambient.y = .05;
	_material->ambient.z = .05;
	_material->ambient.w = 1.0;
	_material->diffuse.x = .8;
	_material->diffuse.y = .05;
	_material->diffuse.z = .05;
	_material->diffuse.w = 1.0;
	_material->specular.x = 1.0;
	_material->specular.y = 1.0;
	_material->specular.z = 1.0;
	_material->specular.w = 1.0;
	_material->shininess = 100.0f;
}

//OpenGL SceneObject draw function
void SceneObject::Draw()
{
	if (_mesh != nullptr)
	{
		//glEnable(GL_NORMALIZE);
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
		glTexCoordPointer(3, GL_FLOAT, 0, _mesh->TexCoords);
		//glIndexPointer(GL_FLOAT, 0, _mesh->Indices);

		//DrawMaterial();

		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->ambient.x, _material->ambient.y, _material->ambient.z, _material->ambient.w));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->diffuse.x, _material->diffuse.y, _material->diffuse.z, _material->diffuse.w));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->specular.x, _material->specular.y, _material->specular.z, _material->specular.w));
		glMaterialfv(GL_FRONT, GL_SHININESS, &(_material->shininess));

		glPushMatrix();
			glTranslatef(_position.x, _position.y, _position.z);
			glRotatef(_rotation, 1.0f, .0f, .0f);
			glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
			//glDrawArrays(GL_TRIANGLES, 0, _mesh->IndexCount);
			//DrawMaterial();
		glPopMatrix();

		glDisableClientState(GL_NORMAL_ARRAY);
		//glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

//Namespace for loading mesh data from a file
namespace MeshLoad
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadNormals(ifstream& inFile, Mesh& mesh);
	void LoadColours(ifstream& inFile, Mesh& mesh);
	void LoadTexCoords(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFIle, Mesh& mesh);

	//Mesh function for vertices loading/handling
	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];
			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	//Mesh function for normals loading/handling
	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.NormalCount;

		if (mesh.NormalCount > 0)
		{
			mesh.Normals = new Vertex[mesh.NormalCount];
			for (int i = 0; i < mesh.NormalCount; i++)
			{
				inFile >> mesh.Normals[i].x;
				inFile >> mesh.Normals[i].y;
				inFile >> mesh.Normals[i].z;
			}
		}
	}

	//Mesh function for colours loading/handling
	void LoadColours(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.ColourCount;

		if (mesh.ColourCount > 0)
		{
			//Go back to the respective tutorial
			//mesh.Colours = new GLfloat[mesh.ColourCount];
			for (int i = 0; i < mesh.NormalCount; i++)
			{
				inFile >> mesh.Colours[i].r;
				inFile >> mesh.Colours[i].g;
				inFile >> mesh.Colours[i].b;
			}
		}
	}

	//Mesh function for texcoords loading/handling
	void LoadTexCoords(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.TexCoordsCount;

		if (mesh.TexCoordsCount > 0)
		{
			mesh.TexCoords = new TexCoord[mesh.TexCoordsCount];
			for (int i = 0; i < mesh.TexCoordsCount; i++)
			{
				inFile >> mesh.TexCoords[i].u;
				inFile >> mesh.TexCoords[i].v;
			}
		}
	}

	//Mesh function for indices loading/handling
	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.IndexCount;

		if (mesh.IndexCount > 0)
		{
			mesh.Indices = new GLushort[mesh.IndexCount];
			for (int i = 0; i < mesh.IndexCount; i++)
			{
				inFile >> mesh.Indices[i];
			}
		}
	}

	//Error and file handling
	Mesh* MeshLoad::Load(char* path)
	{
		
		Mesh* mesh = new Mesh();
		ifstream inFile;

		inFile.open(path);
		if (!inFile.good())
		{
			cerr << "Can't open file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh);
		LoadNormals(inFile, *mesh);
		//void LoadColours(ifstream & inFile, Mesh & mesh);
		LoadTexCoords(inFile, *mesh);
		LoadIndices(inFile, *mesh);

		inFile.close();

		return mesh;
	}
}

//Destructor initialisation
SceneObject::~SceneObject()
{
	//remove pointers for mesh + nullptr
	//_mesh = nullptr;
	//_texture = nullptr;
	//delete _material;
	//_material = nullptr;
}
