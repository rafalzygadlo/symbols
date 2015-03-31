#include <wx/wx.h>
#include "grid.h"
#include "conf.h"
#include "options.h"
#include "tools.h"
#include "NaviDrawer.h"
#include "render.h"


BEGIN_EVENT_TABLE(CGrid,wxGLCanvas)
	EVT_PAINT(OnPaint)
	EVT_SIZE(OnSize)
	EVT_MOUSE_EVENTS(OnMouse)
	EVT_LEAVE_WINDOW(OnMouseLeave)
	EVT_KEY_DOWN(OnKeyDown)
END_EVENT_TABLE()

//int args [] = { WX_GL_RGBA, WX_GL_MIN_RED, 1, WX_GL_MIN_GREEN, 1,WX_GL_MIN_BLUE, 1, WX_GL_DEPTH_SIZE, 1};
CGrid::CGrid(wxWindow *parent)
:wxGLCanvas( parent, wxID_ANY,0, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE|wxWANTS_CHARS)
 //:wxGLCanvas( parent, (wxGLCanvas*) NULL,wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE ,wxEmptyString , args )
{
	//m_Station = station;
	GLContext = new wxGLContext(this);
	
#ifdef DC
	SetDoubleBuffered(true);
#endif
	m_Font = new FTPixmapFont(GetFontPath().mb_str(wxConvUTF8).data());
	m_Font->FaceSize(14);
		
	m_Selected = false;
	m_MoveX = 0;
	m_MoveY = 0;
	m_Scale = 5;
	m_CenterX = 0;
	m_CenterY = 0;
	//m_Buffer = NULL;
	m_OldMoveX = 0;
	m_OldMoveY = 0;
	m_ScaleFactor = 0.5;
	m_GridWidth = DEFAULT_GRID_WIDTH;
	m_GridHeight = DEFAULT_GRID_HEIGHT;
	m_Camera = 0;
	m_GridStep = 50;
	m_X = 0;
	m_Y = 0;

}

CGrid::~CGrid()
{
	delete m_Font;
	delete GLContext;
}

//void CGrid::SetPointsBuffer(CBuffer *ptr)
//{
	//m_Buffer = ptr;
//}

void CGrid::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	SetCurrent(*GLContext);
	
	Render();
	//event.Skip();
}

void CGrid::OnSize(wxSizeEvent &event)
{
	int w, h;
	GetClientSize(&w, &h);
	m_ScreenWidth = w;
    m_ScreenHeight = h;
	SetCurrent(*GLContext);
	Refresh();
	//event.Skip();
}

void CGrid::OnMouseLeave(wxMouseEvent &event)
{
	Refresh();
	event.Skip();
}

void CGrid::OnMouse(wxMouseEvent &event) 
{
	bool refresh = false;
	m_MouseX = event.GetX();
	m_MouseY = event.GetY();
			
	if (event.Dragging()) 
	{
        float vx = m_OldX - m_MouseX;
        float vy = m_OldY - m_MouseY;
					
		m_MoveX -= vx;
        m_MoveY += vy;
		
		//m_OldMoveX = m_MoveX;
		//m_OldMoveY = m_MoveY;
		refresh = true;
				        
    }
    else if (event.GetWheelRotation() > 0) {
		
		SetScaleUp();
		m_Scale++;

		if(m_Scale <= MIN_SCALE)
			m_Scale = MIN_SCALE;

		if(m_Scale > MAX_SCALE)
			m_Scale = MAX_SCALE;
		
		refresh = true;
		      
    }
    else if (event.GetWheelRotation() < 0) {
		
		SetScaleDown();
		m_Scale--;
		
		if(m_Scale <= MIN_SCALE)
			m_Scale = MIN_SCALE;
	
		if(m_Scale > MAX_SCALE)
			m_Scale = MAX_SCALE;
		
		refresh = true;
    }
	
	m_OldX = m_MouseX;
    m_OldY = m_MouseY;

	m_OldMoveX = m_MoveX;
	m_OldMoveY = m_MoveY;

	if(refresh)
		Refresh();
	
	event.Skip();
}

void CGrid::SetScaleUp()
{
	m_MoveX += (m_CenterX + m_OldMoveX - m_MouseX)/m_Scale;
	m_MoveY -= (m_CenterY - m_OldMoveY - m_MouseY)/m_Scale;
}

