#include "light.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include <wx/colordlg.h>
#include <wx/valnum.h>
#include "navidrawer.h"
#include "sectordialog.h"

BEGIN_EVENT_TABLE(CLightPanel, wxGLCanvas)
	EVT_BUTTON(ID_NEW,OnNew)
	EVT_SIZE(OnSize)
	EVT_PAINT(OnPaint)
	EVT_MOUSE_EVENTS(OnMouse)
	EVT_CONTEXT_MENU(OnContextMenu)
	EVT_MENU(ID_NEW,OnNew)
	EVT_MENU(ID_EDIT,OnEdit)
	EVT_MENU(ID_DELETE,OnDelete)
END_EVENT_TABLE()
CLightPanel::CLightPanel(void *db, wxWindow *parent)
	:wxGLCanvas( parent, wxID_ANY,0, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE|wxWANTS_CHARS)
{
	GLContext = new wxGLContext(this);
	//m_DB = db;
}

CLightPanel::~CLightPanel()
{
	for(size_t i = 0; i < m_List.size();i++)
	{
		CSector *ptr = (CSector*)m_List.Item(i);
		delete ptr;
	}
	
	delete GLContext;
}

void CLightPanel::OnContextMenu(wxContextMenuEvent &event)
{
	wxMenu *Menu = new wxMenu();
	Menu->Append(ID_NEW,GetMsg(MSG_NEW));
	if(m_Select.size() > 0)
	{
		Menu->Append(ID_EDIT,GetMsg(MSG_EDIT));
		Menu->Append(ID_DELETE,GetMsg(MSG_DELETE));
	}
	Refresh();
	PopupMenu(Menu);
	delete Menu;
}

void CLightPanel::OnMouse(wxMouseEvent &event)
{
	m_MouseX = event.GetX() - m_CenterX;
	m_MouseY = -event.GetY() + m_CenterY;

	if(event.LeftDown())
		m_LeftDown = !m_LeftDown;
	if(event.RightDown())
		m_RightDown = !m_RightDown;
	
	//if(m_LeftDown || m_RightDown)
		Refresh();
	event.Skip();
}

void CLightPanel::OnSize(wxSizeEvent &event)
{
	GetClientSize(&m_Width, &m_Height);
	Refresh();
}

void CLightPanel::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	SetCurrent(*GLContext);
	Render();
	event.Skip();
	
}

void CLightPanel::OnNew(wxCommandEvent &event)
{
	CSector *Sector = new CSector();
	Append(Sector);
	Refresh();
	
	CSectorDialog *SectorDialog = new CSectorDialog(this);
	SectorDialog->SetSector(Sector);
	if(SectorDialog->ShowModal() == wxID_CANCEL)
		Remove(Sector);
	delete SectorDialog;
}

void CLightPanel::OnEdit(wxCommandEvent &event)
{

	for(size_t i = 0; i < m_Select.size();i++)
	{
		CSector *Sector = (CSector*)m_Select.Item(i);
		CSectorDialog *SectorDialog = new CSectorDialog(this);
		SectorDialog->SetSector(Sector);
		SectorDialog->ShowModal();
		delete SectorDialog;
	}
}

void CLightPanel::OnDelete(wxCommandEvent &event)
{
	for(size_t i = 0; i < m_Select.size();i++)
	{
		Remove((CSector*)m_Select.Item(i));
	}

	m_Select.Clear();
		
}

void CLightPanel::UpdateViewPort()
{
	glViewport(0, 0, (GLint)  m_Width, (GLint) m_Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
			
	//glOrtho(-m_Width,  m_Width, -m_Height , m_Height, -1.0, 1.0f);
	
	glOrtho(0.0,  m_Width, 0.0, m_Height,  -1.0, 1.0f);
	glTranslatef(m_CenterX,m_CenterY,1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

void CLightPanel::SetValues()
{
	if(m_Width < m_Height)
		m_Size = m_Width;
	else
		m_Size = m_Height;
	
	m_CenterX = m_Width/2;
	m_CenterY = m_Height/2;
	m_Radius = m_Size/3;
	
	for(size_t i = 0; i < m_List.size();i++)
	{
		CSector *Sector = (CSector*)m_List.Item(i);
		Sector->SetRadius(m_Radius);
	}
}

void CLightPanel::SelectSector()
{
	GLuint selectBuf[512];
	GLint hits;

	glSelectBuffer (16, selectBuf);
	glRenderMode(GL_SELECT);

	glInitNames();
	glPushName(0);
   
	glPushMatrix ();
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (m_MouseX - 0.1, m_MouseX + 0.1, m_MouseY - 0.1, m_MouseY + 0.1, 0.0, 10.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
   
	glPointSize(5);
	for(size_t i = 0; i < m_List.size();i++)
	{
		CSector *Sector = (CSector*)m_List.Item(i);
		glLoadName(i);
		Sector->Render();
	}
	glPopMatrix ();

	hits = glRenderMode (GL_RENDER);
	
	if(m_LeftDown || m_RightDown)
	{	
		SetSelected(hits,selectBuf);
		m_LeftDown = false;
		m_RightDown = false;
	}
	
}

void CLightPanel::SetSelected(GLint hits, GLuint *select)
{	
	unsigned int i, j;
	GLuint names, *ptr;
	
	m_Select.Clear();
	ptr = (GLuint *) select;
	for (i = 0; i < hits; i++)
	{
		names = *ptr;
		ptr+=3;
		for (j = 0; j < names; j++)
		{
			m_Select.Add(m_List.Item(*ptr));
			ptr++;
		}
    }
		
}


void CLightPanel::RenderSectors()
{
	glPointSize(5);
	for(size_t i = 0; i < m_List.size();i++) 
	{
		CSector *ptr = (CSector*)m_List.Item(i);
		ptr->Render();
	}
}

void CLightPanel::RenderSelected()
{
	for(size_t i = 0; i < m_Select.size();i++)
	{
		CSector *ptr = (CSector*)m_Select.Item(i);
		ptr->RenderSelected();
	}
	
}

void CLightPanel::RenderMouse()
{
	glPointSize(5);
	glEnable(GL_POINT_SMOOTH);
	nvDrawPoint(m_MouseX,m_MouseY);
	glDisable(GL_POINT_SMOOTH);
}

void CLightPanel::Render()
{

	if( !this->IsShownOnScreen() )
		return;
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	SetValues();
	glClearColor(0.0, 0.0, 0.0, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	SelectSector();
	
	UpdateViewPort();

	RenderSelected();
	RenderSectors();
	RenderMouse();

	SwapBuffers();
}

size_t CLightPanel::GetCount()
{
	return m_List.size();
}

CSector *CLightPanel::GetSector(int id)
{
	return (CSector*)m_List.Item(id);
}

//void CLightPanel::OnDelete()
//{
	//RemovePanel(panel);
//}

void CLightPanel::Append(CSector *v)
{
	m_List.Add(v);
}

wxArrayPtrVoid CLightPanel::GetItems()
{
	return m_List;
}

void CLightPanel::Remove(CSector *v)
{
	m_List.Remove(v);
	delete v;
}

