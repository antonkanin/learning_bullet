/*ADD*/	#include "SoftBodyDemo.h"
/*ADD*/	
/*ADD*/	SoftBodyDemo::SoftBodyDemo()
/*ADD*/		:
/*ADD*/	BulletOpenGLApplication()
/*ADD*/	{
/*ADD*/	}
/*ADD*/	
/*ADD*/	void SoftBodyDemo::InitializePhysics() {
/*ADD*/		// create the collision configuration
/*ADD*/		m_pCollisionConfiguration = new btSoftBodyRigidBodyCollisionConfiguration();
/*ADD*/	
/*ADD*/		// create the dispatcher
/*ADD*/		m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);
/*ADD*/	
/*ADD*/		// create the broadphase
/*ADD*/		m_pBroadphase = new btDbvtBroadphase();
/*ADD*/	
/*ADD*/		// create the constraint solver
/*ADD*/		m_pSolver = new btSequentialImpulseConstraintSolver();
/*ADD*/	
/*ADD*/		// create the softbody world
/*ADD*/		m_pWorld = new btSoftRigidDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pCollisionConfiguration);
/*ADD*/	
/*ADD*/		// typecast the world and store it for future usage
/*ADD*/		m_pSoftBodyWorld = (btSoftRigidDynamicsWorld*)m_pWorld;
/*ADD*/	
/*ADD*/		// initialize the world info for soft bodies
/*ADD*/		m_softBodyWorldInfo.m_dispatcher = m_pDispatcher;
/*ADD*/		m_softBodyWorldInfo.m_broadphase = m_pBroadphase;
/*ADD*/		m_softBodyWorldInfo.m_sparsesdf.Initialize();
/*ADD*/	
/*ADD*/		CreateObjects();
/*ADD*/	}
/*ADD*/	
/*ADD*/	void SoftBodyDemo::ShutdownPhysics() {
/*ADD*/		delete m_pWorld;
/*ADD*/		delete m_pSolver;
/*ADD*/		delete m_pBroadphase;
/*ADD*/		delete m_pDispatcher;
/*ADD*/		delete m_pCollisionConfiguration;
/*ADD*/	}
/*ADD*/	
/*ADD*/	void SoftBodyDemo::CreateObjects() {
/*ADD*/		// create a ground plane
/*ADD*/	
/*ADD*/		CreateGameObject(new btBoxShape(btVector3(1,50,50)), 0, btVector3(0.2f, 0.6f, 0.6f), btVector3(0.0f, 0.0f, 0.0f));
/*ADD*/	
/*ADD*/		// create a soft 'ball' with 128 sides and a radius of 3
/*ADD*/		btSoftBody*  pSoftBody = btSoftBodyHelpers::CreateEllipsoid(m_softBodyWorldInfo,btVector3(0,0,0),btVector3(3,3,3),128);
/*ADD*/	
/*ADD*/		// set the body's position
/*ADD*/		pSoftBody->translate(btVector3(0,15,0));
/*ADD*/	
/*ADD*/		// set the 'volume conservation coefficient'
/*ADD*/		pSoftBody->m_cfg.kVC = 0.5;
/*ADD*/	
/*ADD*/		// set the 'linear stiffness'
/*ADD*/		pSoftBody->m_materials[0]->m_kLST = 0.5;
/*ADD*/	
/*ADD*/		// set the total mass of the soft body
/*ADD*/		pSoftBody->setTotalMass(5);
/*ADD*/	
/*ADD*/		// tell the soft body to initialize and
/*ADD*/		// attempt to maintain the current pose
/*ADD*/		pSoftBody->setPose(true,false);
/*ADD*/	
/*ADD*/		// add the soft body to our world
/*ADD*/		m_pSoftBodyWorld->addSoftBody(pSoftBody);
/*ADD*/	}
/*ADD*/	
/*ADD*/	void SoftBodyDemo::RenderScene() {
/*ADD*/		// call the base rendering code first
/*ADD*/		BulletOpenGLApplication::RenderScene();
/*ADD*/		// check the list of our world's soft bodies
/*ADD*/		for (int i=0; i< m_pSoftBodyWorld->getSoftBodyArray().size(); i++) {
/*ADD*/			// get the body
/*ADD*/			btSoftBody*  pBody = (btSoftBody*)m_pSoftBodyWorld->getSoftBodyArray()[i];
/*ADD*/			// is it possible to render?
/*ADD*/			if (m_pSoftBodyWorld->getDebugDrawer() && !(m_pSoftBodyWorld->getDebugDrawer()->getDebugMode() & (btIDebugDraw::DBG_DrawWireframe))) {
/*ADD*/				// draw it
/*ADD*/				btSoftBodyHelpers::Draw(pBody, m_pSoftBodyWorld->getDebugDrawer(), m_pSoftBodyWorld->getDrawFlags());
/*ADD*/			}
/*ADD*/		}
/*ADD*/	}