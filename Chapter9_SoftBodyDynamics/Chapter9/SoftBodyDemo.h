// NOTE
// Three extra steps were taken to configure this project:
//   1) The BulletSoftBody project was included
//	 2) The above project was set as a dependency
//   3) BulletSoftBody_vs2010_debug.lib was added to the list of required .lib files (Linker->Input->Additional Dependencies).
// All of the above are required for the simulation of soft bodies.

/*ADD*/	#include "BulletOpenGLApplication.h"
/*ADD*/	
/*ADD*/	// includes required for soft body simulation
/*ADD*/	#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"
/*ADD*/	#include "BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h"
/*ADD*/	#include "BulletSoftBody/btSoftBodyHelpers.h"
/*ADD*/	
/*ADD*/	class SoftBodyDemo : public BulletOpenGLApplication {
/*ADD*/	public:
/*ADD*/		SoftBodyDemo();
/*ADD*/	
/*ADD*/		virtual void InitializePhysics() override;
/*ADD*/		virtual void ShutdownPhysics() override;
/*ADD*/		virtual void RenderScene() override;
/*ADD*/		void CreateObjects();
/*ADD*/	
/*ADD*/	protected:
/*ADD*/		// a pointer to our world, typecast into its soft body type
/*ADD*/		btSoftRigidDynamicsWorld*  m_pSoftBodyWorld;
/*ADD*/		
/*ADD*/		// the soft body world info. Needed for proper contact generation
/*ADD*/		btSoftBodyWorldInfo  m_softBodyWorldInfo;
/*ADD*/	};
