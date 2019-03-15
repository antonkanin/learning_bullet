#ifndef _BULLETOPENGLAPP_H_
#define _BULLETOPENGLAPP_H_

#include <Windows.h>
#include <GL/GL.h>
#include <GL/freeglut.h>

#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

/*ADD*/	// include our custom Motion State object
/*ADD*/	#include "OpenGLMotionState.h"

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

/*ADD*/		// rendering. Can be overrideen by derived classes
/*ADD*/		virtual void RenderScene();
/*ADD*/	
/*ADD*/		// scene updating. Can be overridden by derived classes
/*ADD*/		virtual void UpdateScene(float dt);

	// physics functions. Can be overrideen by derived classes (like BasicDemo)
	virtual void InitializePhysics() {};
	virtual void ShutdownPhysics() {};

	// camera functions
	void UpdateCamera();
	void RotateCamera(float &angle, float value);
	void ZoomCamera(float distance);

	// drawing functions
	void DrawBox(btScalar* transform, const btVector3 &halfSize, const btVector3 &color = btVector3(1.0f, 1.0f, 1.0f));

protected:
	// camera control
	btVector3 m_cameraPosition; // the camera's current position
	btVector3 m_cameraTarget;	 // the camera's lookAt target
	float m_nearPlane; // minimum distance the camera will render
	float m_farPlane; // farthest distance the camera will render
	btVector3 m_upVector; // keeps the camera rotated correctly
	float m_cameraDistance; // distance from the camera to its target
	float m_cameraPitch; // pitch of the camera 
	float m_cameraYaw; // yaw of the camera

	int m_screenWidth;
	int m_screenHeight;

	// core Bullet components
	btBroadphaseInterface* m_pBroadphase;
	btCollisionConfiguration* m_pCollisionConfiguration;
	btCollisionDispatcher* m_pDispatcher;
	btConstraintSolver* m_pSolver;
	btDynamicsWorld* m_pWorld;

/*ADD*/		// our custom motion state
/*ADD*/		OpenGLMotionState* m_pMotionState;
/*ADD*/		
/*ADD*/		// a simple clock for counting time
/*ADD*/		btClock m_clock;

};
#endif
