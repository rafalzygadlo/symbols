#include <wx/wx.h>
#include "conf.h"
#include "tools.h"
#include "ge64.h"
#include "options.h"
#include "ge64actiondialog.h"


CGE64::CGE64(void *db,CNaviBroker *broker)
{
	m_DB = db;
	m_LightOn = false;
	
}

CGE64::~CGE64()
{	
	
	
}

void CGE64::ShowAction()
{
	void *db = DBConnect();
	if(db == NULL)
		return;

	CGE64ActionDialog *GE64ActionDialog = new CGE64ActionDialog(db,this);
	GE64ActionDialog->ShowModal();
	delete GE64ActionDialog;
	
	DBClose(db);
}

int CGE64::GetLightOn()
{
	return m_LightOn;
}

wxString CGE64::GetDriverHtml(int v)
{

	wxString str;

	str.Append(_("<table border=0 cellpadding=0 cellspacing=0 width=100%>"));
	
	//for(int i = 0; i < GetAlarmCount();i++)
	//{
		//CAlarm *alarm = GetAlarm(i);
		//nvRGBA c = GetAlarmTypeColor(alarm->GetType());
		//str << wxString::Format(_("<tr><td><font color=#%02X%02X%02X size=3>%s</font></td></tr>"),c.R,c.G,c.B,alarm->GetName());
	//}
		
	str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td>"),GetLightOnAsString(GetLightOn())));
	//str.Append(_("<td rowspan=2 align=right width=80>"));
	//if(GetInputVolt() > GetUpperThreshold() || GetInputVolt() < GetLowerThreshold())
		//str.Append(wxString::Format(_("<a target=0 href='%d'><font size=4 color=red>%s</font></a>"),v,GetInputVoltAsString()));
	//else
		//str.Append(wxString::Format(_("<a target=0 href='%d'><font size=4>%s</font></a>"),v, GetInputVoltAsString()));
		
	//str.Append(_("</td>"));
	//str.Append(wxString::Format(_("<tr><td><font size=3>%s</font></td></tr>"),GetAutoAsString(GetAuto())));
	//str << wxString::Format(_("<tr><td><font size=3>%s</font></td></tr>"),GetChargingAsString());
	//str << wxString::Format(_("<tr><td><font size=3>%s</font></td></tr>"),GetAgeAsString());
	//str << wxString::Format(_("<tr><td> </td></tr>"),GetBaseStationName());
	str.Append(_("</table>"));
	return str;

}
