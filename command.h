#ifndef __COMMAND
#define __COMMAND

#include "conf.h"

class CCommand
{	
	bool m_New;
	bool m_Exists;
	int m_Id;
	int m_Type;
	int m_Status;
	wxString m_StatusText;
	wxString m_Name;
	wxString m_SymbolName;
	wxString m_UserFirstName;
	wxString m_UserLastName;
	
public:

	CCommand();
	
	//SET
	void SetId(int v);
	void SetName(wxString v);
	void SetSymbolName(wxString v);
	void SetExists(bool v);
	void SetType(int v);
	void SetStatus(int v);
	void SetAlarmOnDate(wxString v);
	void SetUserFirstName(wxString v);
	void SetUserLastName(wxString v);
	void SetStatusText(wxString v);
				
	//GET
	int GetId();
	bool GetExists();
	
	int GetType();
	int GetIdCommand();
	int GetStatus();

	wxString GetStatusText();
	wxString GetName();
	wxString GetSymbolName();
	wxString GetAlarmOnDate();
	wxString GetUserFirstName();
	wxString GetUserLastName();

	

};



#endif