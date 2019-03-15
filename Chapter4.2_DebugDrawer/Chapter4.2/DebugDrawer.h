/*ADD*/	#ifndef _DEBUG_DRAWER_H
/*ADD*/	#define _DEBUG_DRAWER_H
/*ADD*/	
/*ADD*/	#include "LinearMath/btIDebugDraw.h"
/*ADD*/	
/*ADD*/	class DebugDrawer : public btIDebugDraw {
/*ADD*/	public:
/*ADD*/		// debug mode functions
/*ADD*/		virtual void setDebugMode(int debugMode) override { m_debugMode = debugMode; }
/*ADD*/		virtual int getDebugMode() const override { return m_debugMode; }
/*ADD*/	
/*ADD*/		// drawing functions
/*ADD*/		virtual void  drawContactPoint(const btVector3 &pointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color) override;
/*ADD*/		virtual void  drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color) override;
/*ADD*/	
/*ADD*/		// unused
/*ADD*/		virtual void  reportErrorWarning(const char* warningString) override {}
/*ADD*/		virtual void  draw3dText(const btVector3 &location,const char* textString) override {}
/*ADD*/	
/*ADD*/		void ToggleDebugFlag(int flag);
/*ADD*/	
/*ADD*/	protected:
/*ADD*/		int m_debugMode;
/*ADD*/	};
/*ADD*/	#endif
