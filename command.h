#ifndef __COMMAND
#define __COMMAND

#include "conf.h"

class CCommand
{	
	int m_Id;
	int m_Type;
	int m_Status;
	wxString m_Name;
	wxString m_SymbolName;
	wxString m_UserFirstName;
	wxString m_UserLastName;
	bool m_New;
	bool m_Exists;
	int m_IdCommand;
	
public:

	CCommand();
	//SET
	void SetId(int v);
	void SetName(wxString v);
	void SetSymbolName(wxString v);
	//void SetNew(bool v);
	void SetExists(bool v);
	//void SetConfirmed(bool v);
	void SetType(int v);
	void SetAlarmOnDate(wxString v);
	void SetUserFirstName(wxString v);
	void SetUserLastName(wxString v);
	void SetStatus(int v);
	void SetIdCommand(int v);
			
	//GET
	int GetId();
	wxString GetName();
	wxString GetSymbolName();
	//bool GetNew();
	bool GetExists();
	//bool GetConfirmed();
	int GetType();
	wxString GetAlarmOnDate();
	wxString GetUserFirstName();
	wxString GetUserLastName();
	

};



#endif