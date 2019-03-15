#ifndef _DEBUG_DRAWER_H
#define _DEBUG_DRAWER_H

#include "LinearMath/btIDebugDraw.h"

class DebugDrawer : public btIDebugDraw {
public:
	// debug mode functions
	virtual void setDebugMode(int debugMode) override { m_debugMode = debugMode; }
	virtual int getDebugMode() const override { return m_debugMode; }

	// drawing functions
	virtual void  drawContactPoint(const btVector3 &pointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color) override;
	virtual void  drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color) override;
/*ADD*/		virtual void  drawTriangle(const btVector3& a,const btVector3& b,const btVector3& c,const btVector3& color,btScalar alpha) override;
	// unused
	virtual void  reportErrorWarning(const char* warningString) override {}
	virtual void  draw3dText(const btVector3 &location,const char* textString) override {}

	void ToggleDebugFlag(int flag);

protected:
	int m_debugMode;
};
#endif
