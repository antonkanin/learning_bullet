/*REM*	#include "BulletOpenGLApplication.h" **/
/*ADD*/	#include "BasicDemo.h"
#include "FreeGLUTCallbacks.h"

int main(int argc, char** argv)
{
/*REM*	BulletOpenGLApplication demo; **/
/*ADD*/		BasicDemo demo;
	return glutmain(argc, argv, 1024, 768, "Introduction to Game Physics with Bullet Physics and OpenGL", &demo);
}