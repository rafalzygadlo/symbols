#include "light.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include <wx/mstream.h>
#include <wx/colordlg.h>
#include <wx/dataview.h>
#include "images/del.img"
#include "images/add.img"
#include "geometrytools.h"
#include <wx/valnum.h>
#include "navidrawer.h"

extern unsigned int	add_size;
extern unsigned char add[]; 
extern unsigned int	del_size;
extern unsigned char del[]; 

BEGIN_EVENT_TABLE(CLightPanel, wxGLCanvas)
	EVT_BUTTON(ID_NEW,OnNew)
	EVT_SIZE(OnSize)
	EVT_PAINT(OnPaint)
	EVT_MOUSE_EVENTS(OnMouse)
END_EVENT_TABLE()
CLightPanel::CLightPanel(void *db, wxWindow *parent)
	:wxGLCanvas( parent, wxID_ANY,0, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE|wxWANTS_CHARS)
{
	GLContext = new wxGLContext(this);
	m_DB = db;
	//wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	//SetSizer(Sizer);
	
	//wxMemoryInputStream in_1((const unsigned char*)add,add_size);
    //wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
	//wxButton *New = new wxBitmapButton(this,ID_NEW,wxBitmap(myImage_1));
	//Sizer->Add(New,0,wxALL,1);

	//m_Sizer = new wxWrapSizer(wxHORIZONTAL);
	//Sizer->Add(m_Sizer,1,wxALL|wxEXPAND,0);
		
}

CLightPanel::~CLightPanel()
{
	for(size_t i = 0; i < m_List.size();i++)
	{
		CLight *Light = (CLight*)m_List.Item(i);
		delete Light;
	}
	
	delete GLContext;
}

void CLightPanel::OnMouse(wxMouseEvent &event)
{
	m_MouseX = event.GetX();
	m_MouseY = -event.GetY();
	Refresh();
}

void CLightPanel::OnSize(wxSizeEvent &event)
{
	GetClientSize(&m_Width, &m_Height);
	Refresh();
}

void CLightPanel::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	
	int X = m_MouseX - m_CenterX;
	int Y = m_MouseY - m_CenterY;
	double rad_angle = atan2((double)X, (double)Y);
	double angle = (nvToDegree(rad_angle) - 180) * -1;
	
	SetCurrent(*GLContext);
	Render();
	event.Skip();
			
}

void CLightPanel::UpdateViewPort()
{
	glViewport(0, 0, (GLint)  m_Width, (GLint) m_Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
			
	glOrtho(-m_Width/2,  m_Width/2, -m_Height/2 , m_Height/2, -1.0, 1.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

void CLightPanel::SetValues()
{
	m_CenterX = 0;
	m_CenterY = 0;
	m_Radius = m_Width/1.5;
	
	for(size_t i = 0; i < m_List.size();i++)
	{
		CLight *Light = (CLight*)m_List.Item(i);
		Light->SetRadius(m_Radius);
	}
}

void CLightPanel::SelectSectors()
{

	GLuint selectBuf[512];
	GLint hits;

	glSelectBuffer (512, selectBuf);
	glRenderMode(GL_SELECT);

	glInitNames();
	glPushName(0);
   
	glPushMatrix ();
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0.0, 5.0, 0.0, 5.0, 0.0, 10.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
   
	glPointSize(5);
	for(size_t i = 0; i < m_List.size();i++)
	{
		CLight *Light = (CLight*)m_List.Item(i);
		glLoadName(Light->GetId());
		Light->Render();
	}
	glPopMatrix ();
	
	hits = glRenderMode (GL_RENDER);
	unsigned int i, j;
	GLuint names, *ptr;

	printf ("hits = %d\n", hits);
	ptr = (GLuint *) selectBuf;
	for (i = 0; i < hits; i++) 
	{ /*  for each hit  */
      names = *ptr;
      printf (" number of names for hit = %d\n", names); ptr++;
      printf("  z1 is %g;", (float) *ptr/0x7fffffff); ptr++;
      printf(" z2 is %g\n", (float) *ptr/0x7fffffff); ptr++;
      printf ("   the name is ");
      
	  for (j = 0; j < names; j++) 
	  {     /*  for each name */
         printf ("%d ", *ptr); ptr++;
      }
      printf ("\n");
   }
}



void CLightPanel::RenderSectors()
{
	glPointSize(5);
	for(size_t i = 0; i < m_List.size();i++)
	{
		CLight *Light = (CLight*)m_List.Item(i);
		Light->Render();
	}
}

void CLightPanel::RenderMouse()
{
	nvDrawPoint(m_MouseX,m_MouseY);
}

void CLightPanel::Render()
{

	if( !this->IsShownOnScreen() )
		return;
	
	SetValues();
	
	glClearColor(0.0, 0.0,0.0, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	SelectSectors();
	
	UpdateViewPort();
	RenderSectors();
	RenderMouse();
    SwapBuffers();
}

size_t CLightPanel::GetCount()
{
	return m_List.size();
}

CLight *CLightPanel::GetLight(int id)
{
	return (CLight*)m_List.Item(id);
}

void CLightPanel::OnNew(wxCommandEvent &event)
{
	CLight *Light = new CLight();
	Append(Light);
	
}

void CLightPanel::OnDelete(CLight *panel)
{
	//RemovePanel(panel);
}

void CLightPanel::Append(CLight *panel)
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


CLight::CLight()
{
			
}

CLight::~CLight()
{

}

void CLight::Render()
{
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = m_Radius;






	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glColor4ub(m_Color.Red(),m_Color.Green(),m_Color.Blue(),220);
	nvDrawCircleArcFilled(&c,m_SectorFrom,m_SectorTo);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_BLEND);
		
}

int CLight::GetId()
{
	return m_Id;
}

void CLight::SetId(int v)
{
	m_Id = v;
}

void CLight::SetColor(wxColor color)
{
	m_Color = color;
}

void CLight::SetCoverage(float v)
{
	m_Coverage = v;
}

void CLight::SetSectorFrom(float v)
{
	m_SectorFrom = v;
}

void CLight::SetSectorTo(float v)
{
	m_SectorTo = v;
}

void CLight::SetRadius(float v)
{
	m_Radius = v;
}

//GET
wxColor CLight::GetColor()
{
	return m_Color;
}

float CLight::GetCoverage()
{
	return m_Coverage;
}

float CLight::GetSectorFrom()
{
	return m_SectorFrom;
}

float CLight::GetSectorTo()
{
	return m_SectorTo;
}
