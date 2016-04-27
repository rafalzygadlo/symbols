#ifndef __COMMAND_MODEL
#define __COMMAND_MODEL

#include "conf.h"
#include "listitem.h"

class CCommandModel :public CListItem
{	
	bool m_New;
	int m_Type;
	int m_Status;
	int m_DriverType;
	wxString m_StatusText;
	wxString m_Name;
	wxString m_SymbolName;
	wxString m_UserFirstName;
	wxString m_UserLastName;
	wxString m_DateAdd;
	wxString m_DateSend;
	
public:

	CCommandModel();
	
	//SET
	void SetName(wxString v);
	void SetSymbolName(wxString v);
	void SetType(int v);
	void SetStatus(int v);
	void SetDateAdd(wxString v);
	void SetDateSend(wxString v);
	void SetUserFirstName(wxString v);
	void SetUserLastName(wxString v);
	void SetStatusText(wxString v);
	void SetDriverType(int v);
				
	//GET
	
	int GetType();
	int GetIdCommand();
	int GetStatus();
	int GetDriverType();

	wxString GetStatusText();
	wxString GetName();
	wxString GetSymbolName();
	wxString GetDateAdd();
	wxString GetDateSend();
	wxString GetUserFirstName();
	wxString GetUserLastName();

	

};



#endif