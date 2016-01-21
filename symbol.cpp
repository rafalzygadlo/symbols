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

void CSymbol::RenderText(float x, float y, float vx, float vy, const wchar_t *format ...)
{	
	wchar_t buffer[128];
	va_list args;
	va_start(args,format);
	//swprintf_s(buffer,format,args);
	vswprintf ( buffer, 128, format, args );
	va_end(args);
	
	m_NameFont->Print(x,y,GetFontSize()/m_SmoothScaleFactor/DEFAULT_FONT_FACTOR,0,buffer,vx,vy);

}

void CSymbol::RenderText()
{
	if(GetShowFontNames())
	{
		RenderText(GetLonMap(),GetLatMap(),0.5f,4.1f,GetName());
		RenderText(GetLonMap(),GetLatMap(),0.5f,5.4f,GetMonitoringAsString(GetMonitoring()));
	}
}

void CSymbol::RenderDriver()
{
	for(int i = 0; i < m_DriverList.Length();i++)
	{
		m_DriverList.Get(i)->Render();
		break; // tylko jeden sterownik
	}
}

void CSymbol::Render()
{
	
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

	SetValues();
	RenderSymbol();
	RenderDriver();
	RenderText();
	//RenderRestricted();

	glDisable(GL_BLEND);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);

}

wxString CSymbol::GetHtml()
{
	wxString str;
	str.Append(_("<table border=0 cellpadding=0 cellspacing=0 width=100%>"));
	str << wxString::Format(_("<tr><td><font size=3>%s(%s)</font></td></tr>"),GetName(),GetNumber());
	str.Append(_("</table>"));

	return str;
}

wxString CSymbol::GetFullHtml()
{
	wxString str;
	str.Append(_("<table border=0 cellpadding=0 cellspacing=0 width=100%%>"));
	
#ifdef WEBVIEW
	char *b64 = NULL;
	if(GetPictureAsBase64(db,ptr->GetId(),b64))
	{
		str.Append(wxString::Format(_("<tr><td><center><img src=\"data:image/png;base64,%s\"></center></td></tr>"),b64));
		free(b64);
	}
#endif	

	str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td></tr>"),GetMonitoringAsString(GetMonitoring())));
	str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td></tr>"),GetName()));
	str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td></tr>"),GetNumber()));
	str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td></tr>"),FormatLatitude(GetRLat(),DEFAULT_DEGREE_FORMAT)));
	str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td></tr>"),FormatLongitude(GetRLon(),DEFAULT_DEGREE_FORMAT)));
	
	str.Append(_("</table>"));
	return str;
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

void CSymbol::Read(void *db)
{
	fprintf(stderr,"SYMBOL %d\n",m_Id);
}

void CSymbol::RemoveDriver(CDriver *ptr)
{
	for(int i = 0; i < m_DriverList.Length();i++)
	{
		CDriver *Driver = m_DriverList.Get(i);
		if(ptr == Driver)
		{
			m_DriverList.Remove(i);
		}
	}
}

void CSymbol::ShowGraph()
{
	for(int i = 0; i < GetDriverCount(); i++)
	{
		CDriver *Driver = GetDriver(i);
		Driver->ShowGraph();
	}
}

void CSymbol::LightOn()
{
	for(int i = 0; i < GetDriverCount(); i++)
	{
		CDriver *Driver = GetDriver(i);
		_SetCommand(COMMAND_LIGHT_ON,Driver->GetId(),Driver->GetMMSI(),Driver->GetSBMSID(),Driver->GetBaseStationId(), true);
	}
}

void CSymbol::LightOff()
{
	for(int i = 0; i < GetDriverCount(); i++)
	{
		CDriver *Driver = GetDriver(i);
		_SetCommand(COMMAND_LIGHT_OFF,Driver->GetId(),Driver->GetMMSI(),Driver->GetSBMSID(),Driver->GetBaseStationId(), false);
	}
}

void CSymbol::AutoManagement()
{
	for(int i = 0; i < GetDriverCount(); i++)
	{
		CDriver *Driver = GetDriver(i);
		_SetCommand(COMMAND_AUTO_MANAGEMENT,Driver->GetId(),Driver->GetMMSI(),Driver->GetSBMSID(),Driver->GetBaseStationId(), false);
	}
}

void CSymbol::Reset()
{
	for(int i = 0; i < GetDriverCount(); i++)
	{
		CDriver *Driver = GetDriver(i);
		_SetCommand(COMMAND_RESET,Driver->GetId(),Driver->GetMMSI(),Driver->GetSBMSID(),Driver->GetBaseStationId(), false);
	}
}

void CSymbol::GetTime()
{
	for(int i = 0; i < GetDriverCount(); i++)
	{
		CDriver *Driver = GetDriver(i);
		_SetCommand(COMMAND_GET_TIME,Driver->GetId(),Driver->GetMMSI(),Driver->GetSBMSID(),Driver->GetBaseStationId(), true);
	}
}

void CSymbol::GetUptime()
{
	for(int i = 0; i < GetDriverCount(); i++)
	{
		CDriver *Driver = GetDriver(i);
		_SetCommand(COMMAND_GET_UPTIME,Driver->GetId(),Driver->GetMMSI(),Driver->GetSBMSID(),Driver->GetBaseStationId(), true);
	}
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

void CSymbol::SetMonitoring(int v)
{
	m_Monitoring = v;
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
	if(m_DriverList.Length() < 0)
		return NULL;
	else
		return m_DriverList.Get(v);
}

bool CSymbol::GetExists()
{
	return m_Exists;
}

int CSymbol::GetMonitoring()
{
	return m_Monitoring;
}