#include <wx/wx.h>
#include "conf.h"
#include "tools.h"
#include "ge64.h"
#include "options.h"
#include "ge64actiondialog.h"
#include "navidrawer.h"
#include "db.h"


CGE64::CGE64(void *db,CNaviBroker *broker)
{
	m_Broker = broker;
	m_Scale = 1;
	m_SmoothScaleFactor = 1;
	m_DB = db;
	m_NightMode = false;
	m_MainLampOn = false;
	m_SecondLampOn = false;
	m_GeneratorOn = false;
	m_ManualOn = false;
	m_TranslationX = 0;
	m_TranslationY = 0;
	m_AlarmOn = false;
}

CGE64::~CGE64()
{
	ClearAlarms();
	
}

void CGE64::ClearAlarms()
{
	m_AlarmList._Clear();
}


void CGE64::SetColor(int id)
{
	glColor4ub(GetColor(id).R,GetColor(id).G,GetColor(id).B,GetColor(id).A);
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

void CGE64::SetSymbolColor()
{

	if(m_MainLampOn || m_SecondLampOn)
		SetColor(SYMBOL_LIGHT_ON_COLOR);
	else
		SetColor(SYMBOL_NORMAL_COLOR);
}

bool CGE64::CheckAlarm()
{	
	m_AlarmOn = !m_AlarmOn;
	wxString sql = wxString::Format(_("SELECT "TABLE_GE64_ALARM".id,id_alarm,set_local_utc_time,confirmed,name,type FROM `%s`,`%s` WHERE id_ge64='%d' AND active='%d' AND id_alarm=`%s`.id ORDER BY set_local_utc_time DESC"),TABLE_GE64_ALARM,TABLE_ALARM,GetId(),ALARM_ACTIVE,TABLE_ALARM);
	my_query(m_DB,sql);
	void *result = db_result(m_DB);
	
    char **row = NULL;
	if(result == NULL)
		return false;
	
	m_Alarm = false;
	CAlarm *Alarm = NULL;
	
	while(row = (char**)db_fetch_row(result))
	{
		int id = atoi(row[FI_SBMS_ALARM_ID]);
		Alarm = (CAlarm*)m_AlarmList._Exists(id);
						
		if(Alarm == NULL)
		{
			Alarm = new CAlarm();
			Alarm->SetNew(true);
			m_AlarmList.Add(Alarm);
			
		}
				
		Alarm->SetId(atoi(row[0]));
		Alarm->SetIdAlarm(atoi(row[1]));
		Alarm->SetAlarmOnDate(Convert(row[2]));
		Alarm->SetConfirmed(atoi(row[3]));
		Alarm->SetName(Convert(row[4]));
		Alarm->SetType(atoi(row[5]));
		Alarm->SetExists(true);

	}	
	
	if(m_AlarmList.size() > 0)
	{
		m_Alarm = true;
		
	}else{
		
		m_Alarm = false;
	}
	
	db_free_result(result);
	
	return true;
}


void CGE64::Read()
{
	fprintf(stderr,"GE64\n");

	m_AlarmList._SetExists(false);
	CheckAlarm();		
	m_AlarmList._Remove();
	
		
}


void CGE64::SetValues()
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

void CGE64::SetSmoothScaleFactor(double v) 
{
	int factor = GetScaleFactor();
	if( m_Scale > factor )
		m_SmoothScaleFactor = m_Scale;
	else
		m_SmoothScaleFactor = factor;
}

void CGE64::RenderAlarm()
{
		
	if(!m_Alarm)
		return;
		
	glPushMatrix();
	if(m_AlarmOn)
		SetColor(SYMBOL_ERROR_COLOR);
	else
		glColor4f(1.0f,1.0f,1.0f,0.3f);
	
	glTranslatef(m_LonMap,m_LatMap,0.0f);
	//glTranslatef(0.0,th/2,0.0f);
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = m_RectWidth * 1.5;
	nvDrawCircleArcFilled(&c,270,0);
		
	glPopMatrix();
		
}



void CGE64::RenderGE64()
{
	SetSymbolColor();
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

void CGE64::Render()
{
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

	SetValues();
	RenderGE64();
	RenderAlarm();
	
	glDisable(GL_BLEND);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);
		
}


//GET
bool CGE64::GetNightMode()
{
	return m_NightMode;
}

bool CGE64::GetMainLampOn()
{
	return m_MainLampOn;
}

bool CGE64::GetSecondLampOn()
{
	return m_SecondLampOn;
}

bool CGE64::GetGeneratorOn()
{
	return m_GeneratorOn;
}

bool CGE64::GetManualOn()
{
	return m_ManualOn;
}

int CGE64::GetAlarmCount()
{
	return m_AlarmList.size();
}

//SET
void CGE64::SetNightMode(bool v)
{
	m_NightMode = v;
}

void CGE64::SetMainOn(bool v)
{
	m_MainLampOn = v;
}

void CGE64::SetSecondLampOn(bool v)
{
	m_SecondLampOn = v;
}

void CGE64::SetGeneratorOn(bool v)
{
	m_GeneratorOn = v;
}

void CGE64::SetManualOn(bool v)
{
	m_ManualOn = v;
}

void CGE64::SetLon(double v)
{
	m_Lon = v;
}		

void CGE64::SetLat(double v)
{
	m_Lat = v;
}

void CGE64::SetLonMap(double v)
{
	m_LonMap = v;
}		

void CGE64::SetLatMap(double v)
{
	m_LatMap = v;
}

wxString CGE64::GetAlarmHtml()
{
	wxString str;
	
	if(m_AlarmList._Length() > 0)
	{
		str.Append(_("<hr>"));
		str.Append(wxString::Format(_("<font size=2><b>%s(%d)</b></font><br><br>"), GetMsg(MSG_ALARM),m_AlarmList._Length()));
		str.Append(_("<table border=0 cellpadding=0 cellspacing=0 width=100%>"));
		
		for(int i = 0; i < m_AlarmList._Length();i++)
		{
			CAlarm *Alarm = (CAlarm*)m_AlarmList._Get(i);
			nvRGBA c = GetAlarmTypeColor(Alarm->GetType());
			str << wxString::Format(_("<tr><td><font color=#%02X%02X%02X size=2>%s</font></td><td><font size=2>%s</font></td></tr>"),c.R,c.G,c.B,Alarm->GetName(),Alarm->GetAlarmOnDate());
		}
	
		str.Append(_("</table>"));
	}
	
	return str;
}

wxString CGE64::GetDriverHtml(int v)
{

	wxString str;
	str.Append(_("<table border=0 cellpadding=0 cellspacing=0 width=100%>"));
	str.Append(wxString::Format(_("<tr><td><font size=2><b>%s(%s)</b></font></td></tr>"), GetMsg(MSG_DRIVER),GetName()));
	for(int i = 0; i < m_AlarmList._Length();i++)
	{
		CAlarm *alarm = (CAlarm*)m_AlarmList._Get(i);
		nvRGBA c = GetAlarmTypeColor(alarm->GetType());
		str << wxString::Format(_("<tr><td><font color=#%02X%02X%02X size=3>%s</font></td></tr>"),c.R,c.G,c.B,alarm->GetName());
	}
		
	//str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td>"),GetLightOnAsString(GetLightOn())));
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
	wxString sql = wxString::Format(_("SELECT name,local_utc_time,night_mode,main_lamp_on,second_lamp_on,generator_on,manual_on FROM `%s` WHERE id ='%d'"),TABLE_GE64,GetId());
	my_query(db,sql);
			
	void *result = db_result(db);
		
	char **row = NULL;
	if(result == NULL)
		return wxEmptyString;
		
	row = (char**)db_fetch_row(result);
	if(row)
	{
		str.Append(_("<hr>"));
		str.Append(wxString::Format(_("<font size=2><b>%s(%s)</b></font><br><br>"), GetMsg(MSG_DRIVER),Convert(row[0])));
		str.Append(_("<table border=0 cellpadding=0 cellspacing=0 width=100%>"));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_DATE_TIME_UTC),Convert(row[1])));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_NIGHT_MODE),GetOnOff(atoi(row[2]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_MAIN_LAMP_ON),GetOnOff(atoi(row[3]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_SECOND_LAMP_ON),GetOnOff(atoi(row[4]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_GENERATOR_ON),GetOnOff(atoi(row[5]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_MANUAL_ON),GetOnOff(atoi(row[6]))));
		
		str.Append(_("</table>"));
		
	}
		
	db_free_result(result);

	DBClose(db);

	return str;

}
