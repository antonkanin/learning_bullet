#include "BulletOpenGLApplication.h"

BulletOpenGLApplication::BulletOpenGLApplication() 
/*ADD*/	:
/*ADD*/	m_cameraPosition(10.0f, 5.0f, 0.0f),
/*ADD*/	m_cameraTarget(0.0f, 0.0f, 0.0f),
/*ADD*/	m_upVector(0.0f, 1.0f, 0.0f),
/*ADD*/	m_nearPlane(1.0f),
/*ADD*/	m_farPlane(1000.0f)
{
}

BulletOpenGLApplication::~BulletOpenGLApplication() {}

void BulletOpenGLApplication::Initialize() {
/*ADD*/		// this function is called inside glutmain() after
/*ADD*/		// creating the window, but before handing control
/*ADD*/		// to FreeGLUT
/*ADD*/	
/*ADD*/		// set the backbuffer clearing color to a lightish blue
/*ADD*/		glClearColor(0.6, 0.65, 0.85, 0);
}
void BulletOpenGLApplication::Keyboard(unsigned char key, int x, int y) {}
void BulletOpenGLApplication::KeyboardUp(unsigned char key, int x, int y) {}
void BulletOpenGLApplication::Special(int key, int x, int y) {}
void BulletOpenGLApplication::SpecialUp(int key, int x, int y) {}

void BulletOpenGLApplication::Reshape(int w, int h) {
/*ADD*/		// this function is called once during application intialization
/*ADD*/		// and again every time we resize the window
/*ADD*/	
/*ADD*/		// grab the screen width/height
/*ADD*/		m_screenWidth = w;
/*ADD*/		m_screenHeight = h;
/*ADD*/		// set the viewport
/*ADD*/		glViewport(0, 0, w, h);
/*ADD*/		// update the camera
/*ADD*/		UpdateCamera();
}

void BulletOpenGLApplication::Idle() {
/*ADD*/		// this function is called frequently, whenever FreeGlut
/*ADD*/		// isn't busy processing its own events. It should be used
/*ADD*/		// to perform any updating and rendering tasks
/*ADD*/	
/*ADD*/		// clear the backbuffer
/*ADD*/		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
/*ADD*/	
/*ADD*/		// update the camera
/*ADD*/		UpdateCamera();
/*ADD*/	
/*ADD*/		// swap the front and back buffers
/*ADD*/		glutSwapBuffers();
}

void BulletOpenGLApplication::Mouse(int button, int state, int x, int y) {}
void BulletOpenGLApplication::PassiveMotion(int x, int y) {}
void BulletOpenGLApplication::Motion(int x, int y) {}
void BulletOpenGLApplication::Display() {}

/*ADD*/	void BulletOpenGLApplication::UpdateCamera() {
/*ADD*/		// exit in erroneous situations
/*ADD*/		if (m_screenWidth == 0 && m_screenHeight == 0)
/*ADD*/			return;
/*ADD*/		
/*ADD*/		// select the projection matrix
/*ADD*/		glMatrixMode(GL_PROJECTION);
/*ADD*/		// set it to the matrix-equivalent of 1
/*ADD*/		glLoadIdentity();
/*ADD*/		// determine the aspect ratio of the screen
/*ADD*/		float aspectRatio = m_screenWidth / (float)m_screenHeight;
/*ADD*/		// create a viewing frustum based on the aspect ratio and the
/*ADD*/		// boundaries of the camera
/*ADD*/		glFrustum (-aspectRatio * m_nearPlane, aspectRatio * m_nearPlane, -m_nearPlane, m_nearPlane, m_nearPlane, m_farPlane);
/*ADD*/		// the projection matrix is now set
/*ADD*/	
/*ADD*/		// select the view matrix
/*ADD*/		glMatrixMode(GL_MODELVIEW);
/*ADD*/		// set it to '1'
/*ADD*/		glLoadIdentity();
/*ADD*/		// create a view matrix based on the camera's position and where it's
/*ADD*/		// looking
/*ADD*/		gluLookAt(m_cameraPosition[0], m_cameraPosition[1], m_cameraPosition[2], m_cameraTarget[0], m_cameraTarget[1], m_cameraTarget[2], m_upVector.getX(), m_upVector.getY(), m_upVector.getZ());
/*ADD*/		// the view matrix is now set
/*ADD*/	}