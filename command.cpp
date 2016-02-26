#include <wx/wx.h>
#include "command.h"
#include "conf.h"

CCommand::CCommand()
{
	m_New = false;
}

//SET
void CCommand::SetSymbolName(wxString v)
{
	m_SymbolName = v;
}

void CCommand::SetName(wxString v)
{
	m_Name = v;
}

void CCommand::SetType(int v)
{
	m_Type = v;
}

void CCommand::SetUserFirstName(wxString v)
{
	m_UserFirstName = v;
}

void CCommand::SetUserLastName(wxString v)
{
	m_UserLastName = v;
}

void CCommand::SetStatus(int v)
{
	m_Status = v;
}

void CCommand::SetStatusText(wxString v)
{
	m_StatusText = v;
}

void CCommand::SetCommandDate(wxString v)
{
	m_CommandDate = v;
}

void CCommand::SetDriverType(int v)
{
	m_DriverType = v;
}

//GET
wxString CCommand::GetName()
{
	return m_Name;
}

wxString CCommand::GetSymbolName()
{
	return m_SymbolName;
}

int CCommand::GetType()
{
	return m_Type;
}

int CCommand::GetStatus()
{
	return m_Status;
}

int CCommand::GetDriverType()
{
	return m_DriverType;
}

wxString CCommand::GetStatusText()
{
	return m_StatusText;
}

wxString CCommand::GetUserFirstName()
{
	return m_UserFirstName;
}

wxString CCommand::GetUserLastName()
{
	return m_UserLastName;
}


