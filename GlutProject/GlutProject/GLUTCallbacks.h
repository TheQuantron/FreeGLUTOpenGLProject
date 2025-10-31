#pragma once
class OpenGLRenderer;

//Callbacks using custom functions in namespace
namespace GLUTCallbacks
{
	void Init(OpenGLRenderer* gl);
	void Display();
	void Timer(int prerefferedfresh);
	void Keyboard(unsigned char key, int x, int y);
	void Keyboard_Special(int key, int x, int y);
	void Mouse(int button, int state, int x, int y);
	void Mouse_Motion(int x, int y);
	void Mouse_PassiveMotion(int x, int y);
}

