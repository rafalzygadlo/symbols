#include <wx/wx.h>
#include <wx/notebook.h>
#include "symbol.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "navidrawer.h"
#include "ais.h"
#include "options.h"
#include "render.h"
#include "commanddialog.h"
#include "sbms.h"


CSymbol::CSymbol(CNaviBroker *broker)
{
	m_Broker = broker;
	m_Scale = 1;
	m_SmoothScaleFactor = 1;
	m_RectWidth = 0;
	m_RectHeight = 0;
	m_TranslationX = 0;
	m_TranslationY = 0;
	m_Exists = false;
	m_Selected = false;
	m_TickExit = false;
	m_Monitoring = SYMBOL_NOT_IN_MONITORING;
	m_DB = NULL;
	m_NameFont = NULL;
}

CSymbol::~CSymbol()
{
	for(int i = 0; i < m_DriverList.Length();i++)
	{
		delete m_DriverList.Get(i);
	}	
	
	m_Broker = NULL;
}

void CSymbol::SetFont(nvFastFont *ptr)
{
	m_NameFont = ptr;
}

void CSymbol::SetDB(void *db)
{
	m_DB = db;
}

void CSymbol::OnTickExit()
{
	m_TickExit = true;
}

void CSymbol::SetSmoothScaleFactor(double _Scale) 
{
	int factor = GetScaleFactor();
	if( _Scale > factor )
		m_SmoothScaleFactor = _Scale;
	else
		m_SmoothScaleFactor = factor;
}

void CSymbol::SetValues()
{
	if(m_Broker == NULL)
		return;
	
	m_Scale  = m_Broker->GetMapScale();
	SetSmoothScaleFactor( m_Scale );
	
	m_RectWidth = RECT_WIDTH / m_SmoothScaleFactor;
	m_RectHeight = RECT_HEIGHT / m_SmoothScaleFactor;
	m_TranslationX = 0.0; //(RECT_WIDTH /2)/SmoothScaleFactor; 
	m_TranslationY = -(RECT_HEIGHT /2)/m_SmoothScaleFactor; 
	m_Broker->GetVisibleMap(m_VisibleMap);
	
}

void CSymbol::RenderSymbol()
{
//	SetSymbolColor();
	glPushMatrix();
		
	glTranslatef(m_LonMap,m_LatMap,0.0f);
	
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = m_RectWidth/2;
	
	nvDrawCircleFilled(&c);
	
	glColor4f(0.0,0.0,0.0,0.5);
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

void CSymbol::RenderRestricted()
{
	glColor4f(1.0,0.0,0.0,0.1);
	nvCircle c;
	c.Center.x = m_LonMap;
	c.Center.y = m_LatMap;
	c.Radius = (double)GetRestrictedArea()/1852/GetMilesPerDegree(m_RLon,m_RLat);
	nvDrawCircleFilled(&c);
}

void CSymbol::Render()
{
	
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

	SetValues();
	RenderSymbol();
	//RenderRestricted();

	glDisable(GL_BLEND);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);

}

wxString CSymbol::GetText()
{
	wxString str;
	str.Append(_("<table border=0 cellpadding=2 cellspacing=0 width=100%>"));
	//str << wxString::Format(_("<tr><td><font size=5>%s(%d)</font></td></tr>"),ptr->GetName(),ptr->GetProtocolVersion());
	str << wxString::Format(_("<tr><td><font size=3><b>%s(%s)</b></font></td></tr>"),GetName(),GetNumber());
	//str << wxString::Format(_("<tr><td><font size=3>%s</font></td></tr>"),GetNumber());
	str.Append(_("</table>"));

	return str;
}

void CSymbol::OnTick(void *db)
{
	m_DB = db;
	if(m_Broker == NULL)
		return;
	
	bool result = false;
					
}

void CSymbol::AddDriver(CDriver *ptr)
{
	m_DriverList.Append(ptr);
}

CDriver *CSymbol::ExistsDriver(int id, int type)
{
	for(int i = 0; i < m_DriverList.Length();i++)
	{
		CDriver *ptr = m_DriverList.Get(i);
		if(ptr->GetType() == type && ptr->GetId() == id)
			return ptr;
	}

	return NULL;
}



//SET
void CSymbol::SetColor(int id)
{
	glColor4ub(GetColor(id).R,GetColor(id).G,GetColor(id).B,GetColor(id).A);
}

void CSymbol::SetId(int v)
{
	m_Id = v;
}

void CSymbol::SetRLon(double v)		
{	
	m_RLon = v;
}

void CSymbol::SetRLat(double v)		
{	
	m_RLat = v;
}

void CSymbol::SetRLonMap(double v)	
{	
	m_RLonMap = v;
}

void CSymbol::SetRLatMap(double v)	
{	
	m_RLatMap = v;
}

void CSymbol::SetGpsLon(double v)	
{	
	m_GpsLon = v;
}

void CSymbol::SetGpsLat(double v)	
{	
	m_GpsLat = v;
}

void CSymbol::SetGpsLonMap(double v)
{
	m_GpsLonMap = v;
}

void CSymbol::SetGpsLatMap(double v)
{	
	m_GpsLatMap = v;
}

void CSymbol::SetLon(double v)		
{	
	m_Lon = v;
}

void CSymbol::SetLat(double v)		
{	
	m_Lat = v;
}

void CSymbol::SetLonMap(double v)	
{
	m_LonMap = v;
}

void CSymbol::SetLatMap(double v)	
{	
	m_LatMap = v;
}

void CSymbol::SetNumber(wxString v)
{	
	m_Number = v;
}

void CSymbol::SetName(wxString v)
{	
	m_Name = v;
}

void CSymbol::SetExists(bool v)
{
	m_Exists = v;
}


//GET
int CSymbol::GetId()
{
	return m_Id;
}

double CSymbol::GetRLon()
{		
	return m_RLon;
}

double CSymbol::GetRLat()
{		
	return m_RLat;
}

double CSymbol::GetRLonMap()
{	
	return m_RLonMap;
}

double CSymbol::GetRLatMap()
{	
	return m_RLatMap;
}

double CSymbol::GetLon()
{		
	return m_Lon;
}

double CSymbol::GetLat()
{		
	return m_Lat;
}

double CSymbol::GetLonMap()
{	
	return m_LonMap;
}

double CSymbol::GetLatMap()
{	
	return m_LatMap;
}

wxString CSymbol::GetName()
{
	return m_Name;
}

wxString CSymbol::GetNumber()
{
	return m_Number;
}

int CSymbol::GetDriverCount()
{
	return m_DriverList.Length();
}

CDriver *CSymbol::GetDriver(int v)
{
	return m_DriverList.Get(v);
}

bool CSymbol::GetExists()
{
	return m_Exists;
}