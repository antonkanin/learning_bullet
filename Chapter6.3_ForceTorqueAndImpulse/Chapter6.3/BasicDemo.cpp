#include "BasicDemo.h"

/*ADD*/ BasicDemo::BasicDemo()
/*ADD*/ :
/*ADD*/	BulletOpenGLApplication(),
/*ADD*/ m_bApplyForce(false),
/*ADD*/	m_pExplosion(0),
/*ADD*/ m_bCanExplode(true) {
/*ADD*/ 
/*ADD*/ }

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
}

void BasicDemo::CollisionEvent(btRigidBody* pBody0, btRigidBody* pBody1) {
	// did the box collide with the trigger?
	if (pBody0 == m_pBox->GetRigidBody() && pBody1 == m_pTrigger ||
		pBody1 == m_pBox->GetRigidBody() && pBody0 == m_pTrigger) {
			// if yes, create a big green box nearby
			CreateGameObject(new btBoxShape(btVector3(2,2,2)), 2.0, btVector3(0.3, 0.7, 0.3), btVector3(5, 10, 0));
	}

/*ADD*/		// Impulse testing
/*ADD*/	if (pBody0 == m_pExplosion || pBody1 == m_pExplosion) {
/*ADD*/		// get the pointer of the other object
/*ADD*/		btRigidBody* pOther;
/*ADD*/		pBody0 == m_pExplosion ? pOther = (btRigidBody*)pBody1 : pOther = (btRigidBody*)pBody0;
/*ADD*/		// wake the object up
/*ADD*/		pOther->setActivationState(ACTIVE_TAG);
/*ADD*/		// calculate the vector between the object and
/*ADD*/		// the center of the explosion
/*ADD*/		btVector3 dir = pOther->getWorldTransform().getOrigin() - m_pExplosion->getWorldTransform().getOrigin();
/*ADD*/		// get the distance
/*ADD*/		float dist = dir.length();
/*ADD*/		// calculate the impulse strength
/*ADD*/		float strength = EXPLOSION_STRENGTH;
/*ADD*/		// follow an inverse-distance rule
/*ADD*/		if (dist != 0.0) strength /= dist;
/*ADD*/		// normalize the direction vector
/*ADD*/		dir.normalize();
/*ADD*/		// apply the impulse
/*ADD*/		pOther->applyCentralImpulse(dir * strength);
/*ADD*/	}
}

/*ADD*/	void BasicDemo::Keyboard(unsigned char key, int x, int y) {
/*ADD*/		// call the base implementation first
/*ADD*/		BulletOpenGLApplication::Keyboard(key, x, y);
/*ADD*/		switch(key) {
/*ADD*/		// Force testing
/*ADD*/		case 'g': 
/*ADD*/			{
/*ADD*/				// if 'g' is held down, apply a force
/*ADD*/				m_bApplyForce = true; 
/*ADD*/				// prevent the box from deactivating
/*ADD*/				m_pBox->GetRigidBody()->setActivationState(DISABLE_DEACTIVATION);
/*ADD*/				break;
/*ADD*/			}
/*ADD*/		// Impulse testing
/*ADD*/		case 'e':
/*ADD*/			{
/*ADD*/				// don't create a new explosion if one already exists
/*ADD*/				// or we haven't released the key, yet
/*ADD*/				if (m_pExplosion || !m_bCanExplode) break;
/*ADD*/				// don't let us create another explosion until the key is released
/*ADD*/				m_bCanExplode = false;
/*ADD*/				// create a collision object for our explosion
/*ADD*/				m_pExplosion = new btCollisionObject();
/*ADD*/				m_pExplosion->setCollisionShape(new btSphereShape(3.0f));
/*ADD*/				// get the position that we clicked
/*ADD*/				RayResult result;
/*ADD*/				Raycast(m_cameraPosition, GetPickingRay(x, y), result, true);
/*ADD*/				// create a transform from the hit point
/*ADD*/				btTransform explodeTrans;
/*ADD*/				explodeTrans.setIdentity();
/*ADD*/				explodeTrans.setOrigin(result.hitPoint);
/*ADD*/				m_pExplosion->setWorldTransform(explodeTrans);
/*ADD*/				// set the collision flag
/*ADD*/				m_pExplosion->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
/*ADD*/				// add the explosion trigger to our world
/*ADD*/				m_pWorld->addCollisionObject(m_pExplosion);
/*ADD*/				break;
/*ADD*/			}
/*ADD*/
/*ADD*/		}
/*ADD*/	}
/*ADD*/	
/*ADD*/	void BasicDemo::KeyboardUp(unsigned char key, int x, int y) {
/*ADD*/		// call the base implementation first
/*ADD*/		BulletOpenGLApplication::KeyboardUp(key, x, y);
/*ADD*/		switch(key) {
/*ADD*/		// Force testing
/*ADD*/		case 'g': 
/*ADD*/			{
/*ADD*/				// if 'g' is let go, stop applying the force
/*ADD*/				m_bApplyForce = false; 
/*ADD*/				// allow the object to deactivate again
/*ADD*/				m_pBox->GetRigidBody()->forceActivationState(ACTIVE_TAG); 
/*ADD*/				break;
/*ADD*/			}
/*ADD*/		// Impulse testing
/*ADD*/		case 'e': m_bCanExplode = true; break;
/*ADD*/		}
/*ADD*/	}
/*ADD*/	
/*ADD*/	void BasicDemo::UpdateScene(float dt) {
/*ADD*/		// call the base implementation first
/*ADD*/		BulletOpenGLApplication::UpdateScene(dt);
/*ADD*/
/*ADD*/		// Force testing
/*ADD*/		if (m_bApplyForce) {
/*ADD*/			if (!m_pBox) return;
/*ADD*/			// apply a central upwards force that exceeds gravity
/*ADD*/			m_pBox->GetRigidBody()->applyCentralForce(btVector3(0, 20, 0));
/*ADD*/		}
/*ADD*/
/*ADD*/		// Impulse testing
/*ADD*/		if (m_pExplosion) {
/*ADD*/			// destroy the explosion object after one iteration
/*ADD*/			m_pWorld->removeCollisionObject(m_pExplosion);
/*ADD*/			delete m_pExplosion;
/*ADD*/			m_pExplosion = 0;
/*ADD*/		}
/*ADD*/	}