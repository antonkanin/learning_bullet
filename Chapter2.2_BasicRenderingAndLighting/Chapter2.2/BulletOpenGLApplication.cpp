#include "BulletOpenGLApplication.h"

BulletOpenGLApplication::BulletOpenGLApplication() 
:
m_cameraPosition(10.0f, 5.0f, 0.0f),
m_cameraTarget(0.0f, 0.0f, 0.0f),
m_upVector(0.0f, 1.0f, 0.0f),
m_nearPlane(1.0f),
m_farPlane(1000.0f)
{
}

BulletOpenGLApplication::~BulletOpenGLApplication() {}

void BulletOpenGLApplication::Initialize() {
	// this function is called inside glutmain() after
	// creating the window, but before handing control
	// to FreeGLUT

/*ADD*/		// create some floats for our ambient, diffuse, specular and position
/*ADD*/		GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // dark grey
/*ADD*/		GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // white
/*ADD*/		GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // white
/*ADD*/		GLfloat position[] = { 5.0f, 10.0f, 1.0f, 0.0f };
/*ADD*/		
/*ADD*/		// set the ambient, diffuse, specular and position for LIGHT0
/*ADD*/		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
/*ADD*/		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
/*ADD*/		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
/*ADD*/		glLightfv(GL_LIGHT0, GL_POSITION, position);
/*ADD*/	
/*ADD*/		glEnable(GL_LIGHTING); // enables lighting
/*ADD*/		glEnable(GL_LIGHT0); // enables the 0th light
/*ADD*/		glEnable(GL_COLOR_MATERIAL); // colors materials when lighting is enabled
/*ADD*/		
/*ADD*/		// enable specular lighting via materials
/*ADD*/		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
/*ADD*/		glMateriali(GL_FRONT, GL_SHININESS, 15);
/*ADD*/	
/*ADD*/		// enable smooth shading
/*ADD*/		glShadeModel(GL_SMOOTH);
/*ADD*/		
/*ADD*/		// enable depth testing to be 'less than'
/*ADD*/		glEnable(GL_DEPTH_TEST);
/*ADD*/		glDepthFunc(GL_LESS);

	// set the backbuffer clearing color to a lightish blue
	glClearColor(0.6, 0.65, 0.85, 0);
}
void BulletOpenGLApplication::Keyboard(unsigned char key, int x, int y) {}
void BulletOpenGLApplication::KeyboardUp(unsigned char key, int x, int y) {}
void BulletOpenGLApplication::Special(int key, int x, int y) {}
void BulletOpenGLApplication::SpecialUp(int key, int x, int y) {}

void BulletOpenGLApplication::Reshape(int w, int h) {
	// this function is called once during application intialization
	// and again every time we resize the window

	// grab the screen width/height
	m_screenWidth = w;
	m_screenHeight = h;
	// set the viewport
	glViewport(0, 0, w, h);
	// update the camera
	UpdateCamera();
}

void BulletOpenGLApplication::Idle() {
	// this function is called frequently, whenever FreeGlut
	// isn't busy processing its own events. It should be used
	// to perform any updating and rendering tasks

	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	// update the camera
	UpdateCamera();

/*ADD*/		// draw a simple box of size 1
/*ADD*/		// also draw it red
/*ADD*/		DrawBox(btVector3(1, 1, 1));

	// swap the front and back buffers
	glutSwapBuffers();
}

void BulletOpenGLApplication::Mouse(int button, int state, int x, int y) {}
void BulletOpenGLApplication::PassiveMotion(int x, int y) {}
void BulletOpenGLApplication::Motion(int x, int y) {}
void BulletOpenGLApplication::Display() {}

void BulletOpenGLApplication::UpdateCamera() {
	// exit in erroneous situations
	if (m_screenWidth == 0 && m_screenHeight == 0)
		return;
	
	// select the projection matrix
	glMatrixMode(GL_PROJECTION);
	// set it to the matrix-equivalent of 1
	glLoadIdentity();
	// determine the aspect ratio of the screen
	float aspectRatio = m_screenWidth / (float)m_screenHeight;
	// create a viewing frustum based on the aspect ratio and the
	// boundaries of the camera
	glFrustum (-aspectRatio * m_nearPlane, aspectRatio * m_nearPlane, -m_nearPlane, m_nearPlane, m_nearPlane, m_farPlane);
	// the projection matrix is now set

	// select the view matrix
	glMatrixMode(GL_MODELVIEW);
	// set it to '1'
	glLoadIdentity();
	// create a view matrix based on the camera's position and where it's
	// looking
	gluLookAt(m_cameraPosition[0], m_cameraPosition[1], m_cameraPosition[2], m_cameraTarget[0], m_cameraTarget[1], m_cameraTarget[2], m_upVector.getX(), m_upVector.getY(), m_upVector.getZ());
	// the view matrix is now set
}

