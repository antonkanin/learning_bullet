/*ADD*/	#include "BulletOpenGLApplication.h"
/*ADD*/	#include "btBulletDynamicsCommon.h"
/*ADD*/	class BasicDemo : public BulletOpenGLApplication {
/*ADD*/	public:
/*ADD*/		virtual void InitializePhysics() override;
/*ADD*/		virtual void ShutdownPhysics() override;
/*ADD*/	};