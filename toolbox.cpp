#include <wx/wx.h>
#include "toolbox.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "navidrawer.h"
#include "options.h"
#include "render.h"


CToolBox::CToolBox(CNaviBroker *broker)
{
	m_Broker = broker;
	m_Scale = 1;
	m_SmoothScaleFactor = 1;
	m_RectWidth = 0;
	m_RectHeight = 0;
	m_TranslationX = 0;
	m_TranslationY = 0;
	m_Selected = false;
	m_Margin = 30;
}

CToolBox::~CToolBox()
{	
	
}

void CToolBox::SetDB(void *db)
{

}

void CToolBox::SetFont(nvFastFont *v)
{
	m_NameFont = v;
}

void CToolBox::CreateSymbol(void *MemoryBlock,long MemoryBlockSize)
{
	TMemoryBlock BlockTGA_0;
	BlockTGA_0.Ptr = MemoryBlock;
	BlockTGA_0.Size = MemoryBlockSize;
	m_TextureTGA_0 = LoadFromMemoryBlockTGA( &BlockTGA_0 );
}

void CToolBox::CreateTexture(TTexture *Texture, GLuint *TextureID)
{
	glGenTextures(1, TextureID );
	glBindTexture(GL_TEXTURE_2D, *TextureID );
	glTexImage2D(GL_TEXTURE_2D, 0, Texture->Bpp / 8, Texture->Width, Texture->Height, 0, Texture->Type, GL_UNSIGNED_BYTE, Texture->Data );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	FreeTexture( Texture );
}

void CToolBox::CreateTextures(void) 
{
	//CreateSymbol(icon, icon_size);
	CreateTexture( m_TextureTGA_0,  &m_TextureID_0 );
}


void CToolBox::Mouse(int x, int y, bool lmb, bool mmb, bool rmb)
{
	double _x = m_LonMap;
	double _y = m_LatMap;
	
	if(IsPointInsideBox(x, y, _x - (m_RectWidth) + m_TranslationX,_y - (m_RectHeight) + m_TranslationY,_x + (m_RectWidth) + m_TranslationX , _y + (m_RectHeight) + m_TranslationY))
	{
		((wxWindow*)m_Broker->GetParentPtr())->SetCursor(wxCURSOR_HAND);
		m_Hoover = true;
		if(lmb)
		{
			//fprintf(stderr,"Click\n");
			m_Selected = !m_Selected;
			Click();
			return;
		}
	
	}else{
		m_Hoover = false;
	
	}

	
}

void CToolBox::Click()
{
	wxMessageBox(wxString::Format(_("%d"),GetId()));
	//switch(GetId())
	//{
	
	
	//}
}

void CToolBox::SetSmoothScaleFactor(double v) 
{
	int factor = GetScaleFactor();
	if( m_Scale > factor )
		m_SmoothScaleFactor = m_Scale;
	else
		m_SmoothScaleFactor = factor;
}

void CToolBox::SetValues()
{
	if(m_Broker == NULL)
		return;
	
	m_Scale  = m_Broker->GetMapScale();
	SetSmoothScaleFactor( m_Scale );
	
	m_LonMap = m_ScreenWidth - m_RectWidth;
	m_LatMap = (m_RectHeight*GetId()*3) + m_RectHeight;


	m_RectWidth = RECT_WIDTH; // m_SmoothScaleFactor;
	m_RectHeight = RECT_HEIGHT; // m_SmoothScaleFactor;
	m_TranslationX = 0.0; //(RECT_WIDTH /2)/SmoothScaleFactor; 
	//m_TranslationY = -(RECT_HEIGHT /2)/m_SmoothScaleFactor; 
	m_Broker->GetVisibleMap(m_VisibleMap);
	
}

void CToolBox::UpdateViewPort()
{
	
	//glViewport(0, 0, (GLint)  m_Broker->GetViewportWidth(m_Broker->GetParentPtr()), (GLint) m_Broker->GetViewportHeight(m_Broker->GetParentPtr()));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
	wxWindow *a = (wxWindow*)m_Broker->GetParentPtr();
	m_ScreenHeight = a->GetSize().GetHeight();
	m_ScreenWidth = a->GetSize().GetWidth();

	glOrtho(0, m_ScreenWidth, m_ScreenHeight , 0, -1.0, 1.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
	//glTranslatef(m_MoveX*m_XScale ,m_MoveY*m_YScale,0.0);
	//glScalef(m_Scale,1.0,1.0);
	
	//glTranslatef(-m_Buffer->GetLength(),-GetLastAccuracy(),0.0);
	//glTranslatef(m_ScreenWidth-10,m_ScreenHeight/2,0.0);
}

void CToolBox::RenderSeconds()
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

void CToolBox::RenderText(float x, float y, float vx, float vy, const wchar_t *format ...)
{	
	wchar_t buffer[128];
	va_list args;
	va_start(args,format);
	//swprintf_s(buffer,format,args);
	vswprintf ( buffer, 128, format, args );
	va_end(args);
	
	m_NameFont->Print(x,y,GetFontSize()/m_SmoothScaleFactor/DEFAULT_FONT_FACTOR,0,buffer,vx,vy);

}

void CToolBox::RenderText()
{
		
	RenderText(m_LonMap,m_LatMap,0.5f,3.3f,m_Name);
//	RenderText(GetLonMap(),m_LatMap,0.5f,6.6f,GetName());
//	RenderText(GetLonMap(),GetLatMap(),0.5f,7.7f,GetAgeAsString());
					
//	if(GetBusy())
//		RenderText(GetLonMap(),GetLatMap(),-1.5f,-0.1f,GetCommandCountAsString());

}

void CToolBox::RenderHoover()
{
	if(!m_Hoover)
		return;

	glColor4f(0.0,1.0,0.0,0.8);
	
}

void CToolBox::RenderSelected()
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

void CToolBox::RenderBaseStation()
{
	glPushMatrix();
	if(m_Hoover)
		glColor4f(1.0,0.0,0.0,0.5);
	else
		glColor4f(0.0,0.0,0.0,0.2);
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
	//Circle
#if 0
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
#endif
	glPopMatrix();
	
	
}

void CToolBox::Render()
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
	RenderHoover();
	RenderSeconds();
	RenderText();

	glDisable(GL_BLEND);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);

	glPopMatrix();
}


//SET

void CToolBox::SetLon(double v)
{
	m_Lon = v;
}

void CToolBox::SetLat(double v)
{
	m_Lat = v;
}

void CToolBox::SetLonMap(double v)
{
	m_LonMap = v;
}

void CToolBox::SetLatMap(double v)
{
	m_LatMap = v;
}

void CToolBox::SetName(wxString v)
{
	m_Name = v;
}

void CToolBox::SetStatus(int v)
{
	m_Status = v;
}
