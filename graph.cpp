#include <wx/wx.h>
#include "graph.h"
#include "conf.h"
#include "options.h"
#include "tools.h"
#include "NaviDrawer.h"
#include "render.h"


BEGIN_EVENT_TABLE(CGraph,wxGLCanvas)
	EVT_PAINT(OnPaint)
	EVT_SIZE(OnSize)
	EVT_MOUSE_EVENTS(OnMouse)
	EVT_LEAVE_WINDOW(OnMouseLeave)
	EVT_ENTER_WINDOW(OnMouseEnter)
	EVT_KEY_DOWN(OnKeyUp)
END_EVENT_TABLE()



//int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE};
CGraph::CGraph(wxWindow *parent, CStation *station)
:wxGLCanvas( parent, wxID_ANY,0, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE|wxWANTS_CHARS)
{
	m_Station = station;
	GLContext = new wxGLContext(this);
	
#ifdef DC
	SetDoubleBuffered(true);
#endif
	m_Font = new FTPixmapFont(GetFontPath().mb_str(wxConvUTF8).data());
	m_Font->FaceSize(14);
		
	m_Selected = false;
	m_MoveX = 0;
	m_MoveY = 0;
	m_Scale = 1;
//	m_CenterX = 0;
//	m_CenterY = 0;
	m_OldMoveX = 0;
	m_OldMoveY = 0;
	m_ScaleFactor = 1;
	m_Arrow = 0.0;
	m_Rescale = false;
	m_Seconds = m_Station->GetDataBefore();
}

CGraph::~CGraph()
{
	delete m_Font;
	delete GLContext;
}

void CGraph::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	SetCurrent(*GLContext);
	Render();
	event.Skip();
}

void CGraph::OnSize(wxSizeEvent &event)
{
	Refresh();
	int w, h;

    GetClientSize(&w, &h);

    m_ScreenWidth = w;
    m_ScreenHeight = h;

	event.Skip();
}

void CGraph::OnMouseLeave(wxMouseEvent &event)
{
	Refresh();
	event.Skip();
}

void CGraph::OnMouseEnter(wxMouseEvent &event)
{
	event.Skip();
}

void CGraph::OnKeyUp(wxKeyEvent &event)
{
	switch( event.GetKeyCode() ) 
	{
		case WXK_LEFT:		m_MoveX+=10;	break;
		case WXK_RIGHT:		m_MoveX-=10;	break;
		case 61:			SetScaleUp();	break;
		case 45:			SetScaleDown(); break;
	}
	
	int omx = m_OldMoveX;

	m_OldMoveX = m_MoveX;

	if(m_Scale > MAX_SCALE)
		m_Scale = MAX_SCALE;
	
	if(m_Scale < MIN_SCALE)
	{
		m_MoveX = omx;
		m_Scale = MIN_SCALE;
		return;
	}else{
		
		m_OldMoveX = m_MoveX;
			
	}
		
	
	Refresh(false);
}

void CGraph::OnMouse(wxMouseEvent &event) 
{
	bool refresh = false;
	m_MouseX = event.GetX();
	m_MouseY = event.GetY();
		
	if (event.Dragging()) 
	{
        float vx = m_OldX - m_MouseX;
        float vy = m_OldY - m_MouseY;
					
		m_MoveX -= vx;
        //m_MoveY = vy;
		
		m_OldMoveX = m_MoveX;
        m_OldMoveY = m_MoveY;
		
		refresh = true;
				        
    }
    else if (event.GetWheelRotation() > 0) {

		SetScaleUp();
		refresh = true;
		        
    }
    else if (event.GetWheelRotation() < 0) {
				
		SetScaleDown();
		refresh = true;
		        
    };
		
	m_OldX = m_MouseX;
	m_OldY = m_MouseY;
	
	if(refresh)
		Refresh();
	
	event.Skip();
}

void CGraph::SetScaleUp()
{
	m_MoveX += (m_OldMoveX - m_MouseX)/m_Scale;
	m_Scale++;

	if(m_Scale > MAX_SCALE)
	{
		m_Scale = MAX_SCALE;
		return;
	}
				
	m_OldMoveX = m_MoveX;
  
}

