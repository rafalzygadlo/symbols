#include <wx/wx.h>
#include "symbol.h"
#include "conf.h"
#include "tools.h"
#include "db.h"


CSymbol::CSymbol(void *db, CNaviBroker *broker)
{
	m_Broker = broker;
	m_DB = db;
	m_TextureId = 0;
	m_Scale = 1;
	m_Factor = DEFAULT_FACTOR;
	m_SmoothScaleFactor = 1;
	m_RectWidth = 0;
	m_RectHeight = 0;
	m_TranslationX = 0;
	m_TranslationY = 0;
	
	m_Ticker = new CTicker(this,TICK_SYMBOL);
	m_Ticker->Start(100);
	
}

CSymbol::~CSymbol()
{
	m_Ticker->Stop();
	delete m_Ticker;
}

void CSymbol::SetSmoothScaleFactor(double v) 
{
	if( m_Scale > m_Factor )
		m_SmoothScaleFactor = m_Scale;
	else
		m_SmoothScaleFactor = m_Factor;
}


void CSymbol::SetValues()
{
	m_Scale  = m_Broker->GetMapScale();
	SetSmoothScaleFactor( m_Scale );
	
	m_RectWidth = RECT_WIDTH / m_SmoothScaleFactor;
	m_RectHeight = RECT_HEIGHT / m_SmoothScaleFactor;
	m_TranslationX = 0.0; //(RECT_WIDTH /2)/SmoothScaleFactor; 
	m_TranslationY = -(RECT_HEIGHT /2)/m_SmoothScaleFactor; 
	
	m_Broker->GetVisibleMap(m_VisibleMap);
	
}


void CSymbol::Render()
{
	SetValues();
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	//if(m_On)
		//glColor4f(1.0f,1.0f,1.0f,0.6f);
	//else
		//glColor4f(1.0f,0.0f,0.0f,0.6f);
	
	glBindTexture( GL_TEXTURE_2D, m_TextureId);
	glPushMatrix();
	glTranslatef(m_Lon,m_Lat,0.0f);
		
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,1.0f); glVertex2f(  m_RectWidth/2 + m_TranslationX,  -m_RectHeight/2 + m_TranslationY);
		glTexCoord2f(1.0f,0.0f); glVertex2f(  m_RectWidth/2 + m_TranslationX,   m_RectHeight/2 + m_TranslationY);
		glTexCoord2f(0.0f,0.0f); glVertex2f( -m_RectWidth/2 + m_TranslationX,   m_RectHeight/2 + m_TranslationY);
		glTexCoord2f(0.0f,1.0f); glVertex2f( -m_RectWidth/2 + m_TranslationX,  -m_RectHeight/2 + m_TranslationY);
	glEnd();
	
	glPopMatrix();
			
	glDisable(GL_TEXTURE_2D);			
	glDisable(GL_TEXTURE_2D);

}

//SET
void CSymbol::SetId(int v)
{
	m_Id = v;
}

void CSymbol::SetLon(double v)
{
	m_Lon = v;
}

void CSymbol::SetLat(double v)
{
	m_Lat = v;
}

//GET
int CSymbol::GetId()
{
	return m_Id;
}

double CSymbol::GetLon()
{
	return m_Lon;
}

double CSymbol::GetLat()
{
	return m_Lat;
}
