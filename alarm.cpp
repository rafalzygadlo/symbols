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

//GET
int CAlarm::GetId()
{
	return m_Id;
}

wxString CAlarm::GetName()
{
	return m_Name;
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