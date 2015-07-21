#ifndef __ALARMDIALOG
#define __ALARMDIALOG

#include <wx/wx.h>
#include "conf.h"

class CAlarmDialog: public wxDialog
{
	void *m_DB;
	wxPanel *m_Panel;
	wxTextCtrl *m_TextAlert;
	wxScrolledWindow *m_Scroll;
	bool m_Validate;
	wxString m_StationName;

	wxPanel *GetPanel(wxWindow *parent);
	wxArrayPtrVoid m_Panels;
	bool Validate();
	
public:

	CAlarmDialog(void *db,wxString station);
	~CAlarmDialog();
	//void Set(CData *v);
	void ClearAlert();
	bool IsNewAlert();
	bool IsValidating();
	
	DECLARE_EVENT_TABLE();
		
	enum
	{
		ID_CONFIRM = 3412,
	};

};

class CAlarmPanel: public wxPanel
{
	void *m_DB;
	SAlert *m_Alert;
	void OnConfirm(wxCommandEvent &event);
	
public:

	CAlarmPanel(void *db,wxWindow *parent, SAlert *v);
	void Confirm();
		
	DECLARE_EVENT_TABLE();
		
	enum
	{
		ID_CONFIRM = 3412,
	};

};


#endif