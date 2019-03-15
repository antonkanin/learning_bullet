/*ADD*/	#ifndef _GAMEOBJECT_H_
/*ADD*/	#define _GAMEOBJECT_H_
/*ADD*/	
/*ADD*/	#include "btBulletDynamicsCommon.h"
/*ADD*/	
/*ADD*/	#include "OpenGLMotionState.h"
/*ADD*/	
/*ADD*/	class GameObject {
/*ADD*/	public:
/*ADD*/		GameObject(btCollisionShape* pShape, float mass, const btVector3 &color, const btVector3 &initialPosition = btVector3(0,0,0), const btQuaternion &initialRotation = btQuaternion(0,0,1,1));
/*ADD*/		~GameObject();
/*ADD*/	
/*ADD*/		// accessors
/*ADD*/		btCollisionShape* GetShape() { return m_pShape; }
/*ADD*/	
/*ADD*/		btRigidBody* GetRigidBody() { return m_pBody; }
/*ADD*/	
/*ADD*/		btMotionState* GetMotionState() { return m_pMotionState; }
/*ADD*/	
/*ADD*/		void GetTransform(btScalar* transform) { 
/*ADD*/			if (m_pMotionState) m_pMotionState->GetWorldTransform(transform); 
/*ADD*/		}
/*ADD*/		
/*ADD*/		btVector3 GetColor() { return m_color; }
/*ADD*/	
/*ADD*/	protected:
/*ADD*/		btCollisionShape*  m_pShape;
/*ADD*/		btRigidBody*    m_pBody;
/*ADD*/		OpenGLMotionState*  m_pMotionState;
/*ADD*/		btVector3      m_color;
/*ADD*/	};
/*ADD*/	#endif
