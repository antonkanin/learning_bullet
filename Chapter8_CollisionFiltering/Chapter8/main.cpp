#include "BasicDemo.h"
/*ADD*/	#include "CollisionFilteringDemo.h"
#include "FreeGLUTCallbacks.h"

int main(int argc, char** argv)
{
	/* swap these statements to launch a different demo */
/*ADD*/		//BasicDemo demo;
/*ADD*/		CollisionFilteringDemo demo;
	return glutmain(argc, argv, 1024, 768, "Introduction to Game Physics with Bullet Physics and OpenGL", &demo);
}