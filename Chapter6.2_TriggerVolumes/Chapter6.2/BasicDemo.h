#include "BulletOpenGLApplication.h"
#include "btBulletDynamicsCommon.h"
class BasicDemo : public BulletOpenGLApplication {
public:
	virtual void InitializePhysics() override;
	virtual void ShutdownPhysics() override;

	void CreateObjects();

/*ADD*/		virtual void CollisionEvent(btRigidBody* pBody0, btRigidBody* pBody1) override;
/*ADD*/	
/*ADD*/	protected:
/*ADD*/		// our box to lift
/*ADD*/		GameObject* m_pBox;
/*ADD*/	
/*ADD*/		// a simple trigger volume
/*ADD*/		btCollisionObject* m_pTrigger;
};