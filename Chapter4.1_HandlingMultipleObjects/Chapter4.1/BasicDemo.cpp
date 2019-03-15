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

/*REM*		// create a box shape of size (1,1,1) **/
/*REM*		btBoxShape* pBoxShape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f)); **/
/*REM*		// give our box an initial position of (0,0,0) **/
/*REM*		btTransform transform; **/
/*REM*		transform.setIdentity(); **/
/*REM*		transform.setOrigin(btVector3(0.0f, 0.0f, 0.0f)); **/
/*REM*		// create a motion state **/
/*REM*		m_pMotionState = new OpenGLMotionState(transform); **/
/*REM*		// create the rigid body construction info object, giving it a  **/
/*REM*		// mass of 1, the motion state, and the shape **/
/*REM*		btRigidBody::btRigidBodyConstructionInfo rbInfo(1.0f, m_pMotionState, pBoxShape); **/
/*REM*		btRigidBody* pRigidBody = new btRigidBody(rbInfo); **/
/*REM*		// inform our world that we just created a new rigid body for  **/
/*REM*		// it to manage **/
/*REM*		m_pWorld->addRigidBody(pRigidBody); **/

/*ADD*/	// create a ground plane
/*ADD*/	CreateGameObject(new btBoxShape(btVector3(1,50,50)), 0, btVector3(0.2f, 0.6f, 0.6f), btVector3(0.0f, 0.0f, 0.0f));
/*ADD*/
/*ADD*/	// create our original red box
/*ADD*/	CreateGameObject(new btBoxShape(btVector3(1,1,1)), 1.0, btVector3(1.0f, 0.2f, 0.2f), btVector3(0.0f, 10.0f, 0.0f));
/*ADD*/
/*ADD*/	// create a second box
/*ADD*/	CreateGameObject(new btBoxShape(btVector3(1,1,1)), 1.0, btVector3(0.0f, 0.2f, 0.8f), btVector3(1.25f, 20.0f, 0.0f));
}
