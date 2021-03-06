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
	m_Selected = false;
	m_DB = NULL;
}

CBaseStation::~CBaseStation()
{	
	
}

void CBaseStation::SetDB(void *db)
{
	m_DB = db;
}

void CBaseStation::SetFont(nvFastFont *v)
{
	m_NameFont = v;
}

void CBaseStation::CreateSymbol(void *MemoryBlock,long MemoryBlockSize)
{
	TMemoryBlock BlockTGA_0;
	BlockTGA_0.Ptr = MemoryBlock;
	BlockTGA_0.Size = MemoryBlockSize;
	m_TextureTGA_0 = LoadFromMemoryBlockTGA( &BlockTGA_0 );
}

void CBaseStation::CreateTexture(TTexture *Texture, GLuint *TextureID)
{
	glGenTextures(1, TextureID );
	glBindTexture(GL_TEXTURE_2D, *TextureID );
	glTexImage2D(GL_TEXTURE_2D, 0, Texture->Bpp / 8, Texture->Width, Texture->Height, 0, Texture->Type, GL_UNSIGNED_BYTE, Texture->Data );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	FreeTexture( Texture );
}

void CBaseStation::CreateTextures(void) 
{
	//CreateSymbol(icon, icon_size);
	CreateTexture( m_TextureTGA_0,  &m_TextureID_0 );
}


void CBaseStation::Mouse(int x, int y, bool lmb, bool mmb, bool rmb)
{
	double _x = m_LonMap;
	double _y = m_LatMap;
	
	if(IsPointInsideBox(x, y, _x - (m_RectWidth) + m_TranslationX,_y - (m_RectHeight) + m_TranslationY,_x + (m_RectWidth) + m_TranslationX , _y + (m_RectHeight) + m_TranslationY))
	{
		((wxWindow*)m_Broker->GetParentPtr())->SetCursor(wxCURSOR_HAND);
		if(lmb)
			m_Selected = !m_Selected;
	}
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
	
	m_RectWidth = RECT_WIDTH; // m_SmoothScaleFactor;
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

void CBaseStation::RenderSeconds()
{
	glPushMatrix();
	
	//SetColor(SYMBOL_ERROR_COLOR);
	
	
	glTranslatef(m_LonMap,m_LatMap,0.0f);
	//glTranslatef(0.0,th/2,0.0f);
	glColor4f(1.0f,0.0f,0.0f,0.5f);
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = m_RectWidth * 5;
	for(int i = 0; i < 360; i+=30)
	{
		nvDrawCircleArcFilled(&c,i,i);
	}
	
	glPopMatrix();
	
}

void CBaseStation::RenderText(float x, float y, float vx, float vy, const wchar_t *format ...)
{	
	wchar_t buffer[128];
	va_list args;
	va_start(args,format);
	//swprintf_s(buffer,format,args);
	vswprintf ( buffer, 128, format, args );
	va_end(args);
	
	m_NameFont->Print(x,y,GetFontSize()/m_SmoothScaleFactor/DEFAULT_FONT_FACTOR,0,buffer,vx,vy);

}

void CBaseStation::RenderText()
{
		
	RenderText(m_LonMap,m_LatMap,0.5f,3.3f,m_Name);
//	RenderText(GetLonMap(),m_LatMap,0.5f,6.6f,GetName());
//	RenderText(GetLonMap(),GetLatMap(),0.5f,7.7f,GetAgeAsString());
					
//	if(GetBusy())
//		RenderText(GetLonMap(),GetLatMap(),-1.5f,-0.1f,GetCommandCountAsString());

}

void CBaseStation::RenderSelected()
{
	if(!m_Selected)
		return;

	double x,y;

	x = m_LonMap; 
	y = m_LatMap;
		
	glEnable(GL_BLEND);
	glPushMatrix();
	
	glColor4f(1.0f,1.0f,1.0f,0.5f);	
	glTranslatef(x, y ,0.0f);
	//glTranslatef(m_OffsetX, m_OffsetY,0.0f);
	glLineWidth(2);
	
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
		
	//if(m_SelectedOn)
		c.Radius = m_RectWidth/1.5;
	//else
		//c.Radius = RectWidth*4.0;

	nvDrawCircleFilled(&c);
	glLineWidth(1);
	
	glPopMatrix();
	glDisable(GL_BLEND);
}

void CBaseStation::RenderBaseStation()
{
	glPushMatrix();
	if(m_Status == 0)
		glColor4f(0.0,0.0,0.0,0.1);
	if(m_Status == 1)
		glColor4f(1.0,0.0,0.0,0.8);
		//glBindTexture( GL_TEXTURE_2D, m_TextureID_0);
	glTranslatef(m_LonMap,m_LatMap,0.0f);

	/*
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
	*/
	
	glDisable(GL_TEXTURE_2D);

	//SetSymbolColor();
			
	//glTranslatef(m_LonMap,m_LatMap,0.0f);
	
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = m_RectWidth;
	
	nvDrawCircleFilled(&c);
		
	glLineWidth(1);
	//glBegin(GL_LINES);
		//glVertex2f(0.0f,m_RectWidth);
		//glVertex2f(0.0f,-m_RectWidth);
		//glVertex2f(m_RectWidth,0.0);
		//glVertex2f(-m_RectWidth,0.0);
	//glEnd();
	nvDrawCircle(&c);

	glPopMatrix();
	
	
}

void CBaseStation::Render()
{
	//return;
	glPushMatrix();
	
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

	UpdateViewPort();
	SetValues();
	RenderBaseStation();
	RenderSelected();
	RenderSeconds();
	RenderText();

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

void CBaseStation::SetStatus(int v)
{
	m_Status = v;
}
