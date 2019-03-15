/*ADD*/	#include "BulletOpenGLApplication.h"
/*ADD*/	#include "FreeGLUTCallbacks.h"
/*ADD*/	
int main(int argc, char** argv)
{
/*ADD*/		BulletOpenGLApplication demo;
/*ADD*/		return glutmain(argc, argv, 1024, 768, "Introduction to Game Physics with Bullet Physics and OpenGL", &demo);
}