#include <wx/wx.h>
#include "groupmodel.h"
#include "conf.h"

CGroupModel::CGroupModel()
{
	m_New = false;
	m_ItemCount = 0;
}

//SET
void CGroupModel::SetName(wxString v)
{
	m_Name = v;
}

void CGroupModel::SetNew(bool v)
{
	m_New = v;
}

void CGroupModel::SetItemCount(int v)
{
	m_ItemCount = v;
}

void CGroupModel::SetCode(wxString v)
{
	m_Code = v;
}

//GET
wxString CGroupModel::GetName()
{
	return m_Name;
}

bool CGroupModel::GetNew()
{
	return m_New;
}

int CGroupModel::GetItemCount()
{
	return m_ItemCount;
}

wxString CGroupModel::GetCode()
{
	return m_Code;
}