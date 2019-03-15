/*ADD*/	#include "GameObject.h"
/*ADD*/	GameObject::GameObject(btCollisionShape* pShape, float mass, const btVector3 &color, const btVector3 &initialPosition, const btQuaternion &initialRotation) {
/*ADD*/		// store the shape for later usage
/*ADD*/		m_pShape = pShape;
/*ADD*/	
/*ADD*/		// store the color
/*ADD*/		m_color = color;
/*ADD*/	
/*ADD*/		// create the initial transform
/*ADD*/		btTransform transform;
/*ADD*/		transform.setIdentity();
/*ADD*/		transform.setOrigin(initialPosition);
/*ADD*/		transform.setRotation(initialRotation);
/*ADD*/	
/*ADD*/		// create the motion state from the
/*ADD*/		// initial transform
/*ADD*/		m_pMotionState = new OpenGLMotionState(transform);
/*ADD*/	
/*ADD*/		// calculate the local inertia
/*ADD*/		btVector3 localInertia(0,0,0);
/*ADD*/	
/*ADD*/		// objects of infinite mass can't
/*ADD*/		// move or rotate
/*ADD*/		if (mass != 0.0f)
/*ADD*/			pShape->calculateLocalInertia(mass, localInertia);
/*ADD*/	
/*ADD*/		// create the rigid body construction
/*ADD*/		// info using the mass, motion state
/*ADD*/		// and shape
/*ADD*/		btRigidBody::btRigidBodyConstructionInfo cInfo(mass, m_pMotionState, pShape, localInertia);
/*ADD*/		
/*ADD*/		// create the rigid body
/*ADD*/		m_pBody = new btRigidBody(cInfo);
/*ADD*/	}
/*ADD*/	
/*ADD*/	GameObject::~GameObject() {
/*ADD*/		delete m_pBody;
/*ADD*/		delete m_pMotionState;
/*ADD*/		delete m_pShape;
/*ADD*/	}
