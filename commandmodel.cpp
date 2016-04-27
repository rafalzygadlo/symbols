#include <wx/wx.h>
#include "commandmodel.h"
#include "conf.h"

CCommandModel::CCommandModel()
{
	m_New = false;
}

//SET
void CCommandModel::SetSymbolName(wxString v)
{
	m_SymbolName = v;
}

void CCommandModel::SetName(wxString v)
{
	m_Name = v;
}

void CCommandModel::SetType(int v)
{
	m_Type = v;
}

void CCommandModel::SetUserFirstName(wxString v)
{
	m_UserFirstName = v;
}

void CCommandModel::SetUserLastName(wxString v)
{
	m_UserLastName = v;
}

void CCommandModel::SetStatus(int v)
{
	m_Status = v;
}

void CCommandModel::SetStatusText(wxString v)
{
	m_StatusText = v;
}

void CCommandModel::SetDateAdd(wxString v)
{
	m_DateAdd = v;
}

void CCommandModel::SetDateSend(wxString v)
{
	m_DateSend = v;
}

void CCommandModel::SetDriverType(int v)
{
	m_DriverType = v;
}

//GET
wxString CCommandModel::GetName()
{
	return m_Name;
}

wxString CCommandModel::GetSymbolName()
{
	return m_SymbolName;
}

int CCommandModel::GetType()
{
	return m_Type;
}

int CCommandModel::GetStatus()
{
	return m_Status;
}

int CCommandModel::GetDriverType()
{
	return m_DriverType;
}

wxString CCommandModel::GetStatusText()
{
	return m_StatusText;
}

wxString CCommandModel::GetUserFirstName()
{
	return m_UserFirstName;
}

wxString CCommandModel::GetUserLastName()
{
	return m_UserLastName;
}

wxString CCommandModel::GetDateAdd()
{
	return m_DateAdd;
}

wxString CCommandModel::GetDateSend()
{
	return m_DateSend;
}