void CGraph::SetScaleDown()
{
	m_MoveX -= (m_OldMoveX - m_MouseX)/m_Scale;
	m_Scale--;
	int omx = m_OldMoveX;

	if(m_Scale < MIN_SCALE)
	{
		m_MoveX = omx;
		m_Scale = MIN_SCALE;
		return;
	}else{
		
		m_OldMoveX = m_MoveX;
	}
	
}

void CGraph::SetPointsBuffer(CBuffer *ptr)
{
	m_Buffer = ptr;
}

void CGraph::SetTitle(const wchar_t *v)
{
	m_Title = v;
}

void CGraph::UpdateViewPort()
{
	glViewport(0, 0, (GLint)  m_ScreenWidth, (GLint) m_ScreenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
	
	//glOrtho(0, m_ScreenWidth, m_ScreenHeight, 0, -1.0, 1.0f);
		
	glOrtho(m_GraphLeft,  m_GraphRight, m_GraphBottom , m_GraphTop, -1.0, 1.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
	glTranslatef(m_MoveX*m_XScale ,m_MoveY*m_YScale,0.0);
	glScalef(m_Scale,1.0,1.0);
	
	//glTranslatef(-m_Buffer->GetLength(),-GetLastAccuracy(),0.0);
	//glTranslatef(m_ScreenWidth-10,m_ScreenHeight/2,0.0);
}

void CGraph::RenderText( float x, float y, const char *text )
{		
	glRasterPos2f(x,y);
	m_Font->Render(text,-1,FTPoint(),FTPoint(),FTGL::RENDER_ALL);
}

void CGraph::RenderText( float x, float y, const wchar_t *text )
{		
	glRasterPos2f(x,y);
	m_Font->Render(text,-1,FTPoint(),FTPoint(),FTGL::RENDER_ALL);
}

void CGraph::RenderGrid()
{
		
	int width = m_GraphRight;
	int height = m_GraphTop;
	char txt[64];
	
	glColor3f(0.3f,0.3f,0.3f);
	glBegin(GL_LINES);
	for(int i = 0 ; i < m_Station->GetPointsCount(); i+=900)
	{	
		glVertex2f(i,m_GridTop); 
		glVertex2f(i,m_GridBottom);
	}

	glColor4f(0.6f,0.6f,0.6f,1.0);
	glBegin(GL_LINES);
	for(int i = 3600 ; i <= m_Station->GetPointsCount(); i+=3600)
	{	
		glVertex2f(m_Station->GetPointsCount()-i,m_GraphTop); 
		glVertex2f(m_Station->GetPointsCount()-i,m_GraphBottom);
	}
	
	glColor3f(0.3f,0.3f,0.3f);
	glVertex2f(m_GraphLeft,m_GridTop);
	glVertex2f(m_GraphRight,m_GridTop);

	glVertex2f(m_GraphLeft,m_GridBottom);
	glVertex2f(m_GraphRight,m_GridBottom);
			
	glEnd();
		
	glColor4ub(GetFGColor().Red() ,GetFGColor().Green(),GetFGColor().Blue(),GetFGColor().Alpha());
	
	int count = 1;
	for(int i  = 3600; i < m_Station->GetPointsCount(); i+=3600)
	{	
		sprintf(txt,"-%dh",count);
		RenderText(m_Station->GetPointsCount() - i,m_GridTop,txt);
		count++;
	}

	sprintf(txt,"%ls: %4.2f",GetMsg(MSG_MAX),m_GridTop);
	RenderText(m_GridLeft,m_GridTop,txt);
	sprintf(txt,"%ls: %4.2f",GetMsg(MSG_MIN),m_GridBottom);
	RenderText(m_GridLeft,m_GridBottom,txt);
		
}

void CGraph::RenderData()
{
	glEnable(GL_BLEND);
	glPointSize(2);
	if(m_Buffer->GetLength() > 0)
	{
		RenderGeometry(GL_POINTS,m_Buffer->GetRawVertex(),m_Buffer->GetRawColor(),m_Buffer->GetLength());
		RenderGeometry(GL_LINE_STRIP,m_Buffer->GetRawVertex(),m_Buffer->GetRawColor(),m_Buffer->GetLength());
	}
	glPointSize(1);
	glDisable(GL_BLEND);
}	

void CGraph::RenderTitle()
{
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(0,m_ScreenWidth,m_ScreenHeight,0,0,1);	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
	float CenterX = m_ScreenWidth/2 - m_Font->Advance(m_Title)/2;
	glColor4ub(GetFGColor().Red() ,GetFGColor().Green(),GetFGColor().Blue(),GetFGColor().Alpha());
	RenderText(CenterX,15,m_Title);
	glPopMatrix();
	
}

void CGraph::RenderCube()
{
	glColor3f(1,1,1);
	float x,y,z; 
	x = y = z = m_Station->GetAccuracyMax();
	glBegin(GL_LINE_LOOP);
        glVertex3f( x, y, z);        glVertex3f(-x, y, z);        glVertex3f(-x,-y, z);        glVertex3f( x,-y, z);
    glEnd();

	glColor3f(0,1,0);
    glBegin(GL_LINE_LOOP);
        glVertex3f(-x,-y,-z);        glVertex3f(-x, y,-z);        glVertex3f( x, y,-z);        glVertex3f( x,-y,-z);
    glEnd();

	glColor3f(0,0,1);
    glBegin(GL_LINE_LOOP);
        glVertex3f( x, y, z);        glVertex3f( x, y,-z);        glVertex3f(-x, y,-z);        glVertex3f(-x, y, z);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(-x,-y,-z);
        glVertex3f( x,-y,-z);
        glVertex3f( x,-y, z);
        glVertex3f(-x,-y, z);
    glEnd();

	glBegin(GL_LINE_LOOP);
        //glNormal3f( 1.0f, 0.0f, 0.0f);
        glVertex3f( x, y, z);
        glVertex3f( x,-y, z);
        glVertex3f( x,-y,-z);
        glVertex3f( x, y,-z);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(-x,-y,-z);
        glVertex3f(-x,-y, z);
        glVertex3f(-x, y, z);
        glVertex3f(-x, y,-z);
    glEnd();


   // glFlush();

    //CheckGLError();
}

//{

	//glColor3f(0.0f,1.0f,0.0f);
	//glVertex2i(m_GridLeft,GetAccuracyMax());
	//glVertex2i(m_GridRight,GetAccuracyMax());

//}


void CGraph::Render()
{
	if( !this->IsShownOnScreen() )
		return;
	
	SetValues();
	UpdateViewPort();
	glClearColor((float)GetBGColor().Red()/255, (float)GetBGColor().Green()/255,(float)GetBGColor().Blue()/255, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
	glEnable(GL_POINT_SMOOTH);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GetMutex()->Lock();
	
	RenderGrid();
	RenderData();
	RenderTitle();

	GetMutex()->Unlock();

    SwapBuffers();
	
	glDisable(GL_BLEND);
	glDisable(GL_POINT_SMOOTH);
}

void CGraph::SetValues()
{
	float offsetX = (m_Buffer->GetMax() - m_Buffer->GetMin()) * 0.15;
	float offsetY = m_ScreenWidth * 0.15;

	m_GraphTop = m_Buffer->GetMax() + offsetX;
	m_GraphBottom = m_Buffer->GetMin() - offsetX;

	m_GraphLeft = -offsetY;
	m_GraphRight = m_Buffer->GetLength() + offsetY;
	
	m_GridTop = m_Buffer->GetMax();
	m_GridBottom = m_Buffer->GetMin();
	m_GridLeft = 0;
	m_GridRight = m_Buffer->GetLength();
			
	m_XScale = m_GraphRight / m_ScreenWidth;
	m_YScale = (m_GraphBottom + m_GraphTop) / m_ScreenWidth;
		
}
