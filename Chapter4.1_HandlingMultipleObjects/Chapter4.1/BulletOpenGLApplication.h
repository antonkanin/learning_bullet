#ifndef _BULLETOPENGLAPP_H_
#define _BULLETOPENGLAPP_H_

#include <Windows.h>
#include <GL/GL.h>
#include <GL/freeglut.h>

#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

// include our custom Motion State object
#include "OpenGLMotionState.h"

/*ADD*/	#include "GameObject.h"
/*ADD*/	#include <vector>
/*ADD*/	
/*ADD*/	// a convenient typedef to reference an STL vector of GameObjects
/*ADD*/	typedef std::vector<GameObject*> GameObjects;


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

	// rendering. Can be overrideen by derived classes
	virtual void RenderScene();

	// scene updating. Can be overridden by derived classes
	virtual void UpdateScene(float dt);

	// physics functions. Can be overrideen by derived classes (like BasicDemo)
	virtual void InitializePhysics() {};
	virtual void ShutdownPhysics() {};

	// camera functions
	void UpdateCamera();
	void RotateCamera(float &angle, float value);
	void ZoomCamera(float distance);

	// drawing functions
	void DrawBox(const btVector3 &halfSize);
/*ADD*/		void DrawShape(btScalar* transform, const btCollisionShape* pShape, const btVector3 &color);
/*ADD*/	
/*ADD*/		// object functions
/*ADD*/		GameObject* CreateGameObject(btCollisionShape* pShape, 
/*ADD*/				const float &mass, 
/*ADD*/				const btVector3 &color = btVector3(1.0f,1.0f,1.0f), 
/*ADD*/				const btVector3 &initialPosition = btVector3(0.0f,0.0f,0.0f), 
/*ADD*/				const btQuaternion &initialRotation = btQuaternion(0,0,1,1));

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

/*REM*	// our custom motion state **/
/*REM*	OpenGLMotionState* m_pMotionState; **/

	// a simple clock for counting time
	btClock m_clock;

/*ADD*/		// an array of our game objects
/*ADD*/		GameObjects m_objects;
};
#endif
