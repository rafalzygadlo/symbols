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

int TimeOffset[] = {60,3600,86400,0};
//int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE};
CGraph::CGraph(wxWindow *parent)
:wxGLCanvas( parent, wxID_ANY,0, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE|wxWANTS_CHARS)
{
	GLContext = new wxGLContext(this);
	
#ifdef DC
	SetDoubleBuffered(true);
#endif
	m_Font = new FTPixmapFont(GetFontPath().mb_str(wxConvUTF8).data());
	m_Font->FaceSize(14);
		
	//m_Selected = false;
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
	m_Title = wxEmptyString;
	m_Speed = 1;
	m_Hours = m_Minutes = m_Seconds = 0;
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
		case WXK_LEFT:		m_MoveX+=10*m_Speed;	break;
		case WXK_RIGHT:		m_MoveX-=10*m_Speed;	break;
		case 61:			SetScaleUp();			break;
		case 45:			SetScaleDown();			break;
	}
	
	if(event.GetKeyCode() ==  m_OldKey)
		m_Speed++;
	else
		m_Speed = 1;
	
	m_OldKey = event.GetKeyCode();
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
	
	if(m_MoveX > 0)
		m_MoveX = 0;

	//if(m_MoveX < m_GraphRight)
		//m_MoveX = m_GraphRight;
	
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

		//SetScaleUp();
		refresh = true;
		        
    }
    else if (event.GetWheelRotation() < 0) {
				
		//SetScaleDown();
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

void CGraph::Clear()
{	
	m_Buffer.Clear();
	m_Color.Clear();
}


void CGraph::AddPoint(nvPoint3f v)
{
	m_Buffer.Append(v);
}

void CGraph::AddColor(nvRGBA v)
{
	m_Color.Append(v);
}

void CGraph::SetTitle(const wchar_t *v)
{
	m_Title = v;
}

void CGraph::SetMin(float v)
{
	m_Min = v;
}

void CGraph::SetMax(float v)
{
	m_Max = v;
}

void CGraph::SetTimeTo(int v)
{
	m_TimeTo = v;
}

void CGraph::SetTimeFrom(int v)
{
	m_TimeFrom = v;
}

void CGraph::UpdateViewPort()
{
	glViewport(0, 0, (GLint)  m_ScreenWidth, (GLint) m_ScreenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
	//glOrtho(0, m_ScreenWidth, m_GraphBottom, m_GraphTop, -1.0, 1.0f);
		
	glOrtho(m_GraphLeft,  m_GraphRight, m_GraphBottom , m_GraphTop, -1.0, 1.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
	//glTranslatef(m_MoveX*m_XScale ,m_MoveY*m_YScale,0.0);
	//glScalef(m_Scale,1.0,1.0);
	
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
	
	glPushMatrix();
	//glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
	//glOrtho(0,m_ScreenWidth,m_ScreenHeight,0,0,1);	
	
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();


	glColor4f(0.6f,0.6f,0.6f,1.0);

	
	//seconds

	float a = m_GraphRight/m_Scale;
	int width = m_ScreenWidth;
	//int b = m_MoveX/m_Scale;
	//glScalef(1.0,1.0,1.0);
	//glTranslatef(0.0,0.0,0.0);
	
	glBegin(GL_LINES);
	for(float i = m_GraphLeft; i < m_GraphRight;  i+=(m_GraphRight - m_GraphLeft)/10)
 	
	{
		glVertex2f(i ,m_GraphBottom);	
		glVertex2f(i ,m_GraphTop);	
	}

	for(float i = m_GraphBottom; i < m_GraphTop;  i+=(m_GraphTop - m_GraphBottom)/5)
 	{
		glVertex2f(m_GraphLeft,i);	
		glVertex2f(m_GraphRight,i);	
	}

	//for(int i = m_GraphLeft ; i < m_TimeTo; i+=SECONDS_IN_MINUTE)
	//{
		//glVertex2f(i,m_GridTop);	glVertex2f(i,m_GridBottom);	
	//}
	//for(int i = m_GraphLeft ; i < m_Seconds; i+=60)					{	glVertex2f(i,m_GridTop);	glVertex2f(i,m_GridBottom);	}
		
	glColor4f(0.9f,0.9f,0.9f,0.8f);
	//glVertex2f(m_GraphLeft,m_GridTop);
	//glVertex2f(m_GraphRight,m_GridTop);

	//glVertex2f(m_GraphLeft,m_GridBottom);
	//glVertex2f(m_GraphRight,m_GridBottom);
			
	glEnd();
	
	char txt1[64];
	char txt2[64];
	
	for(float i = m_GraphLeft; i < m_GraphRight;  i+=(m_GraphRight - m_GraphLeft)/10)
 	{
	
		time_t t = m_TimeFrom + i - (m_MoveX/m_Scale);
		tm *_t = gmtime(&t);

		sprintf(txt1,"%02d:%02d:%02d",_t->tm_hour,_t->tm_min,_t->tm_sec);
		//sprintf(txt2,"%02d:%02d:%02d",_t->tm_mon,_t->tm_mday);

		RenderText(i,m_GridTop,txt1);
		//RenderText(i,m_GridBottom+10,txt2);
	}
	

	for(int i = 0 ; i < 20;  i++)
	{
		nvPoint3f p = m_Buffer.Get(i);
		sprintf(txt1,"%4.2f",p.y);
		//float s = (float)m_ScreenWidth/(m_TimeTo-m_TimeFrom);
		RenderText(p.x ,p.y,txt1);
	}


	glColor4ub(GetFGColor().Red() ,GetFGColor().Green(),GetFGColor().Blue(),GetFGColor().Alpha());

	/*
	sprintf(txt1,"%ls: %4.2f",GetMsg(MSG_MAX),m_GridTop);
	RenderText(m_GraphLeft-(m_MoveX),m_GridTop,txt1);
	sprintf(txt1,"%ls: %4.2f",GetMsg(MSG_MIN),m_GridBottom);
	RenderText(m_GridLeft,m_GridBottom + (10/m_YScale),txt1);
	*/
	glPopMatrix();

}

void CGraph::RenderData()
{
	glPushMatrix();
	glTranslatef(m_MoveX*m_XScale ,m_MoveY*m_YScale,0.0);
	glScalef(m_Scale,1.0,1.0);

	glEnable(GL_BLEND);
	glPointSize(5);
	if(m_Buffer.Length() > 0)
	{
		RenderGeometry(GL_POINTS,m_Buffer.GetRawData(),m_Color.GetRawData(),m_Buffer.Length());
		RenderGeometry(GL_LINE_STRIP,m_Buffer.GetRawData(),m_Color.GetRawData(),m_Buffer.Length());
	}
	glPointSize(1);
	glDisable(GL_BLEND);
	glPopMatrix();
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

	//char txt[64];
	//sprintf(txt,"%ls: %4.2f",GetMsg(MSG_MAX),m_GridTop);
	//RenderText(0,15,txt);
	//sprintf(txt,"%ls: %4.2f",GetMsg(MSG_MIN),m_GridBottom);
	//RenderText(0,m_ScreenHeight,txt);


	glPopMatrix();
	
}

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
	//GetMutex()->Lock();
	
	RenderData();
	RenderGrid();
	RenderTitle();

	//GetMutex()->Unlock();

    SwapBuffers();
	
	glDisable(GL_BLEND);
	glDisable(GL_POINT_SMOOTH);
}

void CGraph::SetValues()
{
	float offsetX = (m_Max - m_Min) * 0.15;
	float offsetY = m_ScreenWidth * 0.05;

	m_GraphTop = m_Max + offsetX;
	m_GraphBottom = m_Min - offsetX;

	m_GraphLeft =  0;//-offsetY;
	m_GraphRight = m_ScreenWidth;
	//m_GraphRight = (m_TimeTo - m_TimeFrom) + offsetY;
	
	m_GridTop = m_Max;
	m_GridBottom = m_Min;
	m_GridLeft = 0;
	m_GridRight = m_ScreenWidth;
			
	//m_XScale = m_GraphRight / m_ScreenWidth;
	//m_YScale = (m_GraphBottom + m_GraphTop) / m_ScreenWidth;
	
	m_XScale = m_ScreenWidth / m_ScreenWidth;
	m_YScale = (m_GraphBottom + m_GraphTop) / m_ScreenWidth;
	
	//m_Days = m_TimeTo / SECONDS_IN_DAY;
	m_Hours = m_TimeTo / SECONDS_IN_HOUR;
	m_Minutes = m_TimeTo / SECONDS_IN_MINUTE;
	m_Seconds = m_TimeTo;
	
	//int *ptr = TimeOffset;
	//int a = 0;
	//while(*ptr)
	//{
		//a = *ptr;
		//ptr++;
	//}
}