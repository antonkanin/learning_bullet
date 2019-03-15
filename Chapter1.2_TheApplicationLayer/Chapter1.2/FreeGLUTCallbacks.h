/*ADD*/	#ifndef _FREEGLUTCALLBACKS_H_
/*ADD*/	#define _FREEGLUTCALLBACKS_H_
/*ADD*/	
/*ADD*/	#include "BulletOpenGLApplication.h"
/*ADD*/	
/*ADD*/	// global pointer to our application object
/*ADD*/	static BulletOpenGLApplication* g_pApp;
/*ADD*/	
/*ADD*/	// Various static functions that will be handed to FreeGLUT to be called
/*ADD*/	// during various events (our callbacks). Each calls an equivalent function
/*ADD*/	// in our (global) application object.
/*ADD*/	static void KeyboardCallback(unsigned char key, int x, int y) {
/*ADD*/		g_pApp->Keyboard(key, x, y);
/*ADD*/	}
/*ADD*/	static void KeyboardUpCallback(unsigned char key, int x, int y) {
/*ADD*/		g_pApp->KeyboardUp(key, x, y);
/*ADD*/	}
/*ADD*/	static void SpecialCallback(int key, int x, int y) {
/*ADD*/		g_pApp->Special(key, x, y);
/*ADD*/	}
/*ADD*/	static void SpecialUpCallback(int key, int x, int y) {
/*ADD*/		g_pApp->SpecialUp(key, x, y);
/*ADD*/	}
/*ADD*/	static void ReshapeCallback(int w, int h) {
/*ADD*/		g_pApp->Reshape(w, h);
/*ADD*/	}
/*ADD*/	static void IdleCallback() {
/*ADD*/		g_pApp->Idle();
/*ADD*/	}
/*ADD*/	static void MouseCallback(int button, int state, int x, int y) {
/*ADD*/		g_pApp->Mouse(button, state, x, y);
/*ADD*/	}
/*ADD*/	static void MotionCallback(int x,int y) {
/*ADD*/		g_pApp->Motion(x, y);
/*ADD*/	}
/*ADD*/	static void DisplayCallback(void) {
/*ADD*/		g_pApp->Display();
/*ADD*/	}
/*ADD*/	
/*ADD*/	// our custom-built 'main' function, which accepts a reference to a 
/*ADD*/	// BulletOpenGLApplication object.
/*ADD*/	int glutmain(int argc, char **argv, int width, int height, const char* title, BulletOpenGLApplication* pApp) {
/*ADD*/	    // store the application object so we can
/*ADD*/		// access it globally
/*ADD*/		g_pApp = pApp;
/*ADD*/	
/*ADD*/		// initialize the window
/*ADD*/		glutInit(&argc, argv);
/*ADD*/		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
/*ADD*/		glutInitWindowPosition(0, 0);
/*ADD*/		glutInitWindowSize(width, height);
/*ADD*/		glutCreateWindow(title);
/*ADD*/		glutSetOption (GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
/*ADD*/	
/*ADD*/		// perform custom initialization our of application
/*ADD*/		g_pApp->Initialize();
/*ADD*/	
/*ADD*/		// give our static
/*ADD*/		glutKeyboardFunc(KeyboardCallback);
/*ADD*/		glutKeyboardUpFunc(KeyboardUpCallback);
/*ADD*/		glutSpecialFunc(SpecialCallback);
/*ADD*/		glutSpecialUpFunc(SpecialUpCallback);
/*ADD*/		glutReshapeFunc(ReshapeCallback);
/*ADD*/		glutIdleFunc(IdleCallback);
/*ADD*/		glutMouseFunc(MouseCallback);
/*ADD*/		glutPassiveMotionFunc(MotionCallback);
/*ADD*/		glutMotionFunc(MotionCallback);
/*ADD*/		glutDisplayFunc(DisplayCallback );
/*ADD*/	
/*ADD*/		// perform one render before we launch the application
/*ADD*/		g_pApp->Idle();
/*ADD*/		
/*ADD*/		// hand application control over to the FreeGLUT library.
/*ADD*/		// This function remains in a while-loop until the
/*ADD*/		// application is exited.
/*ADD*/		glutMainLoop();
/*ADD*/		return 0;
/*ADD*/	}
/*ADD*/	#endif