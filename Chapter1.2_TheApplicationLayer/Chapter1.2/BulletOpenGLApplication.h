/*ADD*/	#ifndef _BULLETOPENGLAPP_H_
/*ADD*/	#define _BULLETOPENGLAPP_H_
/*ADD*/	
/*ADD*/	#include <Windows.h>
/*ADD*/	#include <GL/GL.h>
/*ADD*/	#include <GL/freeglut.h>
/*ADD*/	
/*ADD*/	class BulletOpenGLApplication {
/*ADD*/	public:
/*ADD*/		BulletOpenGLApplication();
/*ADD*/		~BulletOpenGLApplication();
/*ADD*/		void Initialize();
/*ADD*/		// FreeGLUT callbacks //
/*ADD*/		virtual void Keyboard(unsigned char key, int x, int y);
/*ADD*/		virtual void KeyboardUp(unsigned char key, int x, int y);
/*ADD*/		virtual void Special(int key, int x, int y);
/*ADD*/		virtual void SpecialUp(int key, int x, int y);
/*ADD*/		virtual void Reshape(int w, int h);
/*ADD*/		virtual void Idle();
/*ADD*/		virtual void Mouse(int button, int state, int x, int y);
/*ADD*/		virtual void PassiveMotion(int x, int y);
/*ADD*/		virtual void Motion(int x, int y);
/*ADD*/		virtual void Display();
/*ADD*/	};
/*ADD*/	#endif
