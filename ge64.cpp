#include <wx/wx.h>
#include "conf.h"
#include "tools.h"
#include "ge64.h"
#include "options.h"
#include "ge64actiondialog.h"
#include "db.h"


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
	str.Append(wxString::Format(_("<tr><td><font size=2><b>%s(%s)</b></font></td></tr>"), GetMsg(MSG_DRIVER),GetName()));
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

wxString CGE64::GetDriverFullHtml()
{
	void *db = DBConnect();

	if(db == NULL)
		return wxEmptyString;

	wxString str;
	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id ='%d'"),TABLE_GE64,GetId());
	my_query(db,sql);
			
	void *result = db_result(db);
		
	char **row = NULL;
	if(result == NULL)
		return wxEmptyString;
		
	row = (char**)db_fetch_row(result);
	if(row)
	{
		str.Append(_("<hr>"));
		str.Append(wxString::Format(_("<font size=2><b>%s(%s)</b></font><br><br>"), GetMsg(MSG_DRIVER),Convert(row[FI_GE64_NAME])));
		str.Append(_("<table border=0 cellpadding=0 cellspacing=0 width=100%>"));
		str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td></tr>"),GetLightOnAsString(GetLightOn())));
		//str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td></tr>"),GetAutoAsString(GetAuto())));
		//str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td></tr>"),GetChargingAsString()));
				
		
		//nvtime_t dt;
		//nvdatetime(atoi(row[FI_SBMS_LOCAL_UTC_TIME]),&dt);
		//str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_DATE_TIME_UTC),Convert(row[FI_SBMS_LOCAL_UTC_TIME])));
		//str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_LATITUDE),FormatLatitude(atof(row[FI_SBMS_LAT]),DEFAULT_DEGREE_FORMAT)));
		//str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_LONGITUDE),FormatLongitude(atof(row[FI_SBMS_LON]),DEFAULT_DEGREE_FORMAT)));
		//str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_INPUT_VOLT),row[FI_SBMS_INPUT_VOLT]));
		//str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>100%%</b></font></td></tr>"),GetMsg(MSG_POWER_OF_LIGHT)));
		//str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_MONITORED_CHANNELS),GetMonitoredChannels(atoi(row[FI_SBMS_MONITORED_CHANNELS]))));
		//str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_OVERLOAD_CHANNELS),GetOverloadChannels(atoi(row[FI_SBMS_OVERLOAD_CHANNELS]))));
		//str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_DOWN_CHANNELS),GetDownChannels(atoi(row[FI_SBMS_DOWN_CHANNELS]))));
		//str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_ANALOG_VALUE),row[FI_SBMS_ANALOG_VALUE]));
		//str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_CALIBRATED),GetOnOff(atoi(row[FI_SBMS_MODE_CALIBRATED]))));
		//str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_FORCED_OFF),GetOnOff(atoi(row[FI_SBMS_MODE_FORCED_OFF]))));
		//str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_PHOTOCELL_NIGHT_TIME),GetPhotoCellValue(atoi(row[FI_SBMS_ANALOG_PIN]), atoi(row[FI_SBMS_ANALOG_VALUE]))));
		//str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_FAULT_OUTPUT),GetOnOff(atoi(row[FI_SBMS_MODE_FAULT_OUTPUT]))));
		//str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_SOLAR_CHARGER_ON),GetOnOff(atoi(row[FI_SBMS_MODE_SOLAR_CHARGER_ON]))));
		//str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_SEASON_CONTROL),GetOnOff(atoi(row[FI_SBMS_MODE_SEASON_CONTROL]))));
		
		
		str.Append(_("</table>"));
		
	}
		
	db_free_result(result);

	DBClose(db);

	return str;

}
