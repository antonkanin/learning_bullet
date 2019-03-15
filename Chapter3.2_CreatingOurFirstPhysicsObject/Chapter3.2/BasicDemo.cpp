#include "BasicDemo.h"

void BasicDemo::InitializePhysics() {
	// create the collision configuration
	m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
	// create the dispatcher
	m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);
	// create the broadphase
	m_pBroadphase = new btDbvtBroadphase();
	// create the constraint solver
	m_pSolver = new btSequentialImpulseConstraintSolver();
	// create the world
	m_pWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pCollisionConfiguration);

	// create our scene's physics objects
	CreateObjects();
}

void BasicDemo::ShutdownPhysics() {
	delete m_pWorld;
	delete m_pSolver;
	delete m_pBroadphase;
	delete m_pDispatcher;
	delete m_pCollisionConfiguration;
}

/*ADD*/	void BasicDemo::CreateObjects() {
/*ADD*/		// create a box shape of size (1,1,1)
/*ADD*/		btBoxShape* pBoxShape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
/*ADD*/		// give our box an initial position of (0,0,0)
/*ADD*/		btTransform transform;
/*ADD*/		transform.setIdentity();
/*ADD*/		transform.setOrigin(btVector3(0.0f, 0.0f, 0.0f));
/*ADD*/		// create a motion state
/*ADD*/		m_pMotionState = new OpenGLMotionState(transform);
/*ADD*/		// create the rigid body construction info object, giving it a 
/*ADD*/		// mass of 1, the motion state, and the shape
/*ADD*/		btRigidBody::btRigidBodyConstructionInfo rbInfo(1.0f, m_pMotionState, pBoxShape);
/*ADD*/		btRigidBody* pRigidBody = new btRigidBody(rbInfo);
/*ADD*/		// inform our world that we just created a new rigid body for 
/*ADD*/		// it to manage
/*ADD*/		m_pWorld->addRigidBody(pRigidBody);
/*ADD*/	}