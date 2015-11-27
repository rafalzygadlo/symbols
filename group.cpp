#include <wx/wx.h>
#include "group.h"
#include "conf.h"

CGroup::CGroup()
{
	m_New = false;
	m_Exists = false;
}

//SET
void CGroup::SetId(int v)
{
	m_Id = v;
}

void CGroup::SetName(wxString v)
{
	m_Name = v;
}

void CGroup::SetNew(bool v)
{
	m_New = v;
}

void CGroup::SetExists(bool v)
{
	m_Exists = v;
}

//GET
int CGroup::GetId()
{
	return m_Id;
}

wxString CGroup::GetName()
{
	return m_Name;
}

bool CGroup::GetNew()
{
	return m_New;
}

bool CGroup::GetExists()
{
	return m_Exists;
}
