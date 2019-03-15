#include "BulletOpenGLApplication.h"
#include "btBulletDynamicsCommon.h"
class BasicDemo : public BulletOpenGLApplication {
public:
	virtual void InitializePhysics() override;
	virtual void ShutdownPhysics() override;

	void CreateObjects();
};