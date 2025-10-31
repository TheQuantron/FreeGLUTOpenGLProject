#include "GLUTCallbacks.h"
#include "OpenGLRenderer.h"

namespace GLUTCallbacks
{
	namespace
	{
		OpenGLRenderer* openGLRenderer = nullptr;
	}

	void Init(OpenGLRenderer* gl)
	{
		openGLRenderer = gl;
	}

	void Display()
	{
		if (openGLRenderer != nullptr)
		{
			openGLRenderer->Display();
		}
	}

	void Timer(int prefferedfresh)
	{
		if (openGLRenderer != nullptr)
		{
			int updateTime = glutGet(GLUT_ELAPSED_TIME);
			openGLRenderer->Update();
			updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
			glutTimerFunc(prefferedfresh - updateTime, GLUTCallbacks::Timer, prefferedfresh);
		}
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		if (openGLRenderer != nullptr)
		{
			openGLRenderer->Keyboard(key, x, y);
		}
	}

	void Keyboard_Special(int key, int x, int y)
	{
		if (openGLRenderer != nullptr)
		{
			openGLRenderer->Keyboard(key, x, y);
		}
	}

	void Mouse(int button, int state, int x, int y)
	{
		if (openGLRenderer != nullptr)
		{
			openGLRenderer->Mouse(button, state, x, y);
		}
	}

	void Mouse_Motion(int x, int y)
	{
		if (openGLRenderer != nullptr)
		{
			openGLRenderer->Mouse_Motion(x, y);
		}
	}

	void Mouse_PassiveMotion(int x, int y)
	{
		if (openGLRenderer != nullptr)
		{
			openGLRenderer->Mouse_PassiveMotion(x, y);
		}
	}
}
