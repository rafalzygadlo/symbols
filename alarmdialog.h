#ifndef __ALARMDIALOG
#define __ALARMDIALOG

#include <wx/wx.h>
#include "conf.h"
#include "symbol.h"

class CSymbol;
class CAlarmDialog: public wxDialog
{
	wxHtmlWindow *m_TextAlarm;
	wxString m_Html;
	int m_Counter;

	wxPanel *GetPanel(wxWindow *parent);
	void OnSetAlarm(wxCommandEvent &event);
	void OnOk(wxCommandEvent &event);
	bool Validate();
	
public:

	CAlarmDialog();
	~CAlarmDialog();
	void Set(CSymbol *v);
	void ClearAlert();
	bool IsNewAlert();
	bool IsValidating();
	void ShowWindow();
	
	DECLARE_EVENT_TABLE();
		
	enum
	{
		ID_CONFIRM = 3412,
		ID_ALARM,
		ID_OK,
	};

};



#endif