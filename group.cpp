#include <wx/wx.h>
#include "group.h"
#include "conf.h"

CGroup::CGroup()
{
	m_New = false;
}

//SET
void CGroup::SetName(wxString v)
{
	m_Name = v;
}

void CGroup::SetNew(bool v)
{
	m_New = v;
}

//GET
wxString CGroup::GetName()
{
	return m_Name;
}

bool CGroup::GetNew()
{
	return m_New;
}
