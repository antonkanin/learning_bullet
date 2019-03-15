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

void BasicDemo::CreateObjects() {
	// create a ground plane
	CreateGameObject(new btBoxShape(btVector3(1,50,50)), 0, btVector3(0.2f, 0.6f, 0.6f), btVector3(0.0f, 0.0f, 0.0f));
/*REM*	// create our original red box */
/*REM*	CreateGameObject(new btBoxShape(btVector3(1,1,1)), 1.0, btVector3(1.0f, 0.2f, 0.2f), btVector3(0.0f, 10.0f, 0.0f)); */

/*ADD*/ // create our red box, but store the pointer for future usage
/*ADD*/	m_pBox = CreateGameObject(new btBoxShape(btVector3(1,1,1)), 1.0, btVector3(1.0f, 0.2f, 0.2f), btVector3(0.0f, 10.0f, 0.0f));

	// create a second box
	CreateGameObject(new btBoxShape(btVector3(1,1,1)), 1.0, btVector3(0.0f, 0.2f, 0.8f), btVector3(1.25f, 20.0f, 0.0f));

/*ADD*/		// create a trigger volume
/*ADD*/		m_pTrigger = new btCollisionObject();
/*ADD*/		// create a box for the trigger's shape
/*ADD*/		m_pTrigger->setCollisionShape(new btBoxShape(btVector3(1,0.25,1)));
/*ADD*/		// set the trigger's position
/*ADD*/		btTransform triggerTrans;
/*ADD*/		triggerTrans.setIdentity();
/*ADD*/		triggerTrans.setOrigin(btVector3(0,1.5,0));
/*ADD*/		m_pTrigger->setWorldTransform(triggerTrans);
/*ADD*/		// flag the trigger to ignore contact responses
/*ADD*/		m_pTrigger->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
/*ADD*/		// add the trigger to our world
/*ADD*/		m_pWorld->addCollisionObject(m_pTrigger);
}

/*ADD*/	void BasicDemo::CollisionEvent(btRigidBody* pBody0, btRigidBody* pBody1) {
/*ADD*/		// did the box collide with the trigger?
/*ADD*/		if (pBody0 == m_pBox->GetRigidBody() && pBody1 == m_pTrigger ||
/*ADD*/			pBody1 == m_pBox->GetRigidBody() && pBody0 == m_pTrigger) {
/*ADD*/				// if yes, create a big green box nearby
/*ADD*/				CreateGameObject(new btBoxShape(btVector3(2,2,2)), 2.0, btVector3(0.3, 0.7, 0.3), btVector3(5, 10, 0));
/*ADD*/		}
/*ADD*/	}