#include "BasicDemo.h"
#include "CollisionFilteringDemo.h"
/*ADD*/	#include "SoftBodyDemo.h"
#include "FreeGLUTCallbacks.h"

int main(int argc, char** argv)
{
	/* swap these statements to launch a different demo */
	//BasicDemo demo;
/*ADD*/		//CollisionFilteringDemo demo;
/*ADD*/ SoftBodyDemo demo;
	return glutmain(argc, argv, 1024, 768, "Introduction to Game Physics with Bullet Physics and OpenGL", &demo);
}