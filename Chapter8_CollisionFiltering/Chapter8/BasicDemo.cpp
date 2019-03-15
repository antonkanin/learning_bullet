#include "BasicDemo.h"

BasicDemo::BasicDemo()
:
BulletOpenGLApplication(),
m_bApplyForce(false),
m_pExplosion(0),
m_bCanExplode(true) {

}

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

	// create our red box, but store the pointer for future usage
	m_pBox = CreateGameObject(new btBoxShape(btVector3(1,1,1)), 1.0, btVector3(1.0f, 0.2f, 0.2f), btVector3(0.0f, 10.0f, 0.0f));

	// create a second box
	CreateGameObject(new btBoxShape(btVector3(1,1,1)), 1.0, btVector3(0.0f, 0.2f, 0.8f), btVector3(1.25f, 20.0f, 0.0f));

	// create a trigger volume
	m_pTrigger = new btCollisionObject();
	// create a box for the trigger's shape
	m_pTrigger->setCollisionShape(new btBoxShape(btVector3(1,0.25,1)));
	// set the trigger's position
	btTransform triggerTrans;
	triggerTrans.setIdentity();
	triggerTrans.setOrigin(btVector3(0,1.5,0));
	m_pTrigger->setWorldTransform(triggerTrans);
	// flag the trigger to ignore contact responses
	m_pTrigger->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
	// add the trigger to our world
	m_pWorld->addCollisionObject(m_pTrigger);

	// create a yellow sphere
	CreateGameObject(new btSphereShape(1.0f), 1.0, btVector3(0.7f, 0.7f, 0.0f), btVector3(-5.0, 10.0f, 0.0f));

	// create a green cylinder
	CreateGameObject(new btCylinderShape(btVector3(1,1,1)), 1.0, btVector3(0.0f, 0.7f, 0.0f), btVector3(-2, 10.0f, 0.0f));

	// create a vertex cloud defining a square-based pyramid
	btVector3 points[5] = {btVector3(-0.5,1,1),
		btVector3(-0.5,1,-1),
		btVector3(-0.5,-1,1),
		btVector3(-0.5,-1,-1),
		btVector3(1,0,0)};
	// create our convex hull
	btConvexHullShape* pShape = new btConvexHullShape(&points[0].getX(),5);
	// initialize the object as a polyhedron
	pShape->initializePolyhedralFeatures();
	// create the game object using our convex hull shape
	CreateGameObject(pShape, 1.0, btVector3(1,1,1), btVector3(5, 15, 0));

	// create two shapes for the rod and the load
	btCollisionShape* pRod = new btBoxShape(btVector3(1.5f, 0.2f, 0.2f));
	btCollisionShape* pLoad = new btSphereShape(0.5f);
	// create a transform we'll use to set each object's position
	btTransform trans;
	trans.setIdentity();
	// create our compound shape
	btCompoundShape* pCompound = new btCompoundShape();
	// add the rod
	pCompound->addChildShape(trans, pRod);
	trans.setOrigin(btVector3(-1.75f, 0.0f, 0.0f));
	// add the top load
	pCompound->addChildShape(trans, pLoad);
	trans.setIdentity();
	// add the bottom load
	trans.setOrigin(btVector3(1.75f, 0.0f, 0.0f));
	pCompound->addChildShape(trans, pLoad);
	// create a game object using the compound shape
	CreateGameObject(pCompound, 2.0f, btVector3(0.8,0.4,0.1), btVector3(-4, 10.0f, 0.0f));

}

void BasicDemo::CollisionEvent(btRigidBody* pBody0, btRigidBody* pBody1) {
	// did the box collide with the trigger?
	if (pBody0 == m_pBox->GetRigidBody() && pBody1 == m_pTrigger ||
		pBody1 == m_pBox->GetRigidBody() && pBody0 == m_pTrigger) {
			// if yes, create a big green box nearby
			CreateGameObject(new btBoxShape(btVector3(2,2,2)), 2.0, btVector3(0.3, 0.7, 0.3), btVector3(5, 10, 0));
	}

	// Impulse testing
	if (pBody0 == m_pExplosion || pBody1 == m_pExplosion) {
		// get the pointer of the other object
		btRigidBody* pOther;
		pBody0 == m_pExplosion ? pOther = (btRigidBody*)pBody1 : pOther = (btRigidBody*)pBody0;
		// wake the object up
		pOther->setActivationState(ACTIVE_TAG);
		// calculate the vector between the object and
		// the center of the explosion
		btVector3 dir = pOther->getWorldTransform().getOrigin() - m_pExplosion->getWorldTransform().getOrigin();
		// get the distance
		float dist = dir.length();
		// calculate the impulse strength
		float strength = EXPLOSION_STRENGTH;
		// follow an inverse-distance rule
		if (dist != 0.0) strength /= dist;
		// normalize the direction vector
		dir.normalize();
		// apply the impulse
		pOther->applyCentralImpulse(dir * strength);
	}
}

void BasicDemo::Keyboard(unsigned char key, int x, int y) {
	// call the base implementation first
	BulletOpenGLApplication::Keyboard(key, x, y);
	switch(key) {
	// Force testing
	case 'g': 
		{
			// if 'g' is held down, apply a force
			m_bApplyForce = true; 
			// prevent the box from deactivating
			m_pBox->GetRigidBody()->setActivationState(DISABLE_DEACTIVATION);
			break;
		}
	// Impulse testing
	case 'e':
		{
			// don't create a new explosion if one already exists
			// or we haven't released the key, yet
			if (m_pExplosion || !m_bCanExplode) break;
			// don't let us create another explosion until the key is released
			m_bCanExplode = false;
			// create a collision object for our explosion
			m_pExplosion = new btCollisionObject();
			m_pExplosion->setCollisionShape(new btSphereShape(3.0f));
			// get the position that we clicked
			RayResult result;
			Raycast(m_cameraPosition, GetPickingRay(x, y), result, true);
			// create a transform from the hit point
			btTransform explodeTrans;
			explodeTrans.setIdentity();
			explodeTrans.setOrigin(result.hitPoint);
			m_pExplosion->setWorldTransform(explodeTrans);
			// set the collision flag
			m_pExplosion->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
			// add the explosion trigger to our world
			m_pWorld->addCollisionObject(m_pExplosion);
			break;
		}
	}
}

void BasicDemo::KeyboardUp(unsigned char key, int x, int y) {
	// call the base implementation first
	BulletOpenGLApplication::KeyboardUp(key, x, y);
	switch(key) {
	// Force testing
	case 'g': 
		{
			// if 'g' is let go, stop applying the force
			m_bApplyForce = false; 
			// allow the object to deactivate again
			m_pBox->GetRigidBody()->forceActivationState(ACTIVE_TAG); 
			break;
		}
	// Impulse testing
	case 'e': m_bCanExplode = true; break;
	}
}

void BasicDemo::UpdateScene(float dt) {
	// call the base implementation first
	BulletOpenGLApplication::UpdateScene(dt);

	// Force testing
	if (m_bApplyForce) {
		if (!m_pBox) return;
		// apply a central upwards force that exceeds gravity
		m_pBox->GetRigidBody()->applyCentralForce(btVector3(0, 20, 0));
	}

	// Impulse testing
	if (m_pExplosion) {
		// destroy the explosion object after one iteration
		m_pWorld->removeCollisionObject(m_pExplosion);
		delete m_pExplosion;
		m_pExplosion = 0;
	}
}