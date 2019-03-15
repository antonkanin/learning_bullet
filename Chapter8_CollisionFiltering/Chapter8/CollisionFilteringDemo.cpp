/*ADD*/	#include "CollisionFilteringDemo.h"
/*ADD*/	
/*ADD*/	CollisionFilteringDemo::CollisionFilteringDemo()
/*ADD*/		:
/*ADD*/	BulletOpenGLApplication()
/*ADD*/	{
/*ADD*/	}
/*ADD*/	
/*ADD*/	void CollisionFilteringDemo::InitializePhysics() {
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
/*ADD*/		CreateObjects();
/*ADD*/	}
/*ADD*/	
/*ADD*/	void CollisionFilteringDemo::ShutdownPhysics() {
/*ADD*/		delete m_pWorld;
/*ADD*/		delete m_pSolver;
/*ADD*/		delete m_pBroadphase;
/*ADD*/		delete m_pDispatcher;
/*ADD*/		delete m_pCollisionConfiguration;
/*ADD*/	}
/*ADD*/	
/*ADD*/	void CollisionFilteringDemo::CreateObjects() {
/*ADD*/		// create a ground plane
/*ADD*/		CreateGameObject(new btBoxShape(btVector3(1,50,50)), 
/*ADD*/			0, btVector3(0.2f, 0.6f, 0.6f), btVector3(0.0f, 0.0f, 0.0f),
/*ADD*/			COLGROUP_STATIC,
/*ADD*/			/*the ground plane can collide with boxes and spheres*/
/*ADD*/			COLGROUP_BOX | COLGROUP_SPHERE);
/*ADD*/	
/*ADD*/		// create 25 boxes and spheres in a 5x5 stack formation 
/*ADD*/		float yPos = 0;
/*ADD*/		for (int i = 0; i < 25; i++) {
/*ADD*/			// calculate the x and y for the object
/*ADD*/			float xPos = -5 + 2*(float)(i % 5);
/*ADD*/			if (i % 5 == 0) yPos += 2;
/*ADD*/			// create a btVector3 for the position
/*ADD*/			btVector3 position(xPos, yPos, 4);
/*ADD*/	
/*ADD*/			// create a box
/*ADD*/			CreateGameObject(new btBoxShape(btVector3(1,1,1)),
/*ADD*/				1.0f,
/*ADD*/				/*alternate colors*/
/*ADD*/				btVector3(1.0f, 0.2f, i%2),
/*ADD*/				position,
/*ADD*/				COLGROUP_BOX,
/*ADD*/				/*boxes can collide with the ground plane and other boxes*/
/*ADD*/				COLGROUP_BOX | COLGROUP_STATIC);
/*ADD*/	
/*ADD*/			// create a sphere in the same location
/*ADD*/			GameObject* pSphere = CreateGameObject(new btSphereShape(1.2),
/*ADD*/				1.0f,
/*ADD*/				/*alternate colors*/
/*ADD*/				btVector3(i%2, 1.0f, 0.2f),
/*ADD*/				position,
/*ADD*/				COLGROUP_SPHERE,
/*ADD*/				/*spheres can collide with the ground plane and other spheres*/
/*ADD*/				COLGROUP_SPHERE | COLGROUP_STATIC);
/*ADD*/			// set the sphere to only move in the XY plane
/*ADD*/			pSphere->GetRigidBody()->setLinearFactor(btVector3(1, 1, 0));
/*ADD*/		}
/*ADD*/	}
/*ADD*/	