void CGrid::SetScaleDown()
{
	m_MoveX -= (m_CenterX + m_OldMoveX - m_MouseX)/m_Scale;
	m_MoveY += (m_CenterY - m_OldMoveY - m_MouseY)/m_Scale;
}

void CGrid::OnKeyDown(wxKeyEvent &event)
{
	switch( event.GetKeyCode() ) 
	{
		case WXK_LEFT:	m_MoveX-=20;	break;
		case WXK_RIGHT:	m_MoveX+=20;	break;
		case WXK_UP:	m_MoveY+=20;	break;
		case WXK_DOWN:	m_MoveY-=20;	break;
		case 61:		SetScaleUp();	m_Scale++;		break;
		case 45:		SetScaleDown(); m_Scale--;		break;
	}
		
	m_OldMoveX = m_MoveX;
	m_OldMoveY = m_MoveY;

	if(m_Scale <= MIN_SCALE)
		m_Scale = MIN_SCALE;
	
	if(m_Scale > MAX_SCALE)
		m_Scale = MAX_SCALE;

	Refresh(false);
}


void CGrid::UpdateViewPort()
{
    glViewport(0, 0, (GLint) m_ScreenWidth, (GLint) m_ScreenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
		
	//glOrtho(-m_ScreenWidth/m_Scale, m_ScreenWidth/m_Scale, -m_ScreenHeight/m_Scale, m_ScreenHeight/m_Scale, -100.0, 100.0f);

	
	//glOrtho(0, m_Buffer->GetMax()/10, m_Buffer->GetMax()/10, 0, -1.0, 1.0f);
	glOrtho(-m_ScreenWidth/2, m_ScreenWidth/2, -m_ScreenHeight/2, m_ScreenHeight/2, -1.0, 1.0f);
				    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(m_ScreenWidth/2,m_ScreenHeight/2,0.0f);
	glTranslatef(m_MoveX,m_MoveY,0.0f);
	//gluLookAt( 0, 0, 2, m_MoveX, m_MoveY, 0, 0, 0, 10);
	//glRotatef(m_MoveX, 1.0f, 0.0f, 0.0f);
    //glRotatef(m_MoveY, 0.0f, 1.0f, 0.0f);
	//glRotatef(m_MoveY, 0.0f, 0.0f, 1.0f);
	//glScalef(m_Scale,m_Scale,m_Scale);
	
	//glScalef(m_Scale,m_Scale,m_Scale);
	
	glScalef(m_Scale,m_Scale,1.0f);
	
			
}

void CGrid::Update3DViewPort()
{
    glViewport(0, 0, (GLint) m_ScreenWidth, (GLint) m_ScreenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
	gluPerspective(80.0f,(GLfloat)m_ScreenWidth/(GLfloat)m_ScreenHeight, -1.0f,1.0f) ;
	glTranslatef(1,10,-20);
			    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(0.0,0.0,0.0f);
	
	//glRotatef(m_MoveY, 0.0f, 0.0f, 1.0f);
	//glTranslatef(0.0,0.0,0.0f);
	gluLookAt( m_Scale, m_Scale, m_Scale, 0, 0, 0, 0, 0, 1);
	
	glTranslatef(0.0,0.0,0.0f);
	glRotatef(m_Y, 0.0f, 0.0f, 1.0f);
	//glRotatef(m_Y, 0.0f, 1.0f, 0.0f);
	//glScalef(m_Scale,m_Scale,m_Scale);
	
	//glScalef(m_Scale,m_Scale,m_Scale);
	//glTranslated(m_X,m_Y,0.0f);
	//glScalef(m_Scale,m_Scale,1.0f);
	
			
}

void CGrid::PrepareBuffer()
{
	//nvPoint2d pt;
	for(int i = 0; i < 10; i++)
	{
//		pt.x =
	//	pt.y = 
		//m_Gri
	}
}

void CGrid::RenderText( float x, float y, const char *text )
{		
	glRasterPos2f(x,y);
	m_Font->Render(text);
}

void CGrid::RenderGrid()
{
	glEnable(GL_BLEND);
	glColor4f(0.6f,0.6f,0.6f,0.5f);
	glBegin(GL_LINES);
	for(int i = 0 ; i <= m_GridHeight; i+=m_GridStep)	{		glVertex3i(i,-m_ScreenHeight ,0.0);		glVertex3i(i, m_ScreenHeight,0.0);	}
	for(int i = 0 ; i <= m_GridHeight; i+=m_GridStep)	{		glVertex3i(-i,-m_ScreenHeight,0.0);		glVertex3i(-i, m_ScreenHeight,0.0);	}
	for(int i = 0 ; i <= m_GridWidth; i+=m_GridStep)	{		glVertex3i(-m_ScreenWidth,i,0.0);		glVertex3i( m_ScreenWidth,i,0.0);	}
	for(int i = 0 ; i <= m_GridWidth; i+=m_GridStep)	{		glVertex3i(-m_ScreenWidth,-i,0.0);		glVertex3i( m_ScreenWidth,-i,0.0);	}
	glEnd();
	glDisable(GL_BLEND);
			
}

void CGrid::RenderGridText()
{
	char txt[16];
	glColor4ub(GetFGColor().Red() ,GetFGColor().Green(),GetFGColor().Blue(),GetFGColor().Alpha());
	
	//right
	float a = (m_ScreenWidth - 100)/2/m_Scale - m_MoveX/m_Scale;
	for(int i = 0 ; i <= m_GridHeight; i+=m_GridStep)	{	sprintf(txt,"%d mm",abs(i)); RenderText(a ,i, txt);	}
	for(int i = 0 ; i <= m_GridHeight; i+=m_GridStep)	{	sprintf(txt,"%d mm",abs(i)); RenderText(a ,-i, txt);}
	
	//left	
	//a = (-m_ScreenWidth + 5)/2/m_Scale - m_MoveX/m_Scale;
	//for(int i = -m_GridHeight ; i <= m_GridHeight; i+=m_GridStep)
	//{
		//sprintf(txt,"%d mm",abs(i));
		//RenderText(a ,i, txt);
	//}
	
	//bottom
	a = (-m_ScreenHeight + 5)/2/m_Scale - m_MoveY/m_Scale;
	for(int i = 0 ; i <= m_GridWidth; i+=m_GridStep * 2)	{	sprintf(txt,"%d mm",abs(i)); RenderText(i ,a, txt);		}
	for(int i = 0 ; i <= m_GridWidth; i+=m_GridStep * 2)	{	sprintf(txt,"%d mm",abs(i)); RenderText(-i ,a, txt);	}
	
	//top
	//a = (m_ScreenHeight - 25)/2/m_Scale - m_MoveY/m_Scale;
	//for(int i = -m_GridWidth ; i <= m_GridWidth; i+=m_GridStep*4)
	//{
		//sprintf(txt,"%d mm",abs(i));
		//RenderText(i ,a, txt);
	//}

	//glPopMatrix();

}

void CGrid::RenderAccuracyCircle()
{
	glLineWidth(2);
	glColor3f(1.0f,0.0f,0.0f);
	nvCircle c;
	c.Center.x = 0;
	c.Center.y = 0;
	//c.Radius = m_Station->GetAccuracyMax();
	nvDrawCircle(&c);
	glLineWidth(1);
}

void CGrid::Render2Circle()
{
	glColor3f(1.0f,1.0f,0.0f);
	nvCircle c;
	c.Center.x = 0;
	c.Center.y = 0;
	//c.Radius = m_Station->GetAccuracyMax()/2; //mm 
	nvDrawCircle(&c);
}

void CGrid::Render2CircleDegrees()
{
	glColor3f(0.4f,0.4f,0.4f);
	char txt[16];
	float r,r1;
	if(m_ScreenHeight < m_ScreenWidth)
		r = m_ScreenHeight/2.2/m_Scale; 
	else
		r = m_ScreenWidth/2.2/m_Scale; 

	if(r > 100)
		r1 = r;
	else
		r1 = 100;
	
	glBegin(GL_LINES);
	for(int i = 0; i <= 360; i+=DEFAULT_CIRCLE_DEGREE)
	{
		double x = r1  * sin(i * nvPI/180);
		double y = r1  * cos(i * nvPI/180);
		glVertex3f(x,y,0.0);
		glVertex3f(0,0,0.0);
	}
	glEnd();
	
	for(int i = 0; i < 360; i+=DEFAULT_CIRCLE_DEGREE)
	{
		double x = r  * sin(i * nvPI/180);
		double y = r  * cos(i * nvPI/180);
		sprintf(txt,"%d %c",abs(i),176);
		RenderText(x, y, txt);
	}

}

void CGrid::RenderDirection()
{
	/*
	float r;
	if(m_ScreenHeight < m_ScreenWidth)
		r = m_ScreenHeight/2.5/m_Scale; 
	else
		r = m_ScreenWidth/2.5/m_Scale; 
	
	char txt[8];
	int count = GetDirectionLength();
	for(int i = 0; i < count; i++)
	{
		double x = r  * sin(i * (360/count) * nvPI/180);
		double y = r  * cos(i * (360/count) * nvPI/180);
		sprintf(txt,"%ls" ,GetDirection(i));
		RenderText(x, y, txt);
	}
	*/

}

void CGrid::RenderReferencePoint()
{
	glPointSize(5);
	glBegin(GL_POINTS);
		glVertex2f(0.0f,0.0f);
	glEnd();
	glPointSize(1);
}

void CGrid::RenderLastPoint()
{
	double dlon,dlat;
	glLineWidth(3);
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	//dlon = m_Station->GetLastPoint().dlon;
	//dlat = m_Station->GetLastPoint().dlat;
		
	glBegin(GL_LINES);
		glVertex2f(0.0f,0.0f);
		glVertex2f(dlon,dlat);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0.0f,0.0f);
		glVertex2f(dlon,0.0);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(0.0f,0.0f);
		glVertex2f(0.0,dlat);
	glEnd();
	
	glPointSize(6);
	glBegin(GL_POINTS);
		glVertex2f(dlon,dlat);
	glEnd();
		
	char txt[16];
	//sprintf(txt,"%4.2f",m_Station->GetLastPoint().d);
	sprintf(txt,"%s","test");
	RenderText(dlon,dlat,txt);
	glLineWidth(1);
}


void CGrid::RenderData()
{
	glEnable(GL_BLEND);
	glPointSize(2);
	glColor3f(0.0f,1.0f,0.0f);
//	if(m_Buffer->GetLength() > 0)
	//	RenderGeometry(GL_POINTS,m_Buffer->GetRawVertex(),m_Buffer->GetRawColor(),m_Buffer->GetLength());
	
	glPointSize(1);
	glDisable(GL_BLEND);
}	

void CGrid::RenderDebug()
{
	/*
	wxFont f = dc.GetFont();
	
	wxFont font;
	font.SetPointSize(12);
	dc.SetFont(font);
	dc.DrawText(wxString::Format(_("Zoom %d"),m_Scale),10,10);
	dc.DrawText(wxString::Format(_("Cx %d"),m_CenterX),10,25);
	dc.DrawText(wxString::Format(_("CY %d"),m_CenterY),10,45);
	dc.DrawText(wxString::Format(_("Lon %f"),GetRefLon()),10,60);
	dc.DrawText(wxString::Format(_("Lat %f"),GetRefLat()),10,75);
	dc.SetFont(f);
		
//	dc.DrawText(wxString::Format(_("Wheel %d"),m_Wheel),10,20);
	*/
}

void CGrid::Render()
{
	if( !this->IsShownOnScreen() )
		return;

	SetValues();
#ifdef _3D
	Update3DViewPort();
#else
	UpdateViewPort();
#endif
		
	glClearColor((float)GetBGColor().Red()/255, (float)GetBGColor().Green()/255, (float)GetBGColor().Blue()/255, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glEnable(GL_POINT_SMOOTH);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GetMutex()->Lock();
	RenderGrid();
	RenderGridText();
	RenderAccuracyCircle();
	Render2Circle();
	Render2CircleDegrees();
	RenderDirection();
	RenderReferencePoint();
	RenderData();
	RenderLastPoint();
	GetMutex()->Unlock();
	
    SwapBuffers();
	glDisable(GL_BLEND);
	glDisable(GL_POINT_SMOOTH);
}

void CGrid::SetValues()
{
	m_GridStep =  abs(m_GridWidth / 10 / m_Scale);
	
	if(m_GridStep <= 10)
		m_GridStep = 10;

	m_CenterX = m_ScreenWidth/2;
	m_CenterY = m_ScreenHeight/2;

}
