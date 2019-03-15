/*ADD*/	#ifndef _OPENGLMOTIONSTATE_H_
/*ADD*/	#define _OPENGLMOTIONSTATE_H_
/*ADD*/	
/*ADD*/	#include "btBulletCollisionCommon.h"
/*ADD*/	
/*ADD*/	class OpenGLMotionState : public btDefaultMotionState {
/*ADD*/	public:
/*ADD*/		OpenGLMotionState(const btTransform &transform) : btDefaultMotionState(transform) {}
/*ADD*/	
/*ADD*/		void GetWorldTransform(btScalar* transform) {
/*ADD*/			btTransform trans;
/*ADD*/			getWorldTransform(trans);
/*ADD*/			trans.getOpenGLMatrix(transform);
/*ADD*/		}
/*ADD*/	};
/*ADD*/	
/*ADD*/	#endif