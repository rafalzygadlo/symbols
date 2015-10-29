#include <wx/wx.h>
#include "command.h"
#include "conf.h"

CCommand::CCommand()
{
	m_New = false;
	m_Exists = false;
	
}

//SET
void CCommand::SetId(int v)
{
	m_Id = v;
}

void CCommand::SetSymbolName(wxString v)
{
	m_SymbolName = v;
}

void CCommand::SetName(wxString v)
{
	m_Name = v;
}

void CCommand::SetExists(bool v)
{
	m_Exists = v;
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

void CCommand::SetIdCommand(int v)
{
	m_IdCommand = v;
}

//GET
int CCommand::GetId()
{
	return m_Id;
}

wxString CCommand::GetName()
{
	return m_Name;
}

wxString CCommand::GetSymbolName()
{
	return m_SymbolName;
}

bool CCommand::GetExists()
{
	return m_Exists;
}

int CCommand::GetType()
{
	return m_Type;
}

wxString CCommand::GetUserFirstName()
{
	return m_UserFirstName;
}

wxString CCommand::GetUserLastName()
{
	return m_UserLastName;
}
