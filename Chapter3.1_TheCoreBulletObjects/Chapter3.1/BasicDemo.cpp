/*ADD*/	#include "BasicDemo.h"
/*ADD*/	
/*ADD*/	void BasicDemo::InitializePhysics() {
/*ADD*/		// create the collision configuration
/*ADD*/		m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
/*ADD*/		// create the dispatcher
/*ADD*/		m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);
/*ADD*/		// create the broadphase
/*ADD*/		m_pBroadphase = new btDbvtBroadphase();
/*ADD*/		// create the constraint solver
/*ADD*/		m_pSolver = new btSequentialImpulseConstraintSolver();
/*ADD*/		// create the world
/*ADD*/		m_pWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pCollisionConfiguration);
/*ADD*/	}
/*ADD*/	
/*ADD*/	void BasicDemo::ShutdownPhysics() {
/*ADD*/		delete m_pWorld;
/*ADD*/		delete m_pSolver;
/*ADD*/		delete m_pBroadphase;
/*ADD*/		delete m_pDispatcher;
/*ADD*/		delete m_pCollisionConfiguration;
/*ADD*/	}
