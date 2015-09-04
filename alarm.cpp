#include <wx/wx.h>
#include "alarm.h"
#include "conf.h"

CAlarm::CAlarm()
{
	
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

//GET
int CAlarm::GetId()
{
	return m_Id;
}

wxString CAlarm::GetName()
{
	return m_Name;
}
