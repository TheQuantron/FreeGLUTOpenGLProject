#include "OpenGLRenderer.h"
#include "GLUTCallbacks.h"

//Constructor initialisation. Rendering prerequisites, GLUT and OpenGL function setup
OpenGLRenderer::OpenGLRenderer(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

		glutInitWindowSize(1600, 1600);
	glutInitWindowPosition(0, 0);
//GLUT window initialisation
	glutCreateWindow("Simple OpenGL Program");
	//glutFullScreen();
	InitGL(argc, argv);

	//OpenGL functions
	glMatrixMode(GL_PROJECTION);
	//add camera stuff
	glLoadIdentity();
	glViewport(0, 0, 1600, 1600);
	gluPerspective(45, 1, 1, 1000); //FOV, aspect ratio, front clip plane, far clip plane
	glMatrixMode(GL_MODELVIEW);
	//GLUT functions
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(16, GLUTCallbacks::Timer, 16);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutSpecialFunc(GLUTCallbacks::Keyboard_Special);
	glutMouseFunc(GLUTCallbacks::Mouse);
	glutMotionFunc(GLUTCallbacks::Mouse_Motion);
	glutPassiveMotionFunc(GLUTCallbacks::Mouse_PassiveMotion);
	
	Mesh* cubeMesh = MeshLoad::Load((char*)"cube.txt");
	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Penguins.raw", 512, 512);

	for (int i = 0; i < 500; i++)
	{
		_objects[i] = new Cube(cubeMesh, texture,
			((rand() % 400) / 10.0f) - 20.0f,
			((rand()) % 200 / 10.0f),
			-(rand() % 1000) / 10.0f);
	}

	rotation = 0.0f;
	_camera = new Camera();
	_lightPosition = new Vector4();
	_lightData = new Lighting();
	InitObjects(_lightPosition, _lightData);

	glutMainLoop();
}

//Lighting initialisation and face culling
void OpenGLRenderer::InitGL(int argc, char* argv[])
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glMatrixMode(GL_MODELVIEW);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

//Lighting initialisation and data setup
void OpenGLRenderer::InitObjects(Vector4* _lightPosition, Lighting* _lightData)
{
	//_lightPosition = new Vector4();
	_lightPosition->x = .0;
	_lightPosition->y = .0;
	_lightPosition->z = 1.0;
	_lightPosition->w = .0;

	//_lightData = new Lighting();
	_lightData->ambient.x = .2;
	_lightData->ambient.y = .2;
	_lightData->ambient.z = .2;
	_lightData->ambient.w = 1.0;
	_lightData->diffuse.x = .8;
	_lightData->diffuse.y = .8;
	_lightData->diffuse.z = .8;
	_lightData->diffuse.w = 1.0;
	_lightData->specular.x = .2;
	_lightData->specular.y = .2;
	_lightData->specular.z = .2;
	_lightData->specular.w = 1.0;
}

//Display function. Clears colour and depth buffers. Sends new position and colour data. Flushes and swaps buffer
void OpenGLRenderer::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(.5, .6, .6, 0);
		//Text Rendering
		Vector3 v = { -1.4f, .7f, -1.0f };
		Colour c = { .0f, 1.0f, .0f };
		DrawString((char*)"WE HAVE PRINTED TEXT! HUZZAH!", &v, &c);
		//_sceneObject->DrawMaterial();
		glutSolidTeapot(_teapotSize);
		for (int i = 0; i < 500; i++)
		{
			_objects[i]->Draw();
		}
	glFlush();
	glutSwapBuffers();
}

//Timer measuring time  -_-
void OpenGLRenderer::Timer() {}

//Standard Update function checking light data and posting to display
void OpenGLRenderer::Update()
{
	_camera->Update();
	_camera->eye.x = _positionX;
	_camera->eye.y = _positionY;
	_camera->eye.z = _positionZ;
	for (int i = 0; i < 500; i++)
	{
		_objects[i]->Update();
	}

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->ambient.x, _lightData->ambient.y, _lightData->ambient.z, _lightData->diffuse.w));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->diffuse.x, _lightData->diffuse.y, _lightData->diffuse.z, _lightData->diffuse.w));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->specular.x, _lightData->specular.y, _lightData->specular.z, _lightData->specular.w));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x, _lightPosition->y, _lightPosition->z, _lightPosition->w));

	glutPostRedisplay(); //Needs to be the last function called. When done updating all data, render new frame
}

//Camera movement using keyboard WASD commands
void OpenGLRenderer::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		_positionY += .1f;
	}

	else if (key == 's')
	{
		_positionY -= .1f;
	}

	if (key == 'a')
	{
		_positionX -= .1f;
	}

	else if (key == 'd')
	{
		_positionX += .1f;
	}

	if (key == 'q')
	{
		_teapotSize += .1f;
	}

	else if (key == 'e')
	{
		_teapotSize -= .1f;
	}
}

void OpenGLRenderer::Keyboard_Special(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		_positionY += .1f;
	}

	else if (key == GLUT_KEY_DOWN)
	{
		_positionY -= .1f;
	}

	if (key == GLUT_KEY_LEFT)
	{
		_positionX -= .1f;
	}

	else if (key == GLUT_KEY_RIGHT)
	{
		_positionX += .1f;
	}
}

void OpenGLRenderer::Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{

	}
}

void OpenGLRenderer::Mouse_Motion(int x, int y)
{
	if (INPUT_MOUSE)
	{

	}
}

void OpenGLRenderer::Mouse_PassiveMotion(int x, int y)
{
	if (INPUT_MOUSE)
	{

	}
}

//Standard polygon draw function using backface culling + rotational and colour data
//void OpenGLRenderer::DrawPolygon()
//{
//	glPushMatrix();
//	glRotatef(rotation, .0f, .0f, -1.0f);
//
//	glBegin(GL_POLYGON);
//	{
//		glColor4f(1.0, 1.0, 1.0, 1.0);
//		glVertex2f(-.75, .5);
//		glVertex2f(.75, .5);
//		glVertex2f(.75, -.5);
//		glVertex2f(-.75, -.5);
//		glEnd();
//	}
//
//	glPopMatrix();
//}

//Standard polygon draw function using translation, rotation and colour data
//void OpenGLRenderer::DrawPolygon(GLfloat x, GLfloat y, GLfloat z, float rotationOffset)
//{
//	glPushMatrix();
//	glTranslatef(x - _positionX, y - _positionY, z - _positionZ);
//	glRotatef(rotation * rotationOffset, .0f, .0f, -1.0f);
//
//	glBegin(GL_POLYGON);
//	{
//		glColor4f(1.0, .0, .0, .0);
//		glVertex2f(-.25, .25);
//		glVertex2f(.25, .25);
//
//		glColor4f(.0, 1.0, .0, .0);
//		glVertex2f(.25, .25);
//
//		glColor4f(.0, .0, 1.0, .0);
//		glVertex2f(-.25, .25);
//		glEnd();
//	}
//	glPopMatrix();
//}

//Draws text into the render window
void OpenGLRenderer::DrawString(const char* text, Vector3* position, Colour* colour)
{
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(.0f, .0f);
	glutBitmapString(GLUT_BITMAP_HELVETICA_10, (unsigned char*)text);
	glPopMatrix();
}

//Destructor initialisation. Pointers nulled and deleted
OpenGLRenderer::~OpenGLRenderer(void)
{
	//delete _camera;
	//_camera = nullptr;
	//delete _lightPosition;
	//_lightPosition = nullptr;
	//delete _lightData;
	//_lightData = nullptr;
	//delete _objects[1000];//add sceneobject 1000 pointer here too
}
