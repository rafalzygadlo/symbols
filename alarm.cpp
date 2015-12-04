#include <wx/wx.h>
#include "alarm.h"
#include "conf.h"

CAlarm::CAlarm()
{
	m_New = false;
	m_Exists = false;
	m_Confirmed = false;
}

//SET
void CAlarm::SetId(int v)
{
	m_Id = v;
}

void CAlarm::SetIdAlarm(int v)
{
	m_IdAlarm = v;
}

void CAlarm::SetSymbolName(wxString v)
{
	m_SymbolName = v;
}

void CAlarm::SetName(wxString v)
{
	m_Name = v;
}

void CAlarm::SetNew(bool v)
{
	m_New = v;
}

void CAlarm::SetExists(bool v)
{
	m_Exists = v;
}

void CAlarm::SetConfirmed(bool v)
{
	m_Confirmed = v;
}

void CAlarm::SetType(int v)
{
	m_Type = v;
}

void CAlarm::SetAlarmOnDate(wxString v)
{
	m_AlarmOnDate = v;
}

void CAlarm::SetUserFirstName(wxString v)
{
	m_UserFirstName = v;
}

void CAlarm::SetUserLastName(wxString v)
{
	m_UserLastName = v;
}

//GET
int CAlarm::GetId()
{
	return m_Id;
}

int CAlarm::GetIdAlarm()
{
	return m_IdAlarm;
}

wxString CAlarm::GetName()
{
	return m_Name;
}

wxString CAlarm::GetSymbolName()
{
	return m_SymbolName;
}

bool CAlarm::GetNew()
{
	return m_New;
}

bool CAlarm::GetExists()
{
	return m_Exists;
}

bool CAlarm::GetConfirmed()
{
	return m_Confirmed;
}

int CAlarm::GetType()
{
	return m_Type;
}

wxString CAlarm::GetAlarmOnDate()
{
	return m_AlarmOnDate;
}

wxString CAlarm::GetUserFirstName()
{
	return m_UserFirstName;
}

wxString CAlarm::GetUserLastName()
{
	return m_UserLastName;
}