/*ADD*/	void BulletOpenGLApplication::DrawBox(const btVector3 &halfSize, const btVector3 &color) {
/*ADD*/		float halfWidth = halfSize.x();
/*ADD*/		float halfHeight = halfSize.y();
/*ADD*/		float halfDepth = halfSize.z();
/*ADD*/	
/*ADD*/		// set the object's color
/*ADD*/		glColor3f(color.x(), color.y(), color.z());
/*ADD*/	
/*ADD*/		// create the vertex positions
/*ADD*/		btVector3 vertices[8]={	
/*ADD*/		btVector3(halfWidth,halfHeight,halfDepth),
/*ADD*/		btVector3(-halfWidth,halfHeight,halfDepth),
/*ADD*/		btVector3(halfWidth,-halfHeight,halfDepth),	
/*ADD*/		btVector3(-halfWidth,-halfHeight,halfDepth),	
/*ADD*/		btVector3(halfWidth,halfHeight,-halfDepth),
/*ADD*/		btVector3(-halfWidth,halfHeight,-halfDepth),	
/*ADD*/		btVector3(halfWidth,-halfHeight,-halfDepth),	
/*ADD*/		btVector3(-halfWidth,-halfHeight,-halfDepth)};
/*ADD*/	
/*ADD*/		// create the indexes for each triangle, using the 
/*ADD*/		// vertices above. Make it static so we don't waste 
/*ADD*/		// processing time recreating it over and over again
/*ADD*/		static int indices[36] = {
/*ADD*/			0,1,2,
/*ADD*/			3,2,1,
/*ADD*/			4,0,6,
/*ADD*/			6,0,2,
/*ADD*/			5,1,4,
/*ADD*/			4,1,0,
/*ADD*/			7,3,1,
/*ADD*/			7,1,5,
/*ADD*/			5,4,7,
/*ADD*/			7,4,6,
/*ADD*/			7,2,3,
/*ADD*/			7,6,2};
/*ADD*/	
/*ADD*/		// start processing vertices as triangles
/*ADD*/		glBegin (GL_TRIANGLES);
/*ADD*/	
/*ADD*/		// increment the loop by 3 each time since we create a 
/*ADD*/		// triangle with 3 vertices at a time.
/*ADD*/	
/*ADD*/		for (int i = 0; i < 36; i += 3) {
/*ADD*/			// get the three vertices for the triangle based
/*ADD*/			// on the index values set above
/*ADD*/			// use const references so we don't copy the object
/*ADD*/			// (a good rule of thumb is to never allocate/deallocate
/*ADD*/			// memory during *every* render/update call. This should 
/*ADD*/			// only happen sporadically)
/*ADD*/			const btVector3 &vert1 = vertices[indices[i]];
/*ADD*/			const btVector3 &vert2 = vertices[indices[i+1]];
/*ADD*/			const btVector3 &vert3 = vertices[indices[i+2]];
/*ADD*/	
/*ADD*/			// create a normal that is perpendicular to the 
/*ADD*/			// face (use the cross product)
/*ADD*/			btVector3 normal = (vert3-vert1).cross(vert2-vert1);
/*ADD*/			normal.normalize ();
/*ADD*/	
/*ADD*/			// set the normal for the subsequent vertices
/*ADD*/			glNormal3f(normal.getX(),normal.getY(),normal.getZ());
/*ADD*/	
/*ADD*/			// create the vertices
/*ADD*/			glVertex3f (vert1.x(), vert1.y(), vert1.z());
/*ADD*/			glVertex3f (vert2.x(), vert2.y(), vert2.z());
/*ADD*/			glVertex3f (vert3.x(), vert3.y(), vert3.z());
/*ADD*/		}
/*ADD*/	
/*ADD*/		// stop processing vertices
/*ADD*/		glEnd();
/*ADD*/	}