#include <wx/wx.h>
#include "alarmmodel.h"
#include "conf.h"


CAlarmModel::CAlarmModel()
{
	m_New = false;
	m_Confirmed = false;
}

//SET
void CAlarmModel::SetIdAlarm(int v)
{
	m_IdAlarm = v;
}

void CAlarmModel::SetSymbolName(wxString v)
{
	m_SymbolName = v;
}

void CAlarmModel::SetName(wxString v)
{
	m_Name = v;
}

void CAlarmModel::SetNew(bool v)
{
	m_New = v;
}

void CAlarmModel::SetConfirmed(bool v)
{
	m_Confirmed = v;
}

void CAlarmModel::SetType(int v)
{
	m_Type = v;
}

void CAlarmModel::SetAlarmOnDate(wxString v)
{
	m_AlarmOnDate = v;
}

void CAlarmModel::SetUserFirstName(wxString v)
{
	m_UserFirstName = v;
}

void CAlarmModel::SetUserLastName(wxString v)
{
	m_UserLastName = v;
}

void CAlarmModel::SetDriverType(int v)
{
	m_DriverType = v;
}

//GET
int CAlarmModel::GetIdAlarm()
{
	return m_IdAlarm;
}

wxString CAlarmModel::GetName()
{
	return m_Name;
}

wxString CAlarmModel::GetSymbolName()
{
	return m_SymbolName;
}

bool CAlarmModel::GetNew()
{
	return m_New;
}

bool CAlarmModel::GetConfirmed()
{
	return m_Confirmed;
}

int CAlarmModel::GetType()
{
	return m_Type;
}

wxString CAlarmModel::GetAlarmOnDate()
{
	return m_AlarmOnDate;
}

wxString CAlarmModel::GetUserFirstName()
{
	return m_UserFirstName;
}

wxString CAlarmModel::GetUserLastName()
{
	return m_UserLastName;
}

int CAlarmModel::GetDriverType()
{
	return m_DriverType;
}
