#include <wx/wx.h>
#include "basestation.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "navidrawer.h"
#include "options.h"
#include "render.h"


CBaseStation::CBaseStation(CNaviBroker *broker)
{
	m_Broker = broker;
	m_Scale = 1;
	m_SmoothScaleFactor = 1;
	m_RectWidth = 0;
	m_RectHeight = 0;
	m_TranslationX = 0;
	m_TranslationY = 0;
	m_DB = NULL;
}

CBaseStation::~CBaseStation()
{	
	
}

void CBaseStation::SetDB(void *db)
{
	m_DB = db;
}

void CBaseStation::SetSmoothScaleFactor(double v) 
{
	int factor = GetScaleFactor();
	if( m_Scale > factor )
		m_SmoothScaleFactor = m_Scale;
	else
		m_SmoothScaleFactor = factor;
}

void CBaseStation::SetValues()
{
	if(m_Broker == NULL)
		return;
	
	m_Scale  = m_Broker->GetMapScale();
	SetSmoothScaleFactor( m_Scale );
	
	m_RectWidth = RECT_WIDTH;// m_SmoothScaleFactor;
	m_RectHeight = RECT_HEIGHT; // m_SmoothScaleFactor;
	m_TranslationX = 0.0; //(RECT_WIDTH /2)/SmoothScaleFactor; 
	//m_TranslationY = -(RECT_HEIGHT /2)/m_SmoothScaleFactor; 
	m_Broker->GetVisibleMap(m_VisibleMap);
	
}

void CBaseStation::UpdateViewPort()
{
	

	//glViewport(0, 0, (GLint)  m_Broker->GetViewportWidth(m_Broker->GetParentPtr()), (GLint) m_Broker->GetViewportHeight(m_Broker->GetParentPtr()));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
	wxWindow *a = (wxWindow*)m_Broker->GetParentPtr();
	int height = a->GetSize().GetHeight();
	int width = a->GetSize().GetWidth();

	glOrtho(0, width, height , 0, -1.0, 1.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
	//glTranslatef(m_MoveX*m_XScale ,m_MoveY*m_YScale,0.0);
	//glScalef(m_Scale,1.0,1.0);
	
	//glTranslatef(-m_Buffer->GetLength(),-GetLastAccuracy(),0.0);
	//glTranslatef(m_ScreenWidth-10,m_ScreenHeight/2,0.0);
}




void CBaseStation::RenderBaseStation()
{
	glPushMatrix();
	glColor4f(0.0,0.0,0.0,0.5);
		//glBindTexture( GL_TEXTURE_2D, m_TextureID_0);
	glTranslatef(m_LonMap,m_LatMap,0.0f);
		
	glBegin(GL_QUADS);
		//glTexCoord2f(1.0f,1.0f); 
		glVertex2f(  m_RectWidth + m_TranslationX,  -m_RectHeight + m_TranslationY);
		//glTexCoord2f(1.0f,0.0f); 
		glVertex2f(  m_RectWidth + m_TranslationX,   m_RectHeight + m_TranslationY);
		//glTexCoord2f(0.0f,0.0f); 
		glVertex2f( -m_RectWidth + m_TranslationX,   m_RectHeight + m_TranslationY);
		//glTexCoord2f(0.0f,1.0f); 
		glVertex2f( -m_RectWidth + m_TranslationX,  -m_RectHeight + m_TranslationY);
	glEnd();
	
	
	glDisable(GL_TEXTURE_2D);

	//SetSymbolColor();
			
	//glTranslatef(m_LonMap,m_LatMap,0.0f);
	
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = m_RectWidth;
	
	nvDrawCircleFilled(&c);
	
	
	glLineWidth(1);
	glBegin(GL_LINES);
		glVertex2f(0.0f,m_RectWidth);
		glVertex2f(0.0f,-m_RectWidth);
		glVertex2f(m_RectWidth,0.0);
		glVertex2f(-m_RectWidth,0.0);
	glEnd();
	nvDrawCircle(&c);

	glPopMatrix();
	
	
}

void CBaseStation::Render()
{
	glPushMatrix();
	
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

	UpdateViewPort();
	SetValues();
	RenderBaseStation();
		
	glDisable(GL_BLEND);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);

	glPopMatrix();
}


//SET

void CBaseStation::SetLon(double v)
{
	m_Lon = v;
}

void CBaseStation::SetLat(double v)
{
	m_Lat = v;
}

void CBaseStation::SetLonMap(double v)
{
	m_LonMap = v;
}

void CBaseStation::SetLatMap(double v)
{
	m_LatMap = v;
}

void CBaseStation::SetName(wxString v)
{
	m_Name = v;
}

//void CBaseStation::SetExists(bool v)
//{
	//m_Exists = v;
//}
//GET
