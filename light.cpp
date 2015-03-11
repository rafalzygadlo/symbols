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
	m_DB = db;
	m_Selected = NULL;
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
	if(m_Selected)
	{
		Menu->Append(ID_EDIT,GetMsg(MSG_EDIT));
		Menu->Append(ID_DELETE,GetMsg(MSG_DELETE));
	}

	PopupMenu(Menu);
	delete Menu;
}

void CLightPanel::OnMouse(wxMouseEvent &event)
{
	m_MouseX = event.GetX() - m_CenterX;
	m_MouseY = event.GetY() - m_CenterY;

	if(event.LeftDown())
		m_LeftDown = !m_LeftDown;
	if(event.RightDown())
		m_RightDown = !m_RightDown;
	
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
	CSectorDialog *SectorDialog = new CSectorDialog();
	SectorDialog->ShowModal();
	delete SectorDialog;
}

void CLightPanel::OnEdit(wxCommandEvent &event)
{

}

void CLightPanel::OnDelete(wxCommandEvent &event)
{

}

void CLightPanel::UpdateViewPort()
{
	glViewport(0, 0, (GLint)  m_Width, (GLint) m_Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
			
	//glOrtho(-m_Width,  m_Width, -m_Height , m_Height, -1.0, 1.0f);
	
	glOrtho(0.0,  m_Width, m_Height, 0.0, -1.0, 1.0f);
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
	glOrtho (m_MouseX - 1, m_MouseX + 1, m_MouseY - 1, m_MouseY + 1, 0.0, 10.0);
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
	
	if(m_LeftDown)
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

	ptr = (GLuint *) select;
	for (i = 0; i < hits; i++) 
	{ 
		names = *ptr;
		ptr+=3;
	  for (j = 0; j < names; j++) 
	  {     
		  m_Selected = (CSector*)m_List.Item(*ptr);
		  return;
      }
    }
	
	m_Selected = NULL;
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
	if(m_Selected)
		m_Selected->RenderSelected();
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

void CLightPanel::Append(CSector *panel)
{
	m_List.Add(panel);
}

wxArrayPtrVoid CLightPanel::GetItems()
{
	return m_List;
}

void CLightPanel::Read(wxString query)
{
	if(!my_query(m_DB,query))
		return;
	
	int rows = 0;
	void *result = db_result(m_DB);
	char **row;
	
	while(row = (char**)db_fetch_row(result))
	{
		wxString str(row[0],wxConvUTF8);
		wxString name(row[1],wxConvUTF8);
		//CItem *Item = new CItem(this,name);
		//Item->_SetId(str);
		//m_Items.Add(Item);
	}

	db_free_result(result);
	
}

