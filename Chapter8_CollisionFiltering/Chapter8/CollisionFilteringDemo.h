/*ADD*/	#include "BulletOpenGLApplication.h"
/*ADD*/	
/*ADD*/	#include "btBulletDynamicsCommon.h"
/*ADD*/	
/*ADD*/	class CollisionFilteringDemo : public BulletOpenGLApplication {
/*ADD*/	public:
/*ADD*/		CollisionFilteringDemo();
/*ADD*/	
/*ADD*/		virtual void InitializePhysics() override;
/*ADD*/		virtual void ShutdownPhysics() override;
/*ADD*/		void CreateObjects();
/*ADD*/	};