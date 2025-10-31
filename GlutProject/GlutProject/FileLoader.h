#pragma once
#include <gl/GL.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "GL\freeglut.h"
#include "OpenGLRenderer.h"

using namespace std;

GLuint object;
float objectRot;
char ch = '1';

void loadOBJ(int pname, char* fname)
{
	FILE* fp;
	int read;
	GLfloat x, y, z;
	char ch;
	object = (GL_LIST_MODE);
	fp = fopen(fname, "r");
	
	if (!fp)
	{
		printf("Can't open file %s\n", fname);
		exit(1);
	}

	GL_POINT_SIZE;
	(object, GL_COMPILE);

	{
		glPushMatrix();
		glBegin(GL_POINTS);
		while (!(feof(fp)))
		{
			read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
			if (read == 4 && ch == 'v')
			{
				Vertex(x, y, z);
			}
		}
		glEnd();
	}
	glPopMatrix();
	glEndList();
	fclose(fp);
}

void reshape(int w, int h)
{
	glViewport(0, 0, 800, 800);
}
