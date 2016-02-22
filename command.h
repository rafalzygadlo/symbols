#ifndef __COMMAND
#define __COMMAND

#include "conf.h"
#include "listitem.h"

class CCommand :public CListItem
{	
	bool m_New;
	int m_Type;
	int m_Status;
	wxString m_StatusText;
	wxString m_Name;
	wxString m_SymbolName;
	wxString m_UserFirstName;
	wxString m_UserLastName;
	wxString m_CommandDate;
	
public:

	CCommand();
	
	//SET
	void SetName(wxString v);
	void SetSymbolName(wxString v);
	void SetType(int v);
	void SetStatus(int v);
	void SetCommandDate(wxString v);
	void SetUserFirstName(wxString v);
	void SetUserLastName(wxString v);
	void SetStatusText(wxString v);
				
	//GET
	
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