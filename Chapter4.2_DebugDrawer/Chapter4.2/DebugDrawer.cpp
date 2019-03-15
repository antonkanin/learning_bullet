/*ADD*/	#include "DebugDrawer.h"
/*ADD*/	#include "BulletOpenGLApplication.h"
/*ADD*/	
/*ADD*/	void DebugDrawer::drawLine(const btVector3 &from,const btVector3 &to, const btVector3 &color)
/*ADD*/	{
/*ADD*/		// draws a simple line of pixels between points.
/*ADD*/	
/*ADD*/		// use the GL_LINES primitive to draw lines
/*ADD*/		glBegin(GL_LINES);
/*ADD*/		glColor3f(color.getX(), color.getY(), color.getZ());
/*ADD*/		glVertex3f(from.getX(), from.getY(), from.getZ());
/*ADD*/		glVertex3f(to.getX(), to.getY(), to.getZ());
/*ADD*/		glEnd();
/*ADD*/	}
/*ADD*/	
/*ADD*/	void DebugDrawer::drawContactPoint(const btVector3 &pointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color)
/*ADD*/	{
/*ADD*/		// draws a line between two contact points
/*ADD*/		btVector3 const startPoint = pointOnB;
/*ADD*/		btVector3 const endPoint = pointOnB + normalOnB * distance;
/*ADD*/		drawLine( startPoint, endPoint, color );
/*ADD*/	}
/*ADD*/	
/*ADD*/	void DebugDrawer::ToggleDebugFlag(int flag) {
/*ADD*/		// checks if a flag is set and enables/
/*ADD*/		// disables it
/*ADD*/		if (m_debugMode & flag)
/*ADD*/			// flag is enabled, so disable it
/*ADD*/			m_debugMode = m_debugMode & (~flag);
/*ADD*/		else
/*ADD*/			// flag is disabled, so enable it
/*ADD*/			m_debugMode |= flag;
/*ADD*/	}