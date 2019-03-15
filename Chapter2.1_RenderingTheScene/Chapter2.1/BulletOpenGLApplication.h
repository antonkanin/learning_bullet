#ifndef _BULLETOPENGLAPP_H_
#define _BULLETOPENGLAPP_H_

#include <Windows.h>
#include <GL/GL.h>
#include <GL/freeglut.h>

/*ADD*/	#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

class BulletOpenGLApplication {
public:
	BulletOpenGLApplication();
	~BulletOpenGLApplication();
	void Initialize();
	// FreeGLUT callbacks //
	virtual void Keyboard(unsigned char key, int x, int y);
	virtual void KeyboardUp(unsigned char key, int x, int y);
	virtual void Special(int key, int x, int y);
	virtual void SpecialUp(int key, int x, int y);
	virtual void Reshape(int w, int h);
	virtual void Idle();
	virtual void Mouse(int button, int state, int x, int y);
	virtual void PassiveMotion(int x, int y);
	virtual void Motion(int x, int y);
	virtual void Display();

/*ADD*/		// camera functions
/*ADD*/		void UpdateCamera();
/*ADD*/	
/*ADD*/	protected:
/*ADD*/		// camera control
/*ADD*/		btVector3 m_cameraPosition; // the camera's current position
/*ADD*/		btVector3 m_cameraTarget;	 // the camera's lookAt target
/*ADD*/		float m_nearPlane; // minimum distance the camera will render
/*ADD*/		float m_farPlane; // farthest distance the camera will render
/*ADD*/		btVector3 m_upVector; // keeps the camera rotated correctly
/*ADD*/	
/*ADD*/		int m_screenWidth;
/*ADD*/		int m_screenHeight;
};
#endif
