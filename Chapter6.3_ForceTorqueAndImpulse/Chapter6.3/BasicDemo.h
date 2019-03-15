#include "BulletOpenGLApplication.h"
#include "btBulletDynamicsCommon.h"

/*ADD*/ #define EXPLOSION_STRENGTH 50.0f

class BasicDemo : public BulletOpenGLApplication {
public:
/*ADD*/ 	BasicDemo();

	virtual void InitializePhysics() override;
	virtual void ShutdownPhysics() override;

	void CreateObjects();

/*ADD*/	virtual void Keyboard(unsigned char key, int x, int y) override;
/*ADD*/	virtual void KeyboardUp(unsigned char key, int x, int y) override;
/*ADD*/	virtual void UpdateScene(float dt);

	virtual void CollisionEvent(btRigidBody* pBody0, btRigidBody* pBody1) override;

protected:
	// our box to lift
	GameObject* m_pBox;

	// a simple trigger volume
	btCollisionObject* m_pTrigger;

/*ADD*/		// keeps track of whether we're holding down the 'g' key
/*ADD*/		bool m_bApplyForce;

/*ADD*/		// explosion variables
/*ADD*/		btCollisionObject* m_pExplosion;
/*ADD*/		bool m_bCanExplode;
